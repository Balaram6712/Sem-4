#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>
#include<unistd.h>

int count = 0;

struct node
{
  int id;
  int time;
  int quantum;
  struct node *link;
};				//creating a node to enter the element into the queue

struct node *head = NULL;	//pointer nodes the head an tail for the queue
struct node *tail = NULL;

int isempty ();
void prnt ();			//defining the functions for later use

void
enqueue (int id, int t)		//enqueue the node into the queue with id and time which is randomly generated
{
  struct node *temp;
  temp = (struct node *) malloc (sizeof (struct node));	//dynamically alloationg memory
  temp->id = id;
  temp->time = t;		//assigning the values into the node
  if (t > 50)
    {
      temp->quantum = 50;
    }
  else
    {
      temp->quantum = t;	//giving the job the required time quantum it should get 
    }

  if (isempty ())
    {
      head = temp;
      tail = temp;		//initial enqueue
    }
  else
    {
      tail->link = temp;
      tail = temp;		//adding the jobs at the end
    }
  count = count + 1;		//incrementing the count
}

void
dequeue ()			//dequeue function
{
  struct node *tp;
  if (isempty ())		//uf queue is empty we return
    {
      return;
    }
  tp = head;
  head = head->link;		//changing the head position
  if (head == NULL)		//if head is NULL then the queue is empty and making the tail also NULL
    {
      tail = NULL;
    }
  free (tp);			//freeing the node
  count = count - 1;
}

void
prnt ()				//function to display the queue
{
  struct node *tm;
  tm = head;
  int f = 0;
  while (tm != NULL)
    {
      printf ("J%d:%d; ", tm->id, tm->time);	//printing the ;ement in the queue by traversing
      f = f + 1;
      tm = tm->link;
      if (f == count)
	{
	  break;
	}
    }
  printf ("\n");
}

int
isempty ()
{
  if ((head == NULL) && (tail == NULL))	//function to check if queue is empty or not
    {
      return 1;			//returning 1 if empty telling that queue is empty
    }
  else
    {
      return 0;
    }
}

int
main ()
{
  int i = 1;
  int t;
  int total_time = 0;
  srand (time (0));
  while (1)
    {
      t = rand () % 301;	//enquue the initial 100 jobs into the queue with id's and random time 
      enqueue (i, t);
      i = i + 1;
      if (i > 100)
	{
	  break;
	}
    }
  int new = 64;
  int n = 101;
  int lo = 1;
  int lt;
  printf ("Created 100 jobs:\n");
  printf ("Initial Queue:   ");
  prnt ();
  printf ("\n");
  struct node *tu;
  int local = 50;		//local is a variable used to print the queue every 50us
  while (1)
    {
      if (head->time < 50)
	{
	  if (local < head->quantum)
	    {
	      head->time = head->time - local;
	      total_time = total_time + local;	//mathematical operations on the queue so that print the queue every 50 us and consume the corresponding time quatum to the job according to the output required
	      head->quantum = head->quantum - local;
	    }
	  else
	    {
	      local = local - head->quantum;
	      total_time = total_time + head->quantum;
	      head->time = head->time - head->quantum;
        head->quantum = head->quantum - (50 - local);
	    }

	}
      else if (head->time >= 50)	//if local is 50 and job time greater we perform the following operations
	{
	  if (local == 50)
	    {
	      local = local - head->quantum;
	      total_time = total_time + head->quantum;
	      head->time = head->time - head->quantum;
	      head->quantum = 0;
	    }
	  else
	    {
        total_time = total_time + local;
        if(head->quantum > local)
        {
            head->quantum = head->quantum - local;
            head->time = head->time - local;  //mathematical operations performed to get the required output          
        }
        else
        {
          head->quantum = head->quantum - local;
          head->time = head->time - head->quantum;
        }

	    }

	}

      if (head->time <= 0)
	{
	  dequeue ();		//if the process completed its full time then dequeue it from the queue
	}
      else if (head->quantum <= 0)	//if the process completed its time quantum then place it at last accordingly
	{
	  if (head->time < 50)
	    {
	      head->quantum = head->time;
	    }
	  else
	    {
	      head->quantum = 50;
	    }

	  tail->link = head;
	  tail = head;		//placing the current node at last and moving the head position
	  head = head->link;
	  tail->link = NULL;
	}
      if (head == NULL && total_time > 1400)
	{
	  printf ("Queue at the end of %d us:  EMPTY\n", total_time);	//if head is null suggesting the queue is empty and printing it and also checking the time > 1400 beacuse last job gets added at 1400 
	  break;
	}

      if (total_time % 50 == 0)
	{
	  local = 50;		//printing at every 50us total time of the scheduler
	  if (head == NULL)
	    {
	      printf ("Queue at the end of %d us:  EMPTY\n", total_time);
	      break;
	    }
	  else
	    {
	      printf ("Queue at the end of %d us:  ", total_time);	//printing the time and the queue
	      prnt ();
	      printf ("\n");
	    }
	}

      if (total_time % 200 == 0 && total_time <= 1400)
	{
	  for (lo = 1; lo <= new; lo++)	//enqueue the jobs correspongly by corresponding time 
	    {
	      lt = rand () % 301;
	      enqueue (n, lt);
	      n = n + 1;
	    }
	  printf ("******%dus passed, added %d new jobs to end\n", total_time, new);	//printing the number of jobs added to the queue at that corresponding time
	  new = new / 2;
	}
    }
}
