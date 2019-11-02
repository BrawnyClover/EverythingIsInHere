
#include <stdio.h> 
#include <stdlib.h> 
#pragma warning(disable: 4996)
#define MAX 100

//data structure to store edge
typedef struct node {
	int num=0;
	struct node* next;
} Node;

//data structure to store graph
typedef struct graph {
	int size;
	char *vertex;     //to store the vertices in character
	int *visited; 
	node *adjList;    //adjacency list of graph
} Graph;



//function to initiate graph
void initGraph(graph *g, int v) {
	g->size = v;
	g->vertex = (char *)malloc(sizeof(char) * v);
	g->visited = (int *)malloc(sizeof(int) * v); 
	g->adjList = (node *)malloc(sizeof(node) * v);
	for (int i = 0; i < v; ++i)
		g->adjList[i].next = NULL;
}

//function to add edges 
void insertEdge(graph *g, int start, int end) {
	node *temp = (node *)malloc(sizeof(node));
	if (start >= g->size || end >= g->size) {
		printf("The vertex is out of range ... \n");
		return;
	}
	temp->num = end;
	temp->next = g->adjList[start].next;
	g->adjList[start].next = temp;
}

//function to print adjacency list of the graph
void printGraph(graph* g) {
	printf("\n===================================================================\n");
	printf("Adjacency List of the  Graph ::\n");
	for (int i = 0; i < g->size; i++) {
		node *temp = g->adjList[i].next;
		printf("Vertex %c : ", g->vertex[i]);
		while (temp) {
			printf("-> %c ", g->vertex[temp->num]);
			temp = temp->next;
		}
		printf("\n");
	}
}

//Task2
struct queue {
	int items[MAX];
	int front;
	int rear;
};

struct queue* createQueue() {
	struct queue* q = (queue *)malloc(sizeof(struct queue));
	q->front = -1;
	q->rear = -1;
	return q;
}
int isEmpty(struct queue* q) {
	if (q->rear == -1)
		return 1;
	else
		return 0;
}
void enqueue(struct queue* q, int value) {
	if (q->rear == MAX - 1)
		printf("\nQueue is Full!!");
	else {
		if (q->front == -1)
			q->front = 0;
		q->rear++;
		q->items[q->rear] = value;
	}
}
int dequeue(struct queue* q) {
	int item;
	if (isEmpty(q)) {
		printf("Queue is empty");
		item = -1;
	}
	else {
		item = q->items[q->front];
		q->front++;
		if (q->front > q->rear) {
			printf("Resetting queue");
			q->front = q->rear = -1;
		}
	}
	return item;
}

void findPath(graph *g, int s, int d, queue * q) {
	if (s == d) return;

	int *visited = (int *)malloc(sizeof(int) * g->size); 
	for (int i = 0; i < g->size; i++)
		visited[i] = 0; 

	visited[s] = 1;
	enqueue(q, s);
	
	node *temp = g->adjList[s].next; 
	for (temp = g->adjList[s].next; ; temp = temp->next){
		if(visited[temp->num] == 1){
			continue;
		}
		enqueue(q, temp->num);
		if (temp->num == d){
			break;
		}
		if (visited[temp->num] == 0) {
			visited[temp->num] = 1; 
		}
	}
	
}

int main(void) {
	freopen("input.txt","r",stdin);
	int size = 0, check = 1;
	int x, y;
	char input[2];
	char source, destination; 

	//Define max number of vertices in the graph
	printf("Enter the number of vertex of graph : ");
	scanf("%d", &size);

	//Create graph
	graph *d_graph = (graph *)malloc(sizeof(graph)); ;
	initGraph(d_graph, size);

	//Store the vertices 
	printf("Enter the vertices of graph with no spaces : ");
	scanf("%s", d_graph->vertex);

	//Get adjacency matrix as an input
	printf("Enter adjacency matrix :\n"); 
	for (int k = 0; k < size; k++) {
		for (int j = 0; j < size; j++) {
			scanf("%d", &check); 
			if (check == 1) {
				insertEdge(d_graph, k, j);
			}
		}
	}

	//print the graph inputted
	printGraph(d_graph);

	//get input of source and destination
	printf("\n===================================================================\n");
	printf("Enter source and destination : ");
	scanf("%s", input);
	printf("%s", input);

	int n = d_graph->size;
	int snode, enode;
	for (int i = 0; i < n; i++) {
		if (d_graph->vertex[i] == input[0]) {
			snode = i;
			break;
		}
	}
	for (int i = 0; i < n; i++) {
		if (d_graph->vertex[i] == input[1]) {
			enode = i;
			break;
		}
	}
	printf("\n");
	struct queue *q = createQueue();
	findPath(d_graph, snode, enode, q);
	
	for(int i=q->front; i<=q->rear; i++){
		printf("%c ", d_graph->vertex[q->items[i]]);
	}
	return 0;
}
