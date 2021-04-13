#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int value;
	int weight;
	struct Node* next;
}Node;

typedef struct Edge{
	int src;
	int dest;
	int weight;
}Edge;

typedef struct Graph{
	Node* adjList; 
}Graph;

Graph* createGraph(int numVert){ /*n is num of vertices*/
	Graph* G = (Graph*)malloc(sizeof(Graph));
	G->adjList = (Node*)malloc(sizeof(Node)*numVert);
	/*init the head vertices*/
	for(int i = 1;i<=numVert;i++){
		G->adjList[i].next = NULL;
	}
	return G;
}

//Edge is a struct with (src,dest,weight)
void addVertices(Graph* G,Edge E){
	printf("\nInside add vertices func");
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->value = E.dest;
	newNode->weight = E.weight;
	newNode->next = NULL;

	if(((G->adjList)[E.src]).next == NULL){
		/*First time atachment*/
		/*point head to new node*/
		((G->adjList)[E.src]).value = E.src;
		((G->adjList)[E.src]).next = newNode;
	}else{
		//already has nodes attached
		Node* currNode = ((G->adjList)[E.src]).next;
		//traverse til the last node
		while(currNode->next!=NULL){
			currNode = currNode->next;
		}
		//curr node points to the last node
		currNode->next = newNode;
	}
}

void printGraph(Graph* G,int numVert){
	for(int i = 1;i<=numVert;i++){
		Node* currNode = ((G->adjList)[i]).next;
		printf("%d->",currNode->value);
		currNode = currNode->next;
		while(currNode!=NULL || currNode->next!=NULL){
			if(currNode->next->next!=NULL)
				printf("%d(%d)->",currNode->value,currNode->weight);
			else
				printf("%d(%d)",currNode->value,currNode->weight);
		}
		printf("\n");
	}
}

int main(){
	int numVert,numEdges;
	printf("\nEnter number of vertices\t");
	//scanf("%d",&numVert);
	numVert = 4;
	Graph* G = createGraph(numVert);
	for(int i = 1;i<=numVert;i++){
		printf("\nEnter the number of edges from %d\t",i);
		//scanf("%d",&numEdges);
		numEdges = 3;
		for(int j = 1;j<=numEdges;j++){
			//Edge* E = (Edge*)malloc(sizeof(Edge));
			Edge E;
			E.src = i;
			printf("\nEnter the dest\t");
			int dst;
			//scanf("%d",&dst);
			dst = 2;
			E.dest = dst;
			printf("\nEnter weight of edge\t");
			int wt;
			//scanf("%d",&wt);
			wt = 4;
			E.weight = wt;
			printf("\nThe Edge E is :");
			printf("\nsrc:%d dst:%d weight:%d",E.src,E.dest,E.weight);
			printf("\nGoing into add vertices func...");
			addVertices(G,E);
			//free(E);
		}
	}
	printf("\nAdj list is:");
	printGraph(G,numVert);
}