Readme


#Project title:

	A linux device driver implementation and to understand how memory mapping is done in Linux


#Motivation:

	The goal of this assignment is to implement prefetch and demand paging on a device special file anf the implementation of the syscall of mmap().The mmap()/munmap() are the most heavily used system calls in Linux.


#Files in Project:
README-Assignment-3-OS-2.txt
REPORT-Asignment-3-OS-2.pdf
2 Source codes:
	1) mykmod_main.c inside kernel directory
	2) memutil.cpp inside the util directory

#Code style:


Written in C++ using standard of GNOME project and DON lab C


#Compiling the programs:

Inside the directory of 99_devmmap_paging:
$: make
which compiles the file and generates the utility file which can be used to test the file

#Running the file with test cases provided:

The utility file can be run by using these commands
Usage:

$ ./util/memutil [options] <devname>

Options:
--operation <optype> : Where optype can be mapread, mapwrite
--message <message> : Message to be written/read-compare to/from the device memory
--paging <ptype>
: Where ptype can be prefetch or demand
--help
: Show this help 
These options can be used to test the utility function

#Testing the file with the scipt:
$ bash runtest.sh
To test the file of the test script which gives the output along with th log files for each test. 
