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
	int V; //num of vertices in graph
}Graph;

Graph* createGraph(int numVert){ /*n is num of vertices*/
	Graph* G = (Graph*)malloc(sizeof(Graph));
	//allocate size for 5 so that it would be from 1,2,3,4
	G->adjList = (Node*)malloc(sizeof(Node)*(numVert+1));
	G->V = numVert;
	/*init the head vertices*/
	for(int i = 1;i<=numVert;i++){
		((G->adjList)[i]).next = NULL;
	}
	printf("\nSuccessful....");
	return G;
}
/*void tryio(void)
{
	Node *newNode;
	newNode =(Node*)malloc(sizeof(Node));
}*/

void printLinst(Node head){
	printf("\nThe list is :");
	printf("%d->",head.value);
	Node* currNode = head.next;
	while(currNode!=NULL){
		printf("%d(%d),",currNode->value,currNode->weight);
		currNode = currNode->next;
	}
	printf("\n");
}

//Edge is a struct with (src,dest,weight)
void addVertices(Graph* G,Edge E){
	//printf("\nInside add vertices func");
	//printf("Sice of node :%d",(int)sizeof(Node));
	printf("\nThe Edge E is :");
	printf("\nsrc:%d dst:%d weight:%d",E.src,E.dest,E.weight);
	Node* newNode;
	//Graph *g=(Graph*) malloc(sizeof(Graph));
	newNode = (Node*)(malloc(sizeof(Node)));
	//Node x;
	//Node* newNode = &x;
	//if (newNode==NULL)exit;
	newNode->value = E.dest;
	newNode->weight = E.weight;
	newNode->next = NULL;

	if(((G->adjList)[E.src]).next == NULL){
		printf("\nFirst time attachment");
		//First time atachment
		//point head to new node
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
	printLinst((G->adjList)[E.src]);
	printf("\nDone..");
}

void printGraph(Graph* G,int numVert){
	for(int i = 1;i<=numVert;i++){
		printLinst(G->adjList[i]);
	}
}

/*void printGraph(Graph* G,int numVert){
	//printf("\nPrinting,Num of vert : %d\n",numVert);
	for(int i = 1;i<=numVert;i++){
		printf("%d-> ",(G->adjList)[i].value);
		Node* currNode = ((G->adjList)[i]).next;
		if(currNode == NULL){
			printf("Empty...");
		}
		else{
			printf("%d(%d)->",currNode->value,currNode->weight);
			//currNode = currNode->next;
			while((currNode->next)!=NULL){
				if(currNode->next == NULL){
					printf("%d(%d)",currNode->value,currNode->weight);
					break;
				}
				else if(currNode->next->next!=NULL){
					printf("%d(%d)->",currNode->value,currNode->weight);
				}
				else{
					printf("%d(%d)",currNode->value,currNode->weight);
				}
				
				//printf("%d(%d)->",currNode->value,currNode->weight);
				currNode = currNode->next;
			}
			printf("\n");
		}
		//currNode = currNode->next;
		//if(currNode == NULL) return;
	}
}*/


int main(){
	int numVert,numEdges;
	//Node *test=(Node*)malloc(sizeof(Node));
	printf("\nEnter number of vertices\t");
	//scanf("%d",&numVert);
	numVert = 4;
	Graph* G = createGraph(numVert);
	//Graph *G=NULL;
	for(int i = 1;i<=numVert;i++){
		printf("\nEnter the number of edges from %d\t",i);
		scanf("%d",&numEdges);
		//numEdges = 3;
		((G->adjList)[i]).value = i;
		for(int j = 1;j<=numEdges;j++){
			//Edge* E = (Edge*)malloc(sizeof(Edge));
			Edge E;
			E.src = i;
			printf("\nEnter the dest\t");
			int dst;
			scanf("%d",&dst);
			//dst = 2;
			E.dest = dst;
			printf("\nEnter weight of edge\t");
			int wt;
			scanf("%d",&wt);
			//wt = 4;
			E.weight = wt;
			//printf("\nThe Edge E is :");
			//printf("\nsrc:%d dst:%d weight:%d",E.src,E.dest,E.weight);
			//printf("\nGoing into add vertices func...");
			addVertices(G,E);
			//tryio();
			//free(E);
		}
	}
	printf("\nAdj list is:\n");
	printGraph(G,numVert);
}