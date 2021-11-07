#include<stdio.h>
#include<stdlib.h>
#define INFINITY 9999
#define MAX 10
struct node
{
int vertex;
int cost;	//the node will also store the cost between the source and the vertex.
struct node *left,*right;
};

struct Graph
{
int numVertices;
struct node **adjLists;
};

 
void dijkstra(struct Graph *graph,int n,int startnode);

struct Graph* create_graph(int); 

void addEdge(struct Graph* graph, int src,int dest, int cost);

void train_time();

void dijkstra_for_train_time(struct Graph* graph,int n,int startnode);

void dijkstra_for_machine_cost(struct Graph* graph,int n,int startnode);

void machine_cost();

struct Graph* create_graph(int vertices)
{
struct Graph *graph = (struct Graph*)malloc(sizeof(struct Graph));
graph -> numVertices = vertices;
graph -> adjLists = malloc(sizeof(struct node *) * vertices);
int i;
for(i=0;i<vertices;i++)
graph -> adjLists[i]= NULL;

return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int cost)
{

//Add edge from source to destination
struct node *newnode = (struct node*)malloc(sizeof(struct node));
newnode -> left = NULL;//we are using doubly linked lists in the adjacency list.
newnode -> right = NULL;
newnode -> vertex = dest;
newnode -> cost = cost;

newnode->right = graph->adjLists[src];
newnode->left = NULL;
if(graph->adjLists[src]!=NULL)
graph->adjLists[src]->left = newnode;
graph->adjLists[src] = newnode;

//Add edge from destination to source
struct node *newnode1 = (struct node*)malloc(sizeof(struct node));
newnode1 -> left = NULL;
newnode1 -> right = NULL;
newnode1 -> vertex = src;
newnode1 -> cost = cost;

newnode1->right = graph->adjLists[dest];
newnode1->left = NULL;
if(graph->adjLists[dest]!=NULL)
graph->adjLists[dest]->left = newnode1;
graph->adjLists[dest] = newnode1;

} 






 

void main()
{
int x;
	printf("Enter \n1 for Single source shortest path algorithm. \n2 to find the fastest route of the train\n3 to find the minimum cost of manufacturing a product\n");
	scanf("%d",&x); 
	switch(x)
	{
	case 1:
	{
	int i,j,n,u,cost;
	printf("Enter no. of vertices:");
	scanf("%d",&n);
	struct Graph* graph = create_graph(n);
	printf("\nEnter the adjacency list:\n");
	
	while(1)
	{
	printf("Enter the source and the destination destination vertex, enter 0 0 to break\n");
	scanf("%d %d", &i,&j);
	if(i == 0 && j==0)
	{
	printf("You have completed giving the inputs to the graph\n");
	break;
	}
	printf("enter the cost between the two vertices\n");
	scanf("%d",&cost);
	addEdge(graph,i,j,cost);
	}
	
	printf("\nEnter the starting node:");
	scanf("%d",&u);
	dijkstra(graph,n,u);
	}
	break;
	case 2:train_time();
	break;
	case 3:machine_cost();
	break;
	default: printf("invalid choice");
	}
	
}
 
void dijkstra(struct Graph* graph,int n,int startnode)
{
 
	int cost[MAX][MAX],distance[MAX],pred[MAX];
	int visited[MAX],count,mindistance,nextnode,i,j;
	
	//pred[] stores the predecessor of each node
	//count gives the number of nodes seen so far
	//create the cost matrix
	
	// Even though the graph is stored in the form of an adjacency list, I will be using a matrix to store the cost.
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			cost[i][j] = 0;	


	struct node *p;
	for(i=0;i<n;i++)
	{
	p = graph->adjLists[i];
	while(p!=NULL)
	{
	cost[i][p->vertex] = p->cost;
	p=p->right;
	}
	}

	for(i=0;i<n;i++)
	{
	for(j=0;j<n;j++)
	{
	if(cost[i][j]==0)
	cost[i][j] = INFINITY;
	}
	}

	//initialize pred[],distance[] and visited[]
	for(i=0;i<n;i++)
	{
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}
	
	distance[startnode]=0;
	visited[startnode]=1;
	count=1;
	
	while(count<n-1)
	{
		mindistance=INFINITY;
		
		//nextnode gives the node at minimum distance
		for(i=0;i<n;i++)
			if(distance[i]<mindistance&&!visited[i])
			{
				mindistance=distance[i];
				nextnode=i;
			}
			
			//check if a better path exists through nextnode			
			visited[nextnode]=1;
			for(i=0;i<n;i++)
				if(!visited[i])
					if(mindistance+cost[nextnode][i]<distance[i])
					{
						distance[i]=mindistance+cost[nextnode][i];
						pred[i]=nextnode;
					}
		count++;
	}
 
	//print the path and distance of each node
	for(i=0;i<n;i++)
		if(i!=startnode)
		{
			printf("\nDistance of node %d=%d",i,distance[i]);
			printf("\nPath=%d",i);
			
			j=i;
			do
			{
				j=pred[j];
				printf("<-%d",j);
			}while(j!=startnode);
		}
printf("\n");
}



























void train_time()
{

//order of the 2d matrix is Delhi, Mysuru and Bengaluru


struct Graph *graph = (struct Graph*)malloc(sizeof(struct Graph));
graph -> numVertices = 3;
graph -> adjLists = malloc(sizeof(struct node *) * 3);
int i,s,s1;
for(i=0;i<3;i++)
graph -> adjLists[i]= NULL;



addEdge(graph,0,1,40);// even though there is a train from Delhi to Mysuru which takes 40 hours to reach, the algorithm suggests you to board a train from Delhi to Bengaluru and then another train from Bengaluru to Mysuru, because this takes only 36 hours. i.e 0 to 2 and 2 to 1 instead of 0 to 1.
addEdge(graph,0,2,33);
addEdge(graph,1,2,3);

printf("Enter the number for the city you want to start from\n");
printf("1. Delhi	2. Mysuru	3.Bengaluru\n");
scanf("%d",&s1);
s=s1-1;
dijkstra_for_train_time(graph,3,s);

}






void dijkstra_for_train_time(struct Graph* graph,int n,int startnode)
{
 
	int cost[MAX][MAX],distance[MAX],pred[MAX];
	int visited[MAX],count,mindistance,nextnode,i,j;
	
	//pred[] stores the predecessor of each node
	//count gives the number of nodes seen so far
	//create the cost matrix
	
	// Even though the graph is stored in the form of an adjacency list, I will be using a matrix to store the cost.
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			cost[i][j] = 0;	


	struct node *p;
	for(i=0;i<n;i++)
	{
	p = graph->adjLists[i];
	while(p!=NULL)
	{
	cost[i][p->vertex] = p->cost;
	p=p->right;
	}
	}

	for(i=0;i<n;i++)
	{
	for(j=0;j<n;j++)
	{
	if(cost[i][j]==0)
	cost[i][j] = INFINITY;
	}
	}

	//initialize pred[],distance[] and visited[]
	for(i=0;i<n;i++)
	{
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}
	
	distance[startnode]=0;
	visited[startnode]=1;
	count=1;
	
	while(count<n-1)
	{
		mindistance=INFINITY;
		
		//nextnode gives the node at minimum distance
		for(i=0;i<n;i++)
			if(distance[i]<mindistance&&!visited[i])
			{
				mindistance=distance[i];
				nextnode=i;
			}
			
			//check if a better path exists through nextnode			
			visited[nextnode]=1;
			for(i=0;i<n;i++)
				if(!visited[i])
					if(mindistance+cost[nextnode][i]<distance[i])
					{
						distance[i]=mindistance+cost[nextnode][i];
						pred[i]=nextnode;
					}
		count++;
	}
 
	//print the path and distance of each node
for(i=0;i<n;i++)
if(i!=startnode)
{
if(i==0)
printf("\nShortest time for Delhi=%d hours",distance[i]);
if(i==1)
printf("\nShortest time for Mysuru=%d hours",distance[i]);
if(i==2)
printf("\nShortest time for Bengaluru=%d hours",distance[i]);

if(i==0)
printf("\nPath= Delhi");
if(i==1)
printf("\nPath= Mysuru");
if(i==2)
printf("\nPath= Bengaluru");
			
j=i;
do
{
j=pred[j];

if(j==0)
printf(" <- Delhi");
if(j==1)
printf(" <- Mysuru");
if(j==2)
printf(" <- Bengaluru");
}while(j!=startnode);
}
printf("\n");
}









//If the final product comes out of a machine after going through a number of machines and the money spent on each machine is known then we can find a way in which a product will require the least amount of money to get manufactured.

void machine_cost()
{


struct Graph *graph = (struct Graph*)malloc(sizeof(struct Graph));
graph -> numVertices = 3;
graph -> adjLists = malloc(sizeof(struct node *) * 3);
int i,s,s1;
for(i=0;i<3;i++)
graph -> adjLists[i]= NULL;



addEdge(graph,0,1,1000);
addEdge(graph,0,2,5000);//0->1->2 sums upto 4000, so that will be preferred instead of 0->2.
addEdge(graph,1,2,3000);

printf("Please select the machine the product is fed into\n");
printf("1.Machine 1 \n2.Machine 2\n3.Machine 3\n"); 
scanf("%d",&s1);
s=s1-1;
dijkstra_for_machine_cost(graph,3,s);
}














void dijkstra_for_machine_cost(struct Graph* graph,int n,int startnode)
{
 
	int cost[MAX][MAX],distance[MAX],pred[MAX];
	int visited[MAX],count,mindistance,nextnode,i,j;
	
	//pred[] stores the predecessor of each node
	//count gives the number of nodes seen so far
	//create the cost matrix
	
	// Even though the graph is stored in the form of an adjacency list, I will be using a matrix to store the cost.
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			cost[i][j] = 0;	


	struct node *p;
	for(i=0;i<n;i++)
	{
	p = graph->adjLists[i];
	while(p!=NULL)
	{
	cost[i][p->vertex] = p->cost;
	p=p->right;
	}
	}

	for(i=0;i<n;i++)
	{
	for(j=0;j<n;j++)
	{
	if(cost[i][j]==0)
	cost[i][j] = INFINITY;
	}
	}

	//initialize pred[],distance[] and visited[]
	for(i=0;i<n;i++)
	{
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}
	
	distance[startnode]=0;
	visited[startnode]=1;
	count=1;
	
	while(count<n-1)
	{
		mindistance=INFINITY;
		
		//nextnode gives the node at minimum distance
		for(i=0;i<n;i++)
			if(distance[i]<mindistance&&!visited[i])
			{
				mindistance=distance[i];
				nextnode=i;
			}
			
			//check if a better path exists through nextnode			
			visited[nextnode]=1;
			for(i=0;i<n;i++)
				if(!visited[i])
					if(mindistance+cost[nextnode][i]<distance[i])
					{
						distance[i]=mindistance+cost[nextnode][i];
						pred[i]=nextnode;
					}
		count++;
	}
 
	//print the path and distance of each node
for(i=0;i<n;i++)
if(i!=startnode)
{
if(i==0)
printf("\nMinimum cost to arrive at machine 1= Rs.%d ",distance[i]);
if(i==1)
printf("\nMinimum cost to arrive at machine 2= Rs.%d ",distance[i]);
if(i==2)
printf("\nMinimum cost to arrive at machine 3= Rs.%d ",distance[i]);

if(i==0)
printf("\nPath= Machine 1");
if(i==1)
printf("\nPath= Machine 2");
if(i==2)
printf("\nPath= Machine 3");
			
j=i;
do
{
j=pred[j];

if(j==0)
printf(" <- Machine 1");
if(j==1)
printf(" <- Machine 2");
if(j==2)
printf(" <- Machine 3");
}while(j!=startnode);
}
printf("\n");
}


