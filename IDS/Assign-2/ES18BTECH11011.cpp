#include<iostream>
#include<bits/stdc++.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#define MAX 1000

int sym1 = 0;
int sym2 = 0;			//variables for checking symmetric or not

struct node
{
  int val;
  node *right;
  node *down;
};				//structural node created with value and right and down link

node *
construct (int a[][1000], int i, int j, int m, int n)
{
  if (i > m - 1 || j > n - 1)
    {
      return NULL;
    }
  node *temp = new node ();	//creating new node dynamically uisng new() function
  temp->val = a[i][j];
  temp->right = construct (a, i, j + 1, m, n);	//construting right nodes in linked list using recursion
  temp->down = construct (a, i + 1, j, m, n);	//constructing down nodes in linked list using recusrion 
  return temp;
}				//construct linked list with right and down link by passing a matrix and returns the head pointer to the matrix linked lists

void
square (node * hh1, node * hh2, FILE * fp)
{
  node *a1;
  node *a2;
  node *b1;
  node *b2;			//temporary nodes for traversal
  a1 = hh1;
  a2 = hh1;			//assigning the nodes to head
  b1 = hh2;
  b2 = hh2;
  int cn1 = 0, cn2 = 0;
  int dn1 = 0, dn2 = 0;		//variables for checking the number of columns and rows
  while (a1 != NULL)
    {
      cn1 = cn1 + 1;
      a1 = a1->right;
    }
  while (a2 != NULL)
    {
      cn2 = cn2 + 1;
      a2 = a2->down;
    }
  while (b1 != NULL)
    {
      dn1 = dn1 + 1;
      b1 = b1->right;
    }
  while (b2 != NULL)
    {
      dn2 = dn2 + 1;
      b2 = b2->down;		//traversing through the lists and incrementing the count
    }

  if (cn1 == cn2)
    {

      fprintf (fp, "Matrix 1 is square matrix\n");	//printing if the matrix is sqaure or not by checking the length
      sym1 = 1;
    }
  else
    {
      fprintf (fp, "Matrix 1 is not square matrix\n");	//printing if the matrix is sqaure or not by checking the length
      sym1 = 0;
    }

  if (dn1 == dn2)
    {
      fprintf (fp, "Matrix 2 is square matrix\n");	//printing if the matrix is sqaure or not by checking the length
      sym2 = 1;
    }
  else
    {
      fprintf (fp, "Matrix 2 is not square matrix\n");	//printing if the matrix is sqaure or not by checking the length
      sym2 = 0;
    }
}				//function to check the two matrices are square matrices or not

int
symmetric (node * q)
{
  node *dig;
  node *ris;			//nodes for traversal and checking symmetry
  node *dos;
  dig = q;
  if (dig->down == NULL)
    {
      return 1;
    }
  else
    {
      ris = dig->right;
      dos = dig->down;		//traversing down and right checking a[i][j] = a[j][i]
      while (1)
	{
	  if (ris->val != dos->val)
	    {
	      return 0;
	    }
	  ris = ris->right;
	  dos = dos->down;
	  if (ris == NULL)
	    {
	      return symmetric (dig->down->right);	//recursing on the diagonal elemnt and checkcing the sub part is symmetric or not
	    }
	}
    }
}				//function to check if the matrices are symmetric or not by passing head node of the matrices

void
mul (node * y1, node * y2, FILE * fpp)
{
  node *mat1rowit;
  node *mat2rowit;
  node *mat1colit;
  node *mat2colit;
  mat1rowit = y1;
  mat2rowit = y2;
  mat1colit = y1;		//assigning temporary nodes to the head
  mat2colit = y2;		//four temporary nodes to point and do the multiplication
  int temp = 0;
  fprintf (fpp, "Resultant Matrix:\n");
  while (mat1rowit != NULL)
    {
      while (mat2colit != NULL)
	{
	  mat2rowit = mat2colit;
	  mat1colit = mat1rowit;
	  while (mat2rowit != NULL && mat1colit != NULL)
	    {
	      temp = temp + (mat1colit->val) * (mat2rowit->val);
	      mat2rowit = mat2rowit->down;	//traversing through the nodes to perform the multiolication by passing head nodes of the two matrices
	      mat1colit = mat1colit->right;
	    }
	  fprintf (fpp, "%d ", temp);	//printing the reult of the multiplication 
	  temp = 0;
	  mat2colit = mat2colit->right;
	}
      fprintf (fpp, "\n");
      mat2colit = y2;
      mat1rowit = mat1rowit->down;
    }
}

void
print_mat (node * head)
{
  node *rigp;
  node *dowp = head;
  while (dowp != NULL)
    {
      rigp = dowp;
      while (rigp != NULL)
	{
	  fprintf (stdout, "%d ", rigp->val);	//printing by traversing right and thenn going down
	  rigp = rigp->right;
	}
      fprintf (stdout, "\n");
      dowp = dowp->down;
    }
}				//to print matrix by passing the head node of the matrix 

int
main ()
{
  int m1, n1, m2, n2;
  int a[MAX][MAX];
  int b[MAX][MAX];		//declaring matrices
  int it = 0;
  int u = 0;
  int tep = 0;
  m1 = 0;
  n1 = 0;			//initialising variables to keep a count
  int len = 0;
  char j;
  FILE *in1;
  in1 = fopen ("input1.txt", "r");	//taking input from the file
  char str[1024];
  fgets (str, 1024, in1);
  fclose (in1);
  len = strlen (str);
  while (1)
    {
      if (str[it] != ',' && str[it != ';'])
	{
	  j = str[it];
	  while (1)
	    {
	      u = u * 10;
	      tep = j - '0';
	      u = u + tep;
	      it = it + 1;
	      j = str[it];
	      if (str[it] == ',' || str[it] == ';' || str[it] == 0)	//storing the elements given in file string into a 2d matrix
		{
		  break;
		}
	    }
	  if (it == len)
	    {
	      break;
	    }
	  j = '0';
	  a[m1][n1] = u;
	  u = 0;
	  tep = 0;
	}
      if (it == len)
	{
	  break;
	}
      if (str[it] == ',')
	{
	  n1 = n1 + 1;
	  it = it + 1;
	}
      else if (str[it] == ';')
	{
	  m1 = m1 + 1;
	  if (str[it + 2] != '\0')
	    {
	      n1 = 0;
	    }
	  else
	    {
	      n1 = n1 + 1;
	    }
	  it = it + 1;
	}
    }

  FILE *in2;
  in2 = fopen ("input2.txt", "r");	//input for the 2nd matrix taken from the file
  fgets (str, 1024, in2);	//getting the elements into the string
  fclose (in2);
  len = strlen (str);
  it = 0;
  u = 0;
  tep = 0;
  m2 = 0;			//initialising variables
  n2 = 0;
  while (1)
    {
      if (str[it] != ',' && str[it != ';'])
	{
	  j = str[it];
	  while (1)
	    {
	      u = u * 10;
	      tep = j - '0';
	      u = u + tep;
	      it = it + 1;
	      j = str[it];
	      if (str[it] == ',' || str[it] == ';' || str[it] == 0)
		{
		  break;
		}
	    }			//storing the input given in file 2 into the 2nd matrix
	  if (it == len)
	    {
	      break;
	    }
	  j = '0';
	  b[m2][n2] = u;
	  u = 0;
	  tep = 0;
	}
      if (it == len)
	{
	  break;
	}
      if (str[it] == ',')
	{
	  n2 = n2 + 1;
	  it = it + 1;
	}
      else if (str[it] == ';')
	{
	  m2 = m2 + 1;
	  if (str[it + 2] != '\0')
	    {
	      n2 = 0;
	    }
	  else
	    {
	      n2 = n2 + 1;
	    }
	  it = it + 1;
	}
    }

  FILE *out;
  out = fopen ("output.txt", "w");	//printing file to output
  int f;
  int g;
  node *head1;
  node *head2;
  head1 = construct (a, 0, 0, m1, n1);
  head2 = construct (b, 0, 0, m2, n2);	//constructing the linked list matrices by passing the two 2d matrices and returning their head position
  square (head1, head2, out);
  if (sym1 == 0 && sym2 == 0)
    {
      fprintf (out, "Matrix 1 and Matrix 2 are not symmetrical\n");	//checking the values returned by calling the symmetric function thelinked list matrices and printing
    }
  else if (sym1 == 0)
    {
      f = symmetric (head2);
      fprintf (out, "Matrix 1 is not symmetrical\n");
      if (f == 1)
	{
	  fprintf (out, "Matrix 2 is symmetrical\n");
	}
      else
	{
	  fprintf (out, "Matrix 2 is not symmetrical\n");	//checking the values returned by calling the symmetric function thelinked list matrices and printing
	}
    }
  else if (sym2 == 0)
    {
      f = symmetric (head1);
      fprintf (out, "Matrix 2 is not symmetrical\n");
      if (f == 1)
	{
	  fprintf (out, "Matrix 1 is symmetrical\n");
	}
      else
	{
	  fprintf (out, "Matrix 1 is not symmetrical\n");	//checking the values returned by calling the symmetric function thelinked list matrices and printing
	}
    }
  else if (sym1 == 1 && sym2 == 1)
    {
      f = symmetric (head1);
      g = symmetric (head2);
      if (f == 1)
	{
	  fprintf (out, "Matrix 1 is symmetrical\n");
	}
      else
	{
	  fprintf (out, "Matrix 1 is not symmetrical\n");
	}
      if (g == 1)
	{
	  fprintf (out, "Matrix 2 is symmetrical\n");
	}
      else
	{
	  fprintf (out, "Matrix 2 is not symmetrical\n");	//checking the values returned by calling the symmetric function thelinked list matrices and printing
	}
    }

  if (n1 != m2)
    {
      fprintf (out, "Multiplication not possible\n");	//printing muliplication not possible if columns of matrix1 and rows of matrix2 do not match 
    }
  else if (n1 == m2)
    {
      mul (head1, head2, out);	//calling the multiplication function to print the resultant matrix
    }
}
