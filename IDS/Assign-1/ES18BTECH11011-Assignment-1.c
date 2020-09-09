#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

int coun = 0;			//count on number of DNA molecules
struct nodealpha
{
  char nuc;
  struct nodealpha *rightlink;
  struct nodealpha *downlink;

};				//defining a node for alpha DNA molecules

struct nodebeta
{
  char nuc;
  struct nodebeta *rightlink;
  struct nodebeta *uplink;
};				//defining a node for beta DNA molecules

struct nodealpha *rootalpha[10000] = { NULL };
struct nodebeta *rootbeta[10000] = { NULL };	//creating root nodes for alpha and beta nodes to store the starting addresses for different chains for a corresponding DNA molecules

int length (int dna_molecule);

void
insert_new (char nucleot)
{
  struct nodealpha *t1;
  struct nodebeta *t2;
  t1 = (struct nodealpha *) malloc (sizeof (struct nodealpha));
  t2 = (struct nodebeta *) malloc (sizeof (struct nodebeta));	//allocating memory dynamically
//      t1->downlink = t2;
//      t2->uplink = t1;
  t1->rightlink = NULL;
  t2->rightlink = NULL;
  if (nucleot == 'A')
    {
      t1->nuc = 'A';		//assigning corresponding nucloetide to the nodes complementing the alpha and beta chains
      t2->nuc = 'T';
    }
  else if (nucleot == 'T')
    {
      t1->nuc = 'T';
      t2->nuc = 'A';
    }
  else if (nucleot == 'G')
    {
      t1->nuc = 'G';
      t2->nuc = 'C';
    }
  else if (nucleot == 'C')
    {
      t1->nuc = 'C';
      t2->nuc = 'G';
    }
  if (rootalpha[coun] == NULL && rootbeta[coun] == NULL)
    {
      rootalpha[coun] = t1;
      rootbeta[coun] = t2;	//if the root nodes are null storing the addresses of the first nodes into the pointer root nodes
      //      rootalpha->downlink = t2;
      //      rootbeta->uplink = t1;
    }
  else
    {
      struct nodealpha *p1;
      struct nodebeta *p2;	//temporary nodes for traversal and inserting the initial sequence of nodes
      p1 = rootalpha[coun];
      p2 = rootbeta[coun];
      while (p1->rightlink != NULL)
	{
	  p1 = p1->rightlink;
	  p2 = p2->rightlink;
	  //              p1->downlink = p2;
	  //              p2->uplink = p1;
	}
      p1->rightlink = t1;
      p2->rightlink = t2;
    }
}				//function for creating initial DNA sequence of nodes

void
insert_existing (int dna_molecule, char nucleotide, int position)
{
  struct nodealpha *temp1;
  struct nodebeta *temp2;	//temporary nodes for traversal and pointing to the start of the root node
  temp1 = rootalpha[dna_molecule];
  temp2 = rootbeta[dna_molecule];
  int j = 1;
  if (temp1 == NULL)
    {
      printf ("The DNA molecule is not yet created\n");	//if there are no items in the list them print empty
    }
  if (position > length (dna_molecule))
    {
      printf ("CAUTION: There is no such location in the DNA molecule\n");	//if given position greater then the length of the corresponding DNA molecule
    }
  else
    {
      struct nodealpha *n1;
      struct nodebeta *n2;	//nodes for storing inserting the nucleotide into the list
      n1 = (struct nodealpha *) malloc (sizeof (struct nodealpha));
      n2 = (struct nodebeta *) malloc (sizeof (struct nodebeta));	//dynamically allocating space for the nodes
      if (nucleotide == 'A')
	{
	  n1->nuc = 'A';
	  n2->nuc = 'T';
	}
      else if (nucleotide == 'T')
	{
	  n1->nuc = 'T';
	  n2->nuc = 'A';
	}
      else if (nucleotide == 'G')
	{
	  n1->nuc = 'G';
	  n2->nuc = 'C';
	}
      else if (nucleotide == 'C')
	{
	  n1->nuc = 'C';
	  n2->nuc = 'G';	//assigning the correspnding nucleotides into the nodes
	}
      n1->rightlink = NULL;
      n2->rightlink = NULL;
//              n1->downlink = n2;
//              n2->uplink = n1;
      while (j < position)
	{
	  temp1 = temp1->rightlink;
	  temp2 = temp2->rightlink;
	  j = j + 1;		//travering until the point where we want to insert the node 
	}
      n1->rightlink = temp1->rightlink;	//updating the pointers and inserting the nodes in between 
      n2->rightlink = temp2->rightlink;	//here the insert happens such that the node will be inserted next to the posiion number given
      temp1->rightlink = n1;
      temp2->rightlink = n2;
    }

}				//function for inserting a nucleotide into existing 

void
del (int dna_molecule, int pos)
{
  struct nodealpha *d1;
  struct nodebeta *d2;		//nodes for pointing to the root nodes of the DNA molecule
  d1 = rootalpha[dna_molecule];
  d2 = rootbeta[dna_molecule];
//      d1->downlink = d2;
//      d2->uplink = d1;
  if (d1 == NULL)
    {
      printf ("The DNA molecule is not yet created\n");	//if the node is NULL then there are no elements in the DNA molecule
    }
  if (pos > length (dna_molecule))
    {
      printf ("Error: There is no such location in the DNA molecule\n");	//if the delete position given greater than length then we print invalid location
    }
  else
    {
      if (pos == 1)
	{
	  d1->rightlink = NULL;
	  d2->rightlink = NULL;
	  free (d1);
	  free (d2);		//if only one element in the DNA molecule then delete that node and free the node using free()
	}
      else
	{
	  int k = 1;		//integer for iteration to keep count until where we go in the list
	  struct nodealpha *up1;
	  struct nodealpha *up2;
	  struct nodebeta *dow1;
	  struct nodebeta *dow2;	//temporry nodes created for addresses updation while deleting a node
	  up1 = d1;
	  dow1 = d2;
	  while (k < pos - 1)
	    {
	      up1 = up1->rightlink;
	      dow1 = dow1->rightlink;
	      k = k + 1;	//we need to iterate until position -1 and update the addresses in the node we want to delete in the current node we are present
	    }
	  up2 = up1->rightlink;
	  dow2 = dow1->rightlink;
	  up1->rightlink = up2->rightlink;
	  dow1->rightlink = dow2->rightlink;
	  up2->rightlink = NULL;
	  dow2->rightlink = NULL;	//deleeting the node by making the addresses NULL and using free() function of that node
	  //      up2->downlink = NULL;
	  //      dow2->uplink = NULL;
	  free (up2);
	  free (dow2);
	}
    }
}				//function to delete a correspnding element from a DNA molecule from a particular position 

void
split (int dna_molecule)
{
  struct nodealpha *sp1;
  struct nodebeta *sp2;
  sp1 = rootalpha[dna_molecule];
  sp2 = rootbeta[dna_molecule];
  int len = length (dna_molecule);
  struct nodebeta *insb[len];	//inserting for upper dna chain
  struct nodealpha *insa[len];	//inserting for lower dna chain
  int u = 0;
  for (u = 0; u < len; u++)
    {
      insb[u] = (struct nodebeta *) malloc (sizeof (struct nodebeta));	//dynamically allocating memory to the nodes created to insert the new lists
      insa[u] = (struct nodealpha *) malloc (sizeof (struct nodealpha));
    }
  u = 0;
  coun = coun + 1;
  rootalpha[coun] = insa[u];	//incrementing coun variable and updating the starting addresses of the new list in the rootnodes arrays
  rootbeta[coun] = insb[u];
  while (sp1->rightlink != NULL)
    {
      if (sp1->nuc == 'A')
	{
	  insa[u]->nuc = 'A';	//2nd DNA alpha
	  insb[u]->nuc = 'T';
	}
      else if (sp1->nuc == 'T')
	{
	  insa[u]->nuc = 'T';
	  insb[u]->nuc = 'A';
	}
      else if (sp1->nuc == 'G')
	{
	  insa[u]->nuc = 'G';
	  insb[u]->nuc = 'C';
	}
      else if (sp1->nuc == 'C')
	{
	  insa[u]->nuc = 'C';
	  insb[u]->nuc = 'G';	//assigning corresponding nucleotide into the new list nodes created
	}
//              sp1->downlink = insb[u];
//              insb[u]->uplink = sp1;
//              sp2->uplink = insa[u];
//              insa[u]->downlink = sp2;
      sp1 = sp1->rightlink;
      sp2 = sp2->rightlink;	//traversing in a while loop though the lists
      insa[u]->rightlink = NULL;
      insb[u]->rightlink = NULL;
      insa[u]->rightlink = insa[u + 1];
      insb[u]->rightlink = insb[u + 1];
      u = u + 1;
    }

  if (sp1->nuc == 'A')
    {
      insa[u]->nuc = 'A';	//2nd DNA alpha
      insb[u]->nuc = 'T';
    }
  else if (sp1->nuc == 'T')
    {
      insa[u]->nuc = 'T';
      insb[u]->nuc = 'A';
    }
  else if (sp1->nuc == 'G')
    {
      insa[u]->nuc = 'G';
      insb[u]->nuc = 'C';
    }
  else if (sp1->nuc == 'C')
    {
      insa[u]->nuc = 'C';
      insb[u]->nuc = 'G';	//assigning the last node the nucleotide into it the while does not update the nucleotide for last node as it observes the right link is NULL so we update it here outside the while
    }
}				//split function to split the DNA molecules which gives ideal DNA molecules

void
print_dna (int dna_molecule)
{
  struct nodealpha *up;
  struct nodebeta *down;	//nodes that point to the root nodes of the particular dna molecule
  up = rootalpha[dna_molecule];
  down = rootbeta[dna_molecule];
//      up->downlink = down;
  int w = 0;
  if (up == NULL)
    {
      printf ("Error: The DNA molecule does not exist\n");
    }
  else
    {
      while (up->rightlink != NULL)
	{
	  printf ("%c --- ", up->nuc);
	  up = up->rightlink;
	}			//printing the alpha chain
      printf ("%c\n", up->nuc);
      while (w < length (dna_molecule))
	{
	  printf ("|     ");
	  w = w + 1;
	}
      printf (" \n");
      while (down->rightlink != NULL)
	{
	  printf ("%c --- ", down->nuc);
	  down = down->rightlink;	//printing the beta chain
	}
      printf ("%c\n", down->nuc);
    }

}				//function to print a particulaer DNA molecule 

void
print_all ()
{
  struct nodealpha *r1;
  struct nodebeta *r2;		//temporary nodes to point to root and traverse throught the lists to print the nodes 
  int e = 0;
  int f = 0;
  while (e < coun + 1)		//while to print all the DNA molecules order by order
    {
      r1 = rootalpha[e];
      r2 = rootbeta[e];
//              r2 = r1->downlink;
      while (r1->rightlink != NULL)
	{
	  printf ("%c --- ", r1->nuc);
	  r1 = r1->rightlink;	//printing the alpha molecules
	}
      printf ("%c\n", r1->nuc);
      while (f < length (e))
	{
	  printf ("|     ");
	  f = f + 1;
	}
      printf (" \n");
      while (r2->rightlink != NULL)
	{
	  printf ("%c --- ", r2->nuc);
	  r2 = r2->rightlink;
	}			//printing beta molecules
      printf ("%c\n", r2->nuc);
      e = e + 1;		//incrementing the count to go to next DNA molecule
      f = 0;
      printf ("\n");
    }
}				//function to print all the DNA molecules

int
length (int dna_molecule)
{
  struct nodealpha *le;
  le = rootalpha[dna_molecule];
  int c = 0;
  if (le == NULL)
    {
      printf ("Error: The DNA molecule does not exist\n");	//if a DNA molecule length is zero then or nor DNA exists then print no DNA molecule exists
    }
  else
    {
      while (le != NULL)
	{
	  c = c + 1;
	  le = le->rightlink;	//traversing through list to find the lost of the molecule 
	}
    }
  return c;
}				//function for finding length of a DNA molecule so that if invalid position given in delete to check the error in it.

int
main ()
{
  int n;
  printf
    ("Enter the number of nucleotide molecules in the initial DNA sequence\n");
  scanf ("%d", &n);
  char nuc[n];
  char dum[n];
  printf ("Enter the nucleotide molecules in order\n");
  int i = 0;
  for (i = 0; i < n; i++)
    {
      scanf ("%c %c", &dum[i], &nuc[i]);	//dummy variable due to problem in while using scanf for characters
    }
  printf ("CAUTION: The DNA molecule numbering starts from 0\n");
  printf
    ("CAUTION: When you inset in a particular position element is inserted next to the position you want to insert in the DNA molecule\n");
  printf
    ("CAUTION: Split only spits the DNA molecule you want to split not all the DNA molecules\n");
  printf
    ("CAUTION: Enter valid input accordingly asked by the print statements\n");
  for (i = 0; i < n; i++)
    {
      insert_new (nuc[i]);	//calling the new molecule insert function intially
    }
  int operation;
  while (1)
    {
      printf ("\n");
      printf ("Enter the operation to be performed from below list:\n");
      printf ("1.Insert nucleotide\n");
      printf ("2.Delete a nucleotide\n");
      printf ("3.Split a DNA molecule\n");
      printf ("4.Print a DNA chain\n");
      printf ("5.Print all the DNA chains\n");
      printf ("6.Exit from the program\n");
      printf ("Enter the operation number:");	//a display menu to choose which operation to perform
      scanf ("%d", &operation);
      int dnaid;		//molecule id
      int position;		//which position to insert
      char nucleotide;		//A/G/T/C
      char dum;			//only single link has been used as two different types of nodes while assigning the links the from one type to another type node.With similar node can be implemented but distinction needs to be there in the node so I implemented in this way
      if (operation == 1)
	{
	  printf
	    ("Enter the DNA molecule number in which you want to insert\n");

	  scanf ("%d", &dnaid);
	  printf ("Enter the nucleotide you want to insert\n");

	  scanf ("%c %c", &dum, &nucleotide);	//dummy variable due to problem in while using scanf for characters
	  printf
	    ("Enter the position in which you want to insert the nucleotide\n");

	  scanf ("%d", &position);
	  insert_existing (dnaid, nucleotide, position);	//calling function to insert into the list
	}
      else if (operation == 2)
	{
	  printf
	    ("Enter the DNA molecule number from which you want to delete a nucleotide\n");

	  scanf ("%d", &dnaid);
	  printf
	    ("Enter the position from which you want to delete a nucleotide\n");

	  scanf ("%d", &position);
	  del (dnaid, position);	//delete function called to delete a nucleotide in a DNA molecule
	}
      else if (operation == 3)
	{
	  printf ("Enter the DNA molecule number which you want to split\n");

	  scanf ("%d", &dnaid);
	  split (dnaid);	//split functfion called on a DNA molecule
	}
      else if (operation == 4)
	{
	  printf ("Enter the DNA molecule number which you want to print\n");
	  scanf ("%d", &dnaid);
	  print_dna (dnaid);	//printf function for a particular DNA called
	}
      else if (operation == 5)
	{
	  print_all ();		//printing all the dna molecules
	}
      else if (operation == 6)
	{
	  break;		// to exit from the opeartions menu and end the program
	}
    }
}
