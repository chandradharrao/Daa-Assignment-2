#include <stdlib.h>
#include <stdio.h>

typedef struct minHeapNode{
	int vertexNum;
	int d; //distance from the src vertex
	int p; //predecessor vertex number
}minHeapNode;

typedef struct minHeap{
	int size; //curr num of nodes in heap
	int capacity; //max capacity of min heap
	minHeapNode** H;
}minHeap;

//create a node of min heap
minHeap newMinHeapNode(int vertexNum,int d,int p){
	minHeapNode* newNode = (minHeapNode*)malloc(sizeof(minHeapNode));
	minHeapNode-<vertexNum = vertexNum;
	newNode->d = d;
	newNode->p = p;
	return newNode;
}

minHeap createMinHeap(int numVert){
	minHeap* newHeap = (minHeapNode*)malloc(sizeof(minHeap));
	minHeap->capacity = numVert;
	minHeap->size = 0; //start of with zero size
	minHeap->H = (minHeapNode**)malloc(sizeof(minHeapNode*)*capacity);
}