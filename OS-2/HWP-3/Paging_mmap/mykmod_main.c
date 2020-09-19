#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/mm.h>

#include <mydev.h>

MODULE_DESCRIPTION("My kernel module - mykmod");
MODULE_AUTHOR("maruthisi.inukonda [at] gmail.com");
MODULE_LICENSE("GPL");

//teams Sai Balaram and Krishna Pawan
/* Dynamically allocate major no */
#define MYKMOD_MAX_DEVS 256
#define MYKMOD_DEV_MAJOR 0

/* init and cleanup module function */
static int mykmod_init_module(void);
static void mykmod_cleanup_module(void);

/* functions for device special file operations */
static int mykmod_open(struct inode *inode, struct file *filp);
static int mykmod_close(struct inode *inode, struct file *filp);
static int mykmod_mmap(struct file *filp, struct vm_area_struct *vma);

/*initialising the module and exit to unload the module */
module_init(mykmod_init_module);
module_exit(mykmod_cleanup_module);

/* Device special file operations */
static struct file_operations mykmod_fops = {
	.owner  = THIS_MODULE,	/* owner (struct module *) */
	.open   = mykmod_open,	/* open */
	.release  = mykmod_close,	/* release */
	.mmap = mykmod_mmap,	/* mmap */
};

/* functions for file operations at virtual memory region */
static void mykmod_vm_open(struct vm_area_struct *vma);
static void mykmod_vm_close(struct vm_area_struct *vma);
static int mykmod_vm_fault(struct vm_area_struct *vma, struct vm_fault *vmf);

/* structure to keep track of per device info */
struct mykmod_dev_info {
	char *data;
	size_t size;
};							
/* structure to keep per VMA info */
struct vma_track {
	int count;
	struct mykmod_dev_info *dev_data; 
};				

/* file operations done at virtual memory region */
static const struct vm_operations_struct mykmod_vm_ops = {
	.open  = mykmod_vm_open,
	.close = mykmod_vm_close,
	.fault = mykmod_vm_fault
};

/* major number of the device */
int mykmod_major;

/* pagfaults in virtual memory region */
long unsigned npagefaults;

/* init module - registering the device driver and loading it into the kernel */
static int mykmod_init_module(void)
{
	printk("mykmod loaded\n");
	printk("mykmod initialized at=%p\n", init_module);
	
	if ((mykmod_major = register_chrdev(MYKMOD_DEV_MAJOR,"mykmod",&mykmod_fops))<0) {
		printk(KERN_WARNING "Failed to register character device\n");
		return 1;
	}
	else {
		printk("register character device %d\n", mykmod_major);
	}
	return 0;
}						

/* cleanup module - unloading the device driver from the kernel */
static void mykmod_cleanup_module(void)
{
	printk("mykmod unloaded\n");
	unregister_chrdev(mykmod_major,"mykmod");
	return;										
}

/* Device special file open operation */
static int
mykmod_open(struct inode *inodep, struct file *filep)
{
	/* Allocating memory for devinfo and store in device table and i_private. */
	if (inodep->i_private == NULL) {
		struct mykmod_dev_info *info;
		info = (struct mykmod_dev_info *)kmalloc(sizeof(struct mykmod_dev_info), GFP_KERNEL);
		info->data = (char *)kzalloc(MYDEV_LEN,GFP_KERNEL);
		info->size = MYDEV_LEN;
		inodep->i_private = info;
	}					
	/* Storing device info in file's private_data as well as inode private data and printing the data */
	filep->private_data = inodep->i_private;
	printk("mykmod_open: filep=%p f->private_data=%p "
                "inodep=%p i_private=%p i_rdev=%x maj:%d min:%d\n",
                filep, filep->private_data,
                inodep, inodep->i_private, inodep->i_rdev, MAJOR(inodep->i_rdev), MINOR(inodep->i_rdev));
	return 0;
}															

/* Device special file close operation */
static int
mykmod_close(struct inode *inodep, struct file *filep)
{
	printk("mykmod_close: inodep=%p filep=%p\n", inodep, filep);	// printing the inode number and the file pointer
	return 0;
}

/*mapping the device special file data into the memory */
static int mykmod_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct vma_track *dev;
	printk("mykmod_mmap: filp=%p vma=%p flags=%lx\n", filp, vma, vma->vm_flags);
	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;	// setting the flags 
	vma->vm_ops = &mykmod_vm_ops;   // setting up the operations to be peformed
	dev = kmalloc(sizeof(struct vma_track),GFP_KERNEL);	  // allocating the data for the structure by passing the corresponding flag
	dev->dev_data = (struct mykmod_dev_info *)(filp->private_data);	  // storing the file private data in the structure
	vma->vm_private_data = dev;
								// setting up vma's flags, save private data devinfo, npagefaults in vm_private_data
	mykmod_vm_open(vma);	// opening the virtual area 
	return 0;
}

/* file open operation at virtual memory region */
static void
mykmod_vm_open(struct vm_area_struct *vma)
{
	npagefaults = 0;	// as virtual region is opened initialise the npagefaults to zero
	printk("mykmod_vm_open: vma=%p npagefaults:%lu\n", vma, npagefaults);
}

/* file close operation at virtual memory region */
static void
mykmod_vm_close(struct vm_area_struct *vma)
{
	printk("mykmod_vm_close: vma=%p npagefaults:%lu\n", vma,npagefaults);
	npagefaults = 0;	// closing the virtual area and setting the npage faults to zero	
	kfree(vma->vm_private_data);
}

/*vm_fault operation is executed when there is a page fault occured while mapping the memory */
static int
mykmod_vm_fault(struct vm_area_struct *vma, struct vm_fault *vmf)
{
	struct vma_track *dev;	 // vm_fault function is automatically called when a page fault occurs
	struct mykmod_dev_info *info;	// for the data to be mapped
	unsigned long offset;
	dev = (struct vma_track *)vma->vm_private_data;
	info = (struct mykmod_dev_info *)dev->dev_data;
	offset = (unsigned long)(vmf->pgoff << PAGE_SHIFT);	   // the offset to get the correct address to get the correct page 
    vmf->page = virt_to_page((unsigned long)info->data + offset);	// which is free
    get_page(vmf->page);
	printk("mykmod_vm_fault: vma=%p vmf=%p pgoff=%lu page=%p\n", vma, vmf, vmf->pgoff, vmf->page);
	npagefaults++;	  // incrementing the page fault count
	return 0;
}
