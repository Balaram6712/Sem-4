#include<iostream>
#include<stdio.h>
#include<malloc.h>
#include<limits.h>
#include<string.h>
#include<cstdio>
#include<fstream>
#define MAX 100000
using namespace std;
int count = 0;
struct node
{
  int val;
  struct node *left;
  struct node *right;
  struct node *parent;
};				//node in the tree with parent link,left link,right link,node value in it

node *
new_node (int x, struct node *pr)
{
  node *temp = new node ();	//allocation of memory to the 
  temp->val = x;
  temp->left = NULL;
  temp->right = NULL;
  if (count == 0)
    {
      temp->parent = NULL;	//if root node then parent is null
    }
  else
    {
      temp->parent = pr;	//if it is not root node then we stre the parent datails in the node
    }
  return temp;			//return the newly created node
};

node *
insert (node * nd, int k, struct node * par)
{
  if (nd == NULL)
    {
      return new_node (k, par);	//if we find the correct place to insert the node then we call the new node function to create and insert the element
    }
  if (k < nd->val)
    {
      par = nd;
      nd->left = insert (nd->left, k, par);	//if key we want ot insert less than current position move left
    }
  else if (k > nd->val)
    {
      par = nd;
      nd->right = insert (nd->right, k, nd);	//if key we want ot insert more than current position move right
    }
  return nd;
}

node *
max_key (node * nde)
{
  while (nde->right != NULL)
    {
      nde = nde->right;		//finding maximum by moving right wards in the bst and finding max until we reach null
    }
  return nde;
}				//function for finding maximum value in a subtree

void
del_node (node * &root, int key)	//function to delete a node with the key value passed
{
  if (root == NULL)
    {
      return ;
    }
  if (key < root->val)
    {
      del_node (root->left, key);
    }
  else if (key > root->val)
    {
      del_node (root->right, key);
    }				//we need to find the where the key exists by proper traversal if key not found we return 0
  else
    {
      if (root->left == NULL && root->right == NULL)	//if the node wanted to delete is leaf node then delete it
	{
	  delete root;
	  root = NULL;
	}
      else if (root->left && root->right)	//if a node to be deleted has both childs first we find the inorder predecessor for the node and then copy the node value into it and then delete the inorder predecessor accordingly 
	{
	  node *tmp = max_key (root->left);
	  root->val = tmp->val;
	  del_node (root->left, tmp->val);
	}
      else
	{
	  node *dl = (root->left) ? root->left : root->right;
	  node *cr = root;	//if node we want to delete has only 1 child then attach the child to its parent node directly depending if left child or right child is present accordingly
	  root = dl;
	  delete cr;
	}
    }
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

void
print_sub_tree (node * nde, int k, ofstream & fot)
{
  node *t = nde;
  while (t->val != k)
    {
      if (t->val > k)
	{
	  t = t->left;
	}
      else if (t->val < k)
	{
	  t = t->right;
	}			//finding the key value where we need to pass the node to print the subtree from and calling the traversal functions to print the subtree
    }
  fot << "In-order Traversal: ";
  print_inorder (t, fot);
  fot << "\n";
  fot << "Pre-order Traversal: ";
  print_preorder (t, fot);
  fot << "\n";
  fot << "Post-order Traversal: ";
  print_postorder (t, fot);
  fot << "\n";
}

int
calculate_nodes_left (node * nde)
{
  int count_left = 1;
  if (nde->left != NULL)
    {
      count_left = count_left + calculate_nodes_left (nde->left);
    }
  if (nde->right != NULL)
    {
      count_left = count_left + calculate_nodes_left (nde->right);
    }
  return count_left;
}				//function to calculate number of nodes in the left side of the tree

int
calculate_nodes_right (node * nde)
{
  int count_right = 1;
  if (nde->right != NULL)
    {
      count_right = count_right + calculate_nodes_right (nde->right);
    }
  if (nde->left != NULL)
    {
      count_right = count_right + calculate_nodes_right (nde->left);
    }
  return count_right;		//function to calculate number of nodes in the right side of the tree
}

void
calculate_imbalance (node * nde, int key, ofstream & fot)
{
  node *tp = nde;
  while (tp->val != key)
    {
      if (tp->val > key)
	{
	  tp = tp->left;
	}
      else if (tp->val < key)
	{
	  tp = tp->right;
	}
    }				//finding the appropriate node to pass to the function and find the difference in the count of the nodesz of the subtree of the value passed
  int left = 0;
  int right = 0;
  if (tp->left != NULL)
    {
      left = calculate_nodes_left (tp->left);
    }
  if (tp->right != NULL)
    {
      right = calculate_nodes_right (tp->right);
    }
  fot << left - right << "(#left child - #right child = " << left << " - " << right << " = " << left - right << ")\n";	//please obser here that absolute value is not being print only left - right nodes being printed
}

int
main ()
{
  FILE *in;			//file pointers
  in = fopen ("input3.txt", "r");	//opening input file in read format
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
  ofstream fout;		//ofstream to print the output into the output file
  fout.open ("output3.txt", ios::trunc);	//used for printing the output into the file 
  fout.close ();
  fout.open ("output3.txt", ios::app);	//appending the output using the ofstream
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
	  root = insert (root, a[id - 1], NULL);	//calling insert function
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
	  if (find (root, a[id - 1], dep)==NULL)
	    {
	      fout << "flase\n\n";	//if delete failed then false is printed stating the key is not present in the bst
	    }
	  else
	    {
	      fout << "true\n\n";	//true is printed if delete sucessfull
	   	  count = count - 1;
	   	  del_node (root, a[id - 1]);	//calling function to delete a node
	    }
	  break;
	case 3:
	  id = id + 1;
	  dep = 0;
	  if (find (root, a[id - 1], dep) == NULL)	//calling the function to check if value present in the bst or not
	    {
	      fout << "false\n\n";
	    }
	  else
	    {
	      fout << "true, depth: " << dep << "\n\n";	//if value found then we print the depth of the key in the tree also
	    }
	  break;
	case 4:
	  if (count == 0)
	    {
	      fout << "No elements in the bst\n\n";	//if count is zero then there are no elemnts in the bst
	    }
	  else
	    {
	      print_tree (root, fout);	//calling the print function
	    	fout << "\n";
	    }
	  break;
	case 5:
	  id = id + 1;
	  dep = 0;
	  if (count == 0)
	    {
	      fout << "No elements in the bst\n\n";
	    }
	  else if (find (root, a[id - 1], dep) == NULL)
	    {
	      fout << "No such key exists in the tree\n\n";	//if there is no such key with in bst then we print this else call the function
	    }
	  else
	    {
	      print_sub_tree (root, a[id - 1], fout);
	    	fout << "\n";
	    }
	  break;
	case 6:
	  id = id + 1;
	  if (count == 0)
	    {
	      fout << "No elements in the bst\n\n";
	    }
	  else if (find (root, a[id - 1], dep) == NULL)
	    {
	      fout << "No such key exists in the tree\n\n";	//if there is no such key with in bst then we print this print statement
	    }
	  else
	    {
	      calculate_imbalance (root, a[id - 1], fout);	//calling imbaalnce function for a key value passed
	    	fout << "\n";
	    }
	  break;
	}
    }
  fout.close ();		//closing the file
}					//please see that true is printed for insert or delete when the operations are sucessfull false when they are not successfull
