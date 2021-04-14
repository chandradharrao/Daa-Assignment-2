#include <stdio.h>
#include <stdlib.h>
#include<math.h>

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


typedef struct minHeapNode{
	int V; //vertex number
	int d; //distance from the src vertex
	int p; //predecessor vertex number
}minHeapNode;

typedef struct minHeap{
	int size; //curr num of nodes in heap
	int capacity; //max capacity of min heap
	minHeapNode** H;//heap array containing pointers to minHeap nodes
	int* map; //maps vertices of graph with its heap array position
}minHeap;

//account for parent vertex

void printRes(int distance[],int n){
	printf("\nDestination	Distance\n");
	for(int i = 0;i<n;i++){
		printf("%d\t%d\n",i,distance[i]);
	}
}

//function that calculates distance of shortest path from given src
//to all otehr vertices of the graph
void dijkstra(Graph* G,int dest){
	//dest == src here
	//create a min heap to represent distances from the dst vertex
	int numVert = G->V;
	minHeap* mH = createMinHeap(G->V);

	//array to store minimum distance of each vertex from dst
	int distance[numVert];

	//initially all vertices are at zero distance
	for(int i = 0;i<numVert;i++){
		distance[i] = INFINITY;
	}

	//initialize minimum heap array with min heap nodes and map with initial pos in heap
	minHeapNode** H = mH->H;
	int* map = mH->map;
	for(int i = 0;i<numVert;i++){
		//let the predecessor of all nodes be "0" ie non existent in the beg
		H[i] = newMinHeapNode(i,distance[i],0);
		map[i] = i;
	}
	//make the distance of dst vertex from itself zero
	distance[dest] = 0;
	//hence find new position of dest vertex
	decrease(mH,dest,distance[dest]);
	mH->size = numVert;

	//until there are nodes whose shortest distance is not yet finalized
	while(!isEmpty(mH->size)){
		//extract the vertes with minimum distance from dest vertex
		minHeapNode* x = extractminMode(mH);
		int xVal = x->V;
		
		//account for predecessor node

		//update the distance of all adacent vertexes of extracted min node
		Node* first = G->adjList[xVal].next;
		Node* curr = first;
		while(curr!=NULL){
			//if shortest distance to curr node from head is not finalized
			//and  it is less than previously calc value
			if(doesContain(mH,curr->value) && distance[xVal] + curr->weight < distance[curr->value]){
				//calc new distance
				distance[curr->value] = distance[xVal] + curr->weight;
				//update it in both map and heap
				decrease(mH,curr->value,distance[curr->value]);
			}
			curr = curr->next;
		}

	}

	//print the distances
	printRes(distance,numVert);
}