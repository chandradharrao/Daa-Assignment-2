#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//note no zero indexing,hence inc by 1 everywhere

typedef struct minHeapNode{
	int V;
	int d; //distance from the src vertex
	int p; //predecessor vertex number
}minHeapNode;

typedef struct minHeap{
	int size; //curr num of nodes in heap
	int capacity; //max capacity of min heap
	minHeapNode** H;//heap array containing pointers to minHeap nodes
	int* map; //maps vertices of graph with its heap array position
}minHeap;

//create a node of min heap
minHeap newMinHeapNode(int V,int d,int p){
	minHeapNode* newNode = (minHeapNode*)malloc(sizeof(minHeapNode));
	minHeapNode->V = V;
	newNode->d = d;
	newNode->p = p;
	return newNode;
}

minHeap createMinHeap(int numVert){
	minHeap* newHeap = (minHeapNode*)malloc(sizeof(minHeap));
	minHeap->capacity = numVert;
	minHeap->size = 0; //start of with zero size
	minHeap->H = (minHeapNode**)malloc(sizeof(minHeapNode*)*minHeap->capacity);
	minHeap->map = (int*)malloc(sizeof(int)*minHeap->capacity);
	return minHeap;
}

//check if heap is empty
bool isEmpty(int n) return (n == 0?true:false);

//minHeap->H contains pointers to node
//address of pointers to node are of type minHeapNode**
void swapMinHeapNodes(minHeapNode* H,int p,int target){
	minHeapNode* temp = H[p];
	H[p] = H[target];
	H[target] = temp;
}

//swap position in the map array
void swapMapNodes(int* map,minHeapNode* n1,minHeapNode* n2){
	//copy the heap array index of n1
	int tempVal = map[n1->V];
	//copy the heap array index of n2 to n1
	map[n1->V] = map[n2->V];
	//copy the tempVal to n2
	map[n2->V] = tempVal;
}	

//heapifies the array starting from the target index
void heapify(minHeap* mH,int target){
	int p,c,n;
	p = target;//parent index
	c = 2*p+1;//left child index
	n = mH->size;//curr num vertices
	H = mH->H;//the heap array

	//if left child exists and is lesser
	if(c<n && H[c]<H[p])
		p = c;
	//if right child exists and is lesser
	if(c+1<n && H[c+1]<H[p])
		p = c+1;
	//swap the node to target position
	if(p!=target){
		swapMinHeapNodes(H,p,target);
		swapMapNodes(mH->map,p,target);
		int nxtPos = p;
		//make the parent as target
		heapify(mH,nxtPos);
	}
}

//extract the root node
minHeapNode* extractminMode(minHeap* mH){
	if(isEmpty(mH->size)) return NULL;

	//first node is min node
	minHeapNode* root = (mH->H)[0];

	//replace root with last node and 
	//decrease effective size of heap array
	(mH->H)[0] = (mH->H)[mH->size -1];

	//update map value ie heap array position of the last node
	(mH->map)[mH->size -1] =0;
	//update value of first node to the end of non -heap array
	(mH->map)[0] = (mH->size) -1

	//reduce heap size
	mH->size = (mH->size) - 1;
	//heapify the heap from the new first node
	heapify(mH,0);

	return root;
}

//function to check if node is present in heap in O(1) time
bool doesContain(minHeap* mH,int V){
	int* map = mH->map;
	//accounted for vetrex scheme of 1 to V
	if(V <= mH->size) return true;
	return false;
}




