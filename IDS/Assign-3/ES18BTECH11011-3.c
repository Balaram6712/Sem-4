#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>

int count = 0;     //count variable
void prnt ();			//defining the print function

struct node
{
  int lo;
  int high;
  int line;
  struct node *link;
};				//defining a structure with low,high indexes and line numbers stored in a stack entry

struct node *top;		// a structure point to the top of the stack

int
isempty ()
{
  if (top == NULL)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}				//function to tell if the stack is empty or not by checking the top pointer value

void
push (int x, int y, int l)
{
  if (isempty ())
    {
      printf ("{ }\n");
    }
  struct node *temp;
  temp = (struct node *) malloc (sizeof (struct node));	//allocating memoey dyanmically and storing the elements into the structure and pushing it into the stack
  temp->lo = x;
  temp->high = y;
  temp->line = l;
  temp->link = top;
  top = temp;
  count = count + 1;		//incrementing the count value to keep tarck of number of elements in the stack
  prnt ();			//printing the elments of the stack after pushing the elements
}

void
pop ()
{
  struct node *tm;
  tm = top;
  top = top->link;		//removing the top element of the stack and changing the position where top points to 
  tm->link = NULL;
  free (tm);
  if (isempty ())
    {
      printf ("{ }\n");
    }
  count = count - 1;		//count decremented to say the content in the stack decreased
  prnt ();			//printing the elements of the stack after popping the top elemnt of the stack 
}

void
prnt ()
{
  struct node *tp;
  tp = top;
  int t = 0;
  t = count;
  while (t > 0)
    {
      printf ("    ");
      t = t - 1;		//depending on the count we print rthe spaces to match the output and tell the depth of the stack and recursion state we are in
      if(t==0)
  {
    printf ("{");
  }
    }
  while (tp != NULL)
    {
      printf ("( %d , %d , %d )", tp->lo, tp->high, tp->line);	//printing the contents at that position
      tp = tp->link;		//tarversing through the list to prin its elements
      if (tp != NULL)
	{
	  printf (" , ");
	}
      else
	{
	  printf ("}\n");
	}

    }
  printf ("\n");
}				//function to print the stack elements

int
partition (int l[], int w, int z)
{
  int pvt;
  pvt = l[z];			//pivot taken as last which is randomly chosen and swapped and kept in that position
  int i;
  i = w - 1;
  int tp;
  int j = 0;
  for (j = w; j < z; j++)
    {
      if (l[j] <= pvt)        //if current element less than pivot element
	{
	  i = i + 1;;
	  tp = l[j];
	  l[j] = l[i];
	  l[i] = tp;		//swapping the elements if condition satisfied
	}
    }
  tp = l[z];
  l[z] = l[i + 1];
  l[i + 1] = tp;		//swapping the pivot element and keeping it in its correct position and returning that index
  return (i + 1);
}

int
part_rand (int s[], int x, int y)
{
  int rd;
  int temp;
  srand(time(0));
  rd = x + (rand () % (y - x));	//randomly choosing a pivot from the array
  temp = s[y];
  s[y] = s[rd];
  s[rd] = temp;			//swapping the chosen pivot with last element to partiton the array
  int in;
  in = partition (s, x, y);	//calling the partition function and returning the index
  return in;
}

void
qucksrt (int w[], int u, int v, int li)
{
  push (u, v, li);		//pushing the corresponding function call into the stack along with line number
  if (u < v)
    {
      int p;
      p = part_rand (w, u, v);	//partitioning the array randomlyt by calling th3 function
      qucksrt (w, u, p - 1, __LINE__);	//calling the quick sort function recursively on left half of the pivot
      qucksrt (w, p + 1, v, __LINE__);	//calling the quick sort function recursively on right half of the pivot
    }
  pop ();			//popping the top of the stack as the function returns to the function it is being called so we need to pop the stack contents
}

int
main ()
{
  int n;
  printf ("Enter the array size to be sorted:");
  scanf ("%d", &n);		//taking size of the array as input
  int a[n];			//declaring array
  printf ("Enter the elements in the array:\n");
  int i;
  for (i = 0; i < n; i++)
    {
      scanf ("%d", &a[i]);	//taking array as input
    }
  qucksrt (a, 0, n - 1, __LINE__);	//calling quicksort function by also passing the macro __LINE__ which passes the current line number
  printf ("The final sorted array is:\n");
  for (i = 0; i < n; i++)
    {
      printf ("%d ", a[i]);	//printing the sorted array 
    }
  printf ("\n");
}
