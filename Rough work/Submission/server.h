#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct minHeapNode{
	int V; //vertex number
	int d; //distance from the src vertex
	int p; //predecessor vertex numbers
}minHeapNode;

typedef struct minHeap{
	int size; //curr num of nodes in heap
	int capacity; //max capacity of min heap
	minHeapNode** H;//heap array containing pointers to minHeap nodes
	int* map; //maps vertices of graph with its heap array position
}minHeap;

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


void printList(Node head);
Graph* createGraph(int numVert);
void addVertices(Graph* G,Edge E);
minHeapNode* newMinHeapNode(int V,int d,int p);
bool isEmpty(int n);
void swapMinHeapNodes(minHeapNode** H,int p,int target);
void swapMapNodes(int* map,minHeapNode* n1,minHeapNode* n2);
void heapify(minHeap* mH,int target);
minHeapNode* extractminMode(minHeap* mH);
bool doesContain(minHeap* mH,int V);
void printHeapArr(minHeapNode** H,int numVert);
void intArrPrinter(int* arr,int n);
void decrease(minHeap* mH,int v,int newDst);
void printHeap(minHeapNode** H,int n);
void printPath(minHeapNode* x,minHeapNode** H,int* map);
void printRes(int distance[],int n,minHeapNode** H,int* map);
minHeap* createMinHeap(int numVert);
void minHeapNodePrinter(minHeapNode* x);
void boolPrinter(bool x);
void dijkstra(Graph* G,int dest);
void printGraph(Graph* G,int numVert);

