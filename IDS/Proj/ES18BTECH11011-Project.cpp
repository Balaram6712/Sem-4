#include<iostream>
#include<malloc.h>
#include<time.h>
#include<climits>
#include<random>
#define MAX_VERTICES 10000	//max vertices
#define MAX_EDGES 3000		//max edges

using namespace std;

random_device rd;
mt19937 gen (rd ());
uniform_real_distribution <> dis (0, 1);	//random generator usedd to for probability of the vent to occur
int tot_recover;		//get a random number between 0 and 1

struct lst
{
  int v;
  struct lst *link;
};				
//a struct for list

struct lst *susceptible = NULL;
struct lst *infected = NULL;
struct lst *recovered = NULL;	//3 linked lists heads for each are being initialised

void
insert_nodenum (int x, char st)
{
  struct lst *temp;
  temp = (struct lst *) malloc (sizeof (struct lst));
  temp->v = x;			//inserting the node number into the node of the list correspondingly
  if (st == 'S')
    {
      if (susceptible == NULL)
	{
	  susceptible = temp;	//if it is the first node to be inserting so that it can be taken care of
	}
      else
	{
	  struct lst *p;
	  p = susceptible;
	  while (p->link != NULL)
	    {
	      p = p->link;	//traversing until the end and inserting accordingly
	    }
	  p->link = temp;
	}
    }
  else if (st == 'R')
    {
      if (recovered == NULL)
	{
	  recovered = temp;	//inserting into Recovery list 'R' is passed as parameter and inserted accordingly into the list
	}
      else
	{
	  struct lst *p;
	  p = recovered;
	  while (p->link != NULL)
	    {
	      p = p->link;
	    }
	  p->link = temp;
	}
    }
  else if (st == 'I')
    {
      if (infected == NULL)
	{
	  infected = temp;
	}
      else
	{
	  struct lst *p;	//inserting into Recovery list 'I' is passed as parameter and inserted accordingly into the list
	  p = infected;		//passing the head of the infected list to the node and traversing through the list upto NULL and inserting accordingly
	  while (p->link != NULL)
	    {
	      p = p->link;
	    }
	  p->link = temp;
	}
    }
}

void
del_lst (int x, char st)	//a number is given which is node and a character which tells  us which list to delete from
{
  struct lst *p;
  if (st == 'S')
    {
      p = susceptible;
      if (p->v == susceptible->v)	//if the node to be deleted is the first one it will be taken care of with this condition
	{
	  susceptible = susceptible->link;	//deleting the node from the list based on the node number
	  p->link = NULL;
	  free (p);		//freeing the space allocated and deleting the node
	}
      else
	{
	  while (p->link->v != x)
	    {
	      p = p->link;
	    }
	  struct lst *tp;
	  tp = p->link;
	  if (tp->link != NULL)
	    {
	      p->link = tp->link;
	    }
	  else
	    {
	      p->link = NULL;
	    }
	  free (tp);
	}
    }
  else if (st == 'I')		//corresponding character is passed and checked for the node in the list based on the passed parameter and deleted correspondingly from the list
    {
      p = infected;
      if (p->v == infected->v)
	{
	  infected = infected->link;
	  p->link = NULL;
	  free (p);		//freeing the space allocated and deleting the node
	}
      else
	{
	  while (p->link->v != x)
	    {
	      p = p->link;
	    }
	  struct lst *tp;
	  tp = p->link;
	  if (tp->link != NULL)
	    {
	      p->link = tp->link;
	    }
	  else
	    {
	      p->link = NULL;
	    }
	  free (tp);
	}			//a function to delete node from the list correspondingly
    }
}

void
print_lists ()
{
  struct lst *temp;
  temp = susceptible;
  cout << "Susceptible nodes list: ";
  if (temp == NULL)
    {
      cout << "NIL" << endl << endl;	//printing from susceptible list
    }
  else
    {
      while (temp != NULL)
	{
	  cout << temp->v << " ";
	  temp = temp->link;
	}
      cout << endl << endl;
    }

  cout << "Infected nodes list: ";
  temp = infected;
  if (temp == NULL)		//printing from infected list
    {
      cout << "NIL" << endl << endl;
    }
  else
    {
      while (temp != NULL)
	{
	  cout << temp->v << " ";	//a function to print the lists from the 3 lists availabe if any list is empty then NIL is printed
	  temp = temp->link;
	}
      cout << endl << endl;
    }
  cout << "Recovered nodes list: ";
  temp = recovered;
  if (temp == NULL)		//printing from recovered list
    {
      cout << "NIL" << endl << endl;
    }
  else
    {
      while (temp != NULL)
	{
	  cout << temp->v << " ";
	  temp = temp->link;
	}
      cout << endl << endl;
    }
}				//a function to print the lists correspondingly by the parameteers passed and which list to be printed

void
cnt ()
{
  struct lst *tm;
  int c = 0;
  tm = susceptible;
  while (tm != NULL)
    {
      tm = tm->link;
      c++;
    }
  cout << "Susceptible count : " << c;
  tm = infected;
  c = 0;
  while (tm != NULL)		// a function to count the number of nodes in each lists
    {
      tm = tm->link;
      c++;
    }
  cout << "     Infected count : " << c;

  tm = recovered;
  c = 0;
  while (tm != NULL)
    {
      tm = tm->link;
      c++;
    }
  cout << "     Recovered count : " << c << endl;

}

int
coun_rec ()
{
  struct lst *tm;
  tm = infected;
  int c = 0;
  while (tm != NULL)
    {
      tm = tm->link;
      c++;
    }				//a fucntion to check if all the nodes recovered counting the recovered list when the queue is empty
  return c;
}

struct pqueue
{
  int n;			//the number of the node
  int tim;			//the time at which the event will occur
  char action;			//the action to be performed
  struct pqueue *link;
};				//a structure for priority queue

struct pqueue *head = NULL;	//head of the priority queue

pqueue *
mknode (int x, int t, char a)
{
  struct pqueue *d;
  d = (struct pqueue *) malloc (sizeof (struct pqueue));	//allocating the memory accordingly
  d->n = x;
  d->tim = t;
  d->action = a;		//allocating the data into the node of the queue
  d->link = NULL;
  return d;			// a make node function for new nodes
}

void
enqueue (int x, int t, char a)
{				//a function for enqueue the event inot the priority queue
  struct pqueue *w = mknode (x, t, a);
  if (head == NULL)		//if it is the first event then inserting the newly created node at start
    {
      head = w;
      return;
    }
  if (head->tim > w->tim)	//if the new nodes event needs to be performed first then it should be attached at start
    {
      w->link = head;
      head = w;
      return;
    }
  else
    {				//if it is not the first priority it is placed accoringly by traversing and if same priority then the event which is in the queue first is given more priority
      struct pqueue *cur;
      cur = head;
      while (cur->link != NULL && cur->link->tim <= w->tim)
	{
	  cur = cur->link;
	}			//if equal it should be attached after that event
      w->link = cur->link;
      cur->link = w;
      return;
    }
}

pqueue *
dequeue ()
{
  struct pqueue *de;
  de = head;			//a function to dequeue the starting or high priority event at that time in the queue
  head = head->link;
  return de;			//and returning the node accordingly so that action or event can be performed
}

void
print_queue ()
{
  struct pqueue *pr;
  pr = head;
  cout << "Eve: ";
  while (pr != NULL)
    {
      cout << pr->n << " " << pr->action << " " << pr->tim << "|";
      pr = pr->link;
    }
  cout << endl;
}				//a function to print the queue

struct node
{
  int vertex;
  char state;
  int recover_time;
  struct node *next;		//a struct node for the node in the graph
};

struct Graph
{
  int num_vertices;
  struct node **adjlists;
};				//a struct for graph which has the adjacency lists

struct node *
create_node (int x)
{
  struct node *newnode;
  newnode = (struct node *) malloc (sizeof (struct node));	//creating the new node and allocating it memory
  newnode->vertex = x;
  newnode->next = NULL;
  newnode->state = 'S';		//initially its state is susceptible
  newnode->recover_time = 0;
  return newnode;
}				//function to create a new vertex

struct Graph *
create_graph (int vertices)
{
  struct Graph *graph;		//allocating memory dynamically for creating the graph
  graph = (struct Graph *) malloc (sizeof (struct Graph));
  graph->num_vertices = vertices;
  graph->adjlists =
    (struct node **) malloc (vertices * sizeof (struct node *));
  int i;
  for (i = 0; i < vertices; i++)
    {
      graph->adjlists[i] = (struct node *) malloc (sizeof (struct node));
      graph->adjlists[i]->vertex = i;
      graph->adjlists[i]->state = 'S';
      graph->adjlists[i]->recover_time = 0;	//initialising all the adjacency lists
      graph->adjlists[i]->next = NULL;
    }
  return graph;
}

void
add_edge (struct Graph *graph, int src, int dest)
{
  struct node *temp;
  temp = graph->adjlists[src];
  while (temp->next != NULL)
    {
      temp = temp->next;
    }
  temp->next = create_node (dest);

  temp = graph->adjlists[dest];
  while (temp->next != NULL)
    {
      temp = temp->next;	//a function to add the edge in graph as it is undirected we should add the edge to both the adjacency lists of source and destination
    }
  temp = create_node (src);
}

void
print_graph (struct Graph *graph)
{
  int n = graph->num_vertices;
  int i;
  struct node *t;
  for (i = 0; i < n; i++)
    {
      cout << i << "->";
      t = graph->adjlists[i];
      t = t->next;
      cout << "{";
      while (t != NULL)
	{
	  cout << t->vertex << " ";
	  t = t->next;
	}
      cout << "}";
      cout << endl;
    }
}				//a functtion to print the graphs through adjacency lists


void
process_trans_SIR (struct Graph *graph, int u, double trans, double recover,
		   int times, int timemax)
{
  graph->adjlists[u]->state = 'I';	//as the event is transfer we remove the node susceptible list and add it to infected and changing the state to infected in the node
  del_lst (u, 'S');
  insert_nodenum (u, 'I');
  int t;
  t = times;
  while (1)
    {
      if (dis (gen) < recover)
	{
	  break;
	}
      else
	{
	  t++;
	}
    }				//as the node is infected we need to find how many days the node will be recovered, will be the number of times we toss a coin until we get a heads 
  if (t + 1 < timemax)
    {
      enqueue (u, t + 1, 'R');	//enqueue the recovery event with the day when the node will recover in to the queue
    }
  //an event to tell when the infected node should recover
  struct node *tt;
  tt = graph->adjlists[u];
  tt = tt->next;
  while (tt != NULL)
    {
      if (tt->state != 'I' && tt->state != 'R')	//if already infected or recovered we need not add them or check them
	{
	  t = times;
	  double test;
	  while (1)
	    {
	      if (dis (gen) < trans)
		{
		  break;
		}
	      else
		{
		  t++;
		}
	    }			//checking for the neighbours of the infected node will it spread or not by checking with trnasmission probbility if it transmits add the event to the queue correspondingly
	  if (t + 1 < timemax)
	    {
	      enqueue (tt->vertex, t + 1, 'T');
	    }
	  //running a loop until we get head or the disease transmitted to neighbour
	}
      tt = tt->next;
    }				//a function if the event is transfer
}

void
process_rec_SIR (struct Graph *graph, int u)
{
  struct node *v;
  v = graph->adjlists[u];
  v->state = 'R';
  del_lst (u, 'I');		//if the event is recovery we call the function and change the node state to recovered
  insert_nodenum (u, 'R');	//deleting the node from the list of infected and inserting it into recovered list
}

void
fast_SIR (struct Graph *graph, double trans, double recover, int initial,
	  int timemax)
{
  int local_times = 0;
  int i;
  enqueue (initial, local_times, 'T');
  for (local_times = 1; local_times <= timemax; local_times++)	//initial infected node being added to the 
    {
      while (head != NULL)	//conduct the events only on thatday and not the rest of the events in next iteration we can condunct the events on the next day  
	{
	  if (head->tim > local_times)
	    {
	      break;
	    }
	  struct pqueue *eve;	//dequeue the first or top node
	  eve = dequeue ();
	  if (eve->action == 'T')
	    {
	      if (graph->adjlists[eve->n]->state == 'S')	//checking the state and event to be performed of the node and calling the respective function
		{
		  process_trans_SIR (graph, eve->n, trans, recover,
				     local_times, timemax);
		}
	    }
	  else if (eve->action == 'R')
	    {
	      process_rec_SIR (graph, eve->n);
	    }
	}
      cout << "Day  " << local_times << ": ";
      cnt ();			//count of the nodes in every list
    if(head==NULL)
    {
      if(coun_rec()==0)
      {
        tot_recover = local_times;
        break;                          //if no more events in the queue and no more nodes infected then we can end the simulation
      }
    }
  }
}
int
main ()
{
  int vertices, edges, src, dest;
  vertices = MAX_VERTICES;
  struct Graph *graph = create_graph (vertices);	//creating a graph with MAX_VERTICES
  int count = 0;		//the nodes count from 0 to 9999 number
  int i;
  srand (time (0));
  for (i = 0; i < MAX_VERTICES; i++)
    {
     // src = rand () % (10000);
      count = 0;
      for(count=0;count<5;count++)
      {
        dest = rand () % (10000);
        while(i==dest)
        {           //if src and dest equal we generate another number
          dest = rand () % (10000);
        }
        add_edge (graph, i, dest);  
      }
      	//generating a random graph
    }   //3 edges per node
  for (i = 0; i < MAX_VERTICES; i++)
    {
      insert_nodenum (i, 'S');	//inserting all the nodes into the susceptible list
    }
  int tmax = 300;		//nax days of simulation
  double tow = 0.5;		//transmission rate
  double gamma = 0.2;		//recovery rate if infected
  int initial;
  initial = rand () % (10000);	//getting a random node infected and passing it to the simulation function
  fast_SIR (graph, tow, gamma, initial, tmax);	//The simulation starts from Day 0 to Day 299 and 300 day simulation
  if(tot_recover<300&&tot_recover!=0)
  {
    cout << "Total days of recovery: " << tot_recover <<  endl;  
    cout << "Simulation has ended as no further people got infected" << endl;
  }           //if the people getting infected is 0 after somedays and less than 300 days then we stop the simulation as no one can further be infected
  else
  {
   cout << "Total days of recovery: 300"  <<  endl; //if 300 days has been completed
   cout << "Simulation has ended 300 days has been completed" << endl;
  }
  
}
