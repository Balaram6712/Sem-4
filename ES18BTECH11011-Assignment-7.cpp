#include<iostream>
#include<malloc.h>
#include<fstream>
#include<cstdio>
#define MAX 100000
using namespace std;

int count = 0;			//keeping a count of number of variables
struct node
{
  int val;
  int size;			//size of the subtree need to see with or without including that node
  struct node *left;		//link to left node
  struct node *right;		//link to right node
  struct node *parent;
};

node *
new_node (int x,node *pr)		//fucntion when we create a new node
{
  node *temp = new node ();	//allocating space dynamically
  temp->val = x;		//entering value of the node into it
  temp->left = NULL;		//left and right links are NULL
  temp->right = NULL;
  if(count==0)
  {
    temp->parent = NULL;
  }
  else
  {
    temp->parent = pr;  
  }
  
  temp->size = 1;     //initialising node size to 1 
  return temp;
}

node *
find (node * root, int key, int &dep)	//function to find a key value in the bst
{
  if (root == NULL || root->val == key)
    {
      if (root == 0)
	{
	  dep = 0;		//if not found then depth is made 0 and false is printed
	}
      return root;		//if node found we return the root value
    }
  if (root->val < key)
    {
      dep = dep + 1;
      return find (root->right, key, dep);	//incrementing the depth if key value > present node value then we move right in the bst 
    }

  if (root->val > key)
    {
      dep = dep + 1;
      return find (root->left, key, dep);	//incrementing the depth if key value < present node value then we move left in the bst
    }
}

int
get_size (node * t)		//a function to find the size of the subtree when node is passed through it where size is stored in its node
{
  if (t == NULL)
    {
      return 0;
    }
  return t->size;
}

void
fix_size (node * t)		//fix size which helps fixing the size of the s
{
  t->size = get_size (t->left) + get_size (t->right) + 1;
}

node *
rotate_right (node * p)
{
  node *q;
  q = p->left;
  if (q == NULL)
    {
      return p;
    }
  p->left = q->right;
  if(q->right!=NULL)
  {
    q->right->parent = p;
  }
  q->right = p;
  q->parent = p->parent;
  p->parent = q;
  fix_size (p);			//rotating right a node and ints child to right to set the roor insertion to corect position
  fix_size (q);
  return q;
}

node *
rotate_left (node * p)
{
  node *q;
  q = p->right;
  if (q == NULL)
    {
      return p;			//rotating left a node and its child to right to set the root insertion to correct position
    }
  p->right = q->left;
  if(q->left!=NULL)
  {
    q->left->parent = p;
  }
  q->left = p;
  q->parent = p->parent;
  p->parent = q;
  fix_size (p);
  fix_size (q);
  return q;
}

node *
insert_root (node * ro, int k,node *pt)
{
  if (ro == NULL)
    {
      return new_node (k,pt);	//if no node present we insert new node
    }
  if (ro->val > k)		//if the value is less than current root,insert it in right place and then roatte right and set it correct so that it becomes the root of that subtree where it wants to root of the tree randomised fashion
    {				//similarly for the value greater than current node we insert and then left rotate and set it as root
      pt = ro;
      ro->left = insert_root (ro->left, k,pt);
      return rotate_right (ro);
    }
  else
    {
      pt = ro;
      ro->right = insert_root (ro->right, k,pt);
      return rotate_left (ro);
    }
}

node *
insert (node * nde, int k,node *pt)	// a classic insertion of a new node with k key in p tree
{
  if (nde == NULL)
    {
      return new_node (k,pt);
    }
  if (rand () % (nde->size + 1) == nde->size)	//probability of 1/n 
    {
      pt = nde;
      return insert_root (nde, k,pt);	//calling insert root function
    }
  if (nde->val > k)
    {
      pt = nde;
      nde->left = insert (nde->left, k,pt);	//if not randomised then we insert normally into left subtree if insert less than present node value in that subtree it might be root insert based on randomised insertion in that subtree 
    }				//similar insert into the right subtree if insert value greater than current node value
  else
    {
      pt = nde;
      nde->right = insert (nde->right, k,pt);
    }
  fix_size (nde);
  return nde;
}

node *
join (node * a, node * b)	//a join function which works in randomized way if we want to delet a node with 2 children 
{				//it might make the left child a root or the right subtree root based on the sizes of the the subtrees corresponfingly 
  if (a == NULL)
    {
      return b;
    }
  if (b == NULL)
    {
      return a;
    }
  if (rand () % (a->size + b->size) < a->size)	//checking probability of left node becoming a root when its parent node is deleted
    {
      a->right = join (a->right, b);
      fix_size (a);
      return a;			//making left chilad parent and joining the right child of left node and right child of the deleted tree and joining them 
    }
  else				//checking probability of left node becoming a root when its parent node is deleted
    {
      b->left = join (a, b->left);
      fix_size (b);
      return b;
    }
}

node *
del_node (node * rem, int k)	//function to delete node 
{
  int p = 0;
  if (rem == NULL)
    {
      return NULL;
    }
  if (k < rem->val)
    {
      rem->left = del_node (rem->left, k);	//if value to be deleted less than current node value then we go to left subtree
    }
  else if (k > rem->val)
    {
      rem->right = del_node (rem->right, k);	//if value to be deleted greater than current node value then we go to right subtree
    }
  else
    {
      node *temp;
      temp = rem;		//if value found we deleyed that node and call the join function to join the two subtrees
      rem = join (rem->left, rem->right);
      if(rem!=NULL)               //root of the joined tree is being returned by join function
      {
        rem->parent = temp->parent;
      }
      free (temp);
    }
  return rem;
}

void
print_inorder (node * nde, ofstream & fot)
{				//function to print inorder traversal of the tree which is left,root,right traversal of the bst 
  if (nde == NULL)
    {
      return;
    }
  print_inorder (nde->left, fot);
  fot << nde->val << " ";
  print_inorder (nde->right, fot);
}

void
print_preorder (node * nde, ofstream & fot)
{
  if (nde == NULL)		//function to print inorder traversal of the tree which is root,left,right traversal of the bst
    {
      return;
    }
  fot << nde->val << " ";
  print_preorder (nde->left, fot);
  print_preorder (nde->right, fot);
}

void
print_postorder (node * nde, ofstream & fot)
{
  if (nde == NULL)		//function to print inorder traversal of the tree which is root,left,right traversal of the bst
    {
      return;
    }
  print_postorder (nde->left, fot);
  print_postorder (nde->right, fot);
  fot << nde->val << " ";
}

void
print_tree (node * nde, ofstream & fot)
{
  node *p = nde;
  fot << "In-order Traversal: ";	//function called in main function to print all the 3 traversals
  print_inorder (p, fot);
  fot << "\n";
  fot << "Pre-order Traversal: ";
  print_preorder (p, fot);
  fot << "\n";
  fot << "Post-order Traversal: ";
  print_postorder (p, fot);
  fot << "\n";
}

int
main ()
{
  FILE *in;			//file pointers
  in = fopen ("input.txt", "r");	//opening input file in read format
  int a[MAX];			//array to store the input
  int n;
  int len = 0;
  while (!feof (in))
    {
      fscanf (in, "%d", &a[len]);
      len = len + 1;		//taking intput from the file and strdoring it in a array
    }
  fclose (in);
  int id = 1;
  node *root = NULL;
  srand (time (0));
  ofstream fout;
  fout.open ("output.txt", ios::trunc);
  fout.close ();
  fout.open ("output.txt", ios::app);
  while (a[0]--)		//as first value is the number of operations to be given we loop over that value acordingly
    {

      int op;
      int val;
      id = id + 1;		//using id to iterate over the array to perform the function accordingly
      int dep = 0;
      int k = 1;
      switch (a[id - 1])
	{
	case 1:
	  count = count + 1;
	  id = id + 1;
	  root = insert (root, a[id - 1],NULL);	//, NULL);      //calling insert function
	  if (root != NULL)
	    {
	      fout << "true\n\n";	//if insert successful true is printed
	    }
	  else
	    {
	      fout << "flase\n\n";	//if insert not successful then false is printed
	    }
	  break;
	case 2:
	  id = id + 1;
	  dep = 0;
	  if (find (root, a[id - 1], dep) == NULL)
	    {
	      fout << "flase\n\n";	//if delete failed then false is printed stating the key is not present in the bst
	    }
	  else
	    {
	      fout << "true\n\n";	//true is printed if delete sucessfull
	      count = count - 1;
	      root = del_node (root, a[id - 1]);	//calling function to delete a node
	      fix_size (root);
	    }
	  break;
	case 3:
	  if (count == 0)
	    {
	      fout << "No elements in the bst\n\n";	//if count is zero then there are no elemnts in the bst
	    }
	  else
	    {
	      print_tree (root, fout);	//calling the print function
	      fout << "\n";
	    }
	}
    }
  fout.close ();
}
