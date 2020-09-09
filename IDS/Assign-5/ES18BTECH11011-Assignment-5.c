#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX 10000

struct node_eval
{
  float val;
  struct node_eval *next;
};				//node for evaluating the post fix expression
struct node_infi
{
  char ele;
  struct node_infi *next;
};				//node for converting infix to postfix
struct node_paren
{
  char par;
  int num;
  struct node_paren *next;
};				//node for checking parenthesis

struct node_eval *top_post_eval = NULL;
struct node_infi *top_infi = NULL;
struct node_paren *top_paren = NULL;	//3 top structure nodes for the 3 stacks created

void
push_paren (char b, int nu)
{
  struct node_paren *q;
  q = (struct node_paren *) malloc (sizeof (struct node_paren *));	//dynamic allocation of mempry
  q->par = b;
  q->num = nu;
  if (top_paren == NULL)
    {
      top_paren = q;
      top_paren->next = NULL;
    }
  else
    {
      q->next = top_paren;
      top_paren = q;
    }
}				//function for pushing the character for checking the parenthesis

void
pop_paren ()
{
  struct node_paren *g;
  g = top_paren;
  top_paren = top_paren->next;
  g->next = NULL;
  free (g);			//using free to deallocate the memory allocated
}				//function for popping the character for checking the parenthesis

void
push_infi (char p)
{
  struct node_infi *tu;
  tu = (struct node_infi *) malloc (sizeof (struct node_infi));	//dynamic allocation of memory
  tu->ele = p;
  if (top_infi == NULL)
    {
      top_infi = tu;
      top_infi->next = NULL;
    }
  else
    {
      tu->next = top_infi;
      top_infi = tu;
    }
}				//dunction for pushing a character into the infix to post fix evaluation stack

void
pop_infi ()
{
  struct node_infi *tr;
  tr = top_infi;
  top_infi = top_infi->next;
  tr->next = NULL;
  free (tr);			//using free to deallocate the memory allocated
}				//function for popping the element from top for infix to postfix evaluation stack

int
power (int base, int exponent)
{
  int result = 1;
  for (exponent; exponent > 0; exponent--)
    {
      result = result * base;
    }
  return result;
}				//function for evaluation a^b

int
precedence (char c)
{
  if (c == '^')
    {
      return 3;
    }
  else if (c == '*' || c == '/')
    {
      return 2;
    }
  else if (c == '+' || c == '-')
    {
      return 1;
    }
  else
    {
      return -1;
    }
}				//precdence value a operator should be given so that accordingly we perform the operations

void
push_post_eval (float x)
{
  struct node_eval *temp;
  temp = (struct node_eval *) malloc (sizeof (struct node_eval));
  temp->val = x;
  if (top_post_eval == NULL)
    {
      top_post_eval = temp;
      top_post_eval->next = NULL;
    }
  else
    {
      temp->next = top_post_eval;
      top_post_eval = temp;
    }
}				//function for pushing value into postfix evaluation stack

void
pop_post_eval ()
{
  struct node_eval *tp;
  tp = top_post_eval;
  top_post_eval = top_post_eval->next;
  tp->next = NULL;
  free (tp);
}				//function for poping the value in the infix evaluation stack

int
is_valid (int s, char y[])
{
  int h;
  int l = 0;
  for (h = 0; h < s; h++)
    {
      l = 0;
      if (y[h] != '(' && y[h] != '[' && y[h] != '{' && y[h] != ']'
	  && y[h] != '}' && y[h] != ')' && y[h] != '+' && y[h] != '-'
	  && y[h] != '/' && y[h] != '*' && y[h] != '^' && y[h] != '\n')
	{
	  l = l + 1;
	}
      if (y[h] >= 48 && y[h] <= 57)
	{
	  l = l - 1;
	}
      if (l == 1)
	{
	  printf ("The given expression is invalid at %c\n", y[h]);
	  return 0;
	}
    }
  return 1;
}				//a function for checking if the given expressions has correct characters and correct operads or not
void prnt()
{
	struct node_eval *temp;
	temp = top_post_eval;
	while(temp!=NULL)
	{
		printf("%f \n",temp->val);
		temp = temp->next;
	}
	printf("\n");
}
int
main ()
{
  char a[MAX];
  char post[MAX];		//character array for storing the postfix string 
  fgets (a, MAX, stdin);	//taking string input
  int len;			//a string length
  len = strlen (a);
  int i, r;
  int dt = -1;
  if (!is_valid (len, a))	//calling is_valid function to tell if given expression has the valid operators or not 
    {
      return 0;
    }
  for (i = 0; i < len - 1; i++)
    {
      if ((a[i] == '*' || a[i] == '/' || a[i] == '+' || a[i] == '^' || a[i] == '-') && (a[i + 1] == '*' || a[i + 1] == '/' || a[i + 1] == '+' || a[i + 1] == '^' || a[i + 1] == '-'))	//check for side by side operators
	{
	  printf ("Invalid %c , %c operators given as input side by side\n",
		  a[i], a[i + 1]);
	  return 0;
	}			// a for loop such that there are no operator side by side
    }
  int tmp[MAX];
  int it = 1;
  for (i = 0; i < len; i++)
    {
      if (!isdigit (a[i]))
	{
	  tmp[i] = it;
	  it = it + 1;
	}
    }
  for (i = 0; i < len; i++)	//loop for checking the parenthesis balancing
    {
      if (a[i] == '(' || a[i] == '[' || a[i] == '{')
	{
	  push_paren (a[i], tmp[i]);
	  //pushing the characters into parenthesis evaluation stack
	  continue;
	}

      char t;
      int eq;
      switch (a[i])
	{
	case ')':
	  t = top_paren->par;
	  eq = top_paren->num;	//if correspondiing closing bracket found pop it and check it is the matching bracket or not if not return s parethesis is not matching
	  pop_paren ();
	  if (t == '{' || t == '[')
	    {
	      printf
		("Unmatched pranthesis at %c found at symbol number %d\n", t,
		 eq);
	      return 0;
	    }
	  break;
	case '}':
	  t = top_paren->par;
	  eq = top_paren->num;	//if correspondiing closing bracket found pop it and check it is the matching bracket or not if not return s parethesis is not matching
	  pop_paren ();
	  if (t == '[' || t == '(')
	    {
	      printf
		("Unmatched pranthesis at %c found at symbol number %d\n", t,
		 eq);
	      return 0;
	    }
	  break;
	case ']':		//if correspondiing closing bracket found pop it and check it is the matching bracket or not if not return s parethesis is not matching 
	  t = top_paren->par;
	  eq = top_paren->num;
	  pop_paren ();
	  if (t == '{' || t == '(')
	    {
	      printf
		("Unmatched pranthesis at %c found at symbol number %d\n", t,
		 eq);
	      return 0;
	    }
	  break;
	}
    }
  if (top_paren != NULL)	//at the end  if stack is not empty then there are still parenthesis not matched
    {
      printf ("Unmatched parenthesis %c found at symbol number %d\n",
	      top_paren->par, top_paren->num);
      return 0;
    }
  for (i = 0; i < len; i++)
    {
      if (a[i] == '[' || a[i] == '{')
	{
	  a[i] = '(';
	}
      if (a[i] == ']' || a[i] == '}')
	{
	  a[i] = ')';
	}
    }				//converting all the different parenthesis for ease of evaluation of the infix to postfix conversion

  int k = 0;
  char chr;
  char spc;
  spc = ' ';			//character for space
  char w;
  push_infi ('N');		//a dummy character to tell that it is the stack bottom due to some problem with null had to use this
  for (i = 0; i < len; i++)	//keep while as we have to ad space in post array so get correct postt value output
    {
      chr = a[i];
      if (isdigit (a[i]))
	{
	  post[k] = chr;
	  k = k + 1;		//if it is a digit then transfer it into postfix character array
	  if (isdigit (a[i + 1]))	//checking if it is multidigit or not
	    {
	      continue;
	    }
	  else
	    {
	      post[k] = spc;	//adding a space after the digit to get the postfix string for evaluating the postfix expression
	      k = k + 1;
	    }
	}
      else if (a[i] == '(')	//pushing the parenthesis into the stack
	{
	  push_infi ('(');
	}
      else if (a[i] == ')')	//add it to the postfix string as an expression is eclosed with in ( and ) and also add a space
	{
	  while (top_infi->ele != 'N' && top_infi->ele != '(')
	    {
	      w = top_infi->ele;
	      pop_infi ();
	      post[k] = w;
	      k = k + 1;
	      post[k] = spc;
	      k = k + 1;
	    }
	  if (top_infi->ele == '(')
	    {
	      w = top_infi->ele;
	      pop_infi ();
	    }
	}
      else
	{
	  while (top_infi->ele != 'N' && precedence (a[i]) <= precedence (top_infi->ele))	//if an operator is scanned then check for precendence of the scanned one and the operator in the stack and act accordingly
	    {
	      w = top_infi->ele;
	      pop_infi ();
	      post[k] = w;
	      k = k + 1;
	      post[k] = spc;
	      k = k + 1;	//pop all the operators from the stack which are greater than or equal to in precedence than that of the scanned operator,After doing that Push the scanned operator to the stack.
	    }
	  push_infi (a[i]);
	}
    }
  while (top_infi->ele != 'N')	//after scanning completed pishing the remaining into the postfix character array
    {
      w = top_infi->ele;
      pop_infi ();
      post[k] = w;
      k = k + 1;
      if (top_infi->next == NULL)
	{
	  break;
	}			//if final character then no need to add space
      else
	{
	  post[k] = spc;
	  k = k + 1;
	}
    }
  float op1;
  float op2;
  float res;
  dt = -1;
  len = strlen (post);
  printf ("%s", post);		//printing the postfix expression
  for (r = 0; r < len; r++)
    {
      if (isdigit (post[r]))
	{
	  dt = (dt == -1) ? 0 : dt;
	  dt = dt * 10 + post[r] - 48;	//incase of multtidigit add the value to the postfix evaluation stack
	  continue;
	}
      if (dt != -1)
	{
	  push_post_eval (dt);
	}
      if (post[r] == '+' || post[r] == '-' || post[r] == '*' || post[r] == '/'
	  || post[r] == '^')
	{
	  op2 = top_post_eval->val;
	  pop_post_eval ();
	  op1 = top_post_eval->val;
	  pop_post_eval ();
	  	//depending on the operator encountered popping the top values in the stack and performing the necessary operation and pushing again it inot the stack
	  switch (post[r])
	    {
	    case '+':
	      res = op1 + op2;
	      push_post_eval (res);
	      break;
	    case '-':
	      res = op1 - op2;
	      push_post_eval (res);
	      break;
	    case '*':
	      res = op1 * op2;
	      push_post_eval (res);
	      break;
	    case '/':
	      res = (float) op1 / (float) op2;
	      push_post_eval (res);
	      break;
	    case '^':
	      res = power (op1, op2);
	      push_post_eval (res);	//switch case for evaluating the postfix expression and pushing the resulrant value back into the stack
	      break;
	    }
	}
      dt = -1;			//a characcter for pushing the values into the stack correspondingly
    }
  if (top_post_eval->next == NULL && top_post_eval != NULL)
    {
      printf ("Postfix evaluation value of the expression is: %.2f\n", top_post_eval->val);	//printing the final evaluated value
    }
}
