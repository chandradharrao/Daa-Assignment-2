#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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

//create a node for min heap array
//V->vertex Number,d->distance from dest,p->predecessor
minHeapNode* newMinHeapNode(int V,int d,int p){
	minHeapNode* newNode = (minHeapNode*)malloc(sizeof(minHeapNode));
	newNode->V = V;
	newNode->d = d;
	newNode->p = p;
	return newNode;
}

//creates a minimum Heap including its map and heap array
minHeap* createMinHeap(int numVert){
	minHeap* newHeap = (minHeap*)malloc(sizeof(minHeap));
	newHeap->capacity = numVert;
	newHeap->size = 0; //start of with zero size
	newHeap->H = (minHeapNode**)malloc(sizeof(minHeapNode*)*(numVert + 1));
	newHeap->map = (int*)malloc(sizeof(int)*(numVert + 1));
	return newHeap;
}

//check if heap is empty
bool isEmpty(int n){
	return (n == 0?true:false);
}

//minHeap->H contains pointers to node
//address of pointers to node are of type minHeapNode**
void swapMinHeapNodes(minHeapNode** H,int p,int target){
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
	minHeapNode** H = mH->H;//the heap array

	printf("\n%d vs %d",H[c]->d,H[p]->d);
	//if left child exists and is lesser
	if(c<=n && H[c]->d < H[p]->d)
		p = c;
	//if right child exists and is lesser
	if(c+1<=n && H[c+1]->d < H[p]->d)
		p = c+1;
	//swap the node to target position
	if(p!=target){
		printf("\nFinsihed swapping...");
		swapMinHeapNodes(H,p,target);
		swapMapNodes(mH->map,mH->H[p],mH->H[target]);
		int nxtPos = p;
		//make the parent as target
		heapify(mH,nxtPos);
	}
}

//extract the root node
minHeapNode* extractminMode(minHeap* mH){
	if(isEmpty(mH->size)) return NULL;

	//first node is min node
	minHeapNode* root = (mH->H)[1];

	//replace root with last node and 
	(mH->H)[1] = (mH->H)[mH->size];

	//update map value ie heap array position of the last node
	(mH->map)[mH->size] = 1;
	//update value of first node to the end of non -heap array
	(mH->map)[1] = (mH->size);

	//reduce heap size
	mH->size = (mH->size) - 1;
	//heapify the heap from the new first node
	heapify(mH,1);

	return root;
}

//function to check if node is present in heap in O(1) time
bool doesContain(minHeap* mH,int V){
	int* map = mH->map;
	//accounted for vetrex scheme of 1 to V
	if(V <= mH->size) return true;
	return false;
}

//reduce the dist value of the vertex v and reheapify
void decrease(minHeap* mH,int v,int newDst){
	//grab the index in heap array of node with value v from the map
	int* map = mH->map;
	int c = map[v];
	//grab the node at index c and update dist
	(mH->H)[c]->d = newDst;
	int p = (c-1)/2;
	while(p > 1 && mH->H[c]->d < mH->H[p]->d){
		//swap child and parent
		swapMinHeapNodes(mH->H,p,c);
		swapMapNodes(map,mH->H[p],mH->H[c]);

		//move child to parent pos
		c = p;
		//find new pparent index
		p = (c-1)/2;
	}
}

void printHeap(minHeapNode** H,int n){
	for(int i = 1;i<=n;i++){
		printf("%d,",H[i]->V);
	}
	printf("..................\n");
}

/*
int main(){
	int arr[6][3] = {{6,6,0},{4,4,0},{3,3,0},{1,1,0},{2,2,0},{5,5,0}};
	minHeap* newHeap = (minHeap*)malloc(sizeof(minHeap));
	minHeapNode** x = (minHeapNode**)malloc(sizeof(minHeapNode*)*6);
	for(int i = 1;i<=6;i++){
		minHeapNode* y = (minHeapNode*)malloc(sizeof(minHeapNode));
		y->V = arr[i][0];
		y->d = arr[i][1];
		y->p = arr[i][2];
		x[i] = y;
	}
	newHeap->capacity = 6;
	newHeap->size = 0; //start of with zero size
	newHeap->H = x;
	newHeap->map = (int*)malloc(sizeof(int)*newHeap->capacity);
	
	heapify(newHeap,0);
	printf("\nSorted order is :");
	while(true){
		minHeapNode* nd = extractminMode(newHeap);
		if(nd == NULL){
			printf("\nReturned Null");
			return -1;
		}else{
			printf("%d,",nd->d);
		}
	}
	return 0;
}
*/

