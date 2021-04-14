#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>

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

void printList(Node head){
	printf("\nThe list is :");
	printf("%d->",head.value);
	Node* currNode = head.next;
	while(currNode!=NULL){
		printf("%d(%d),",currNode->value,currNode->weight);
		currNode = currNode->next;
	}
	printf("\n");
}

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

//Edge is a struct with (src,dest,weight)
void addVertices(Graph* G,Edge E){
	printf("\nThe Edge E is :");
	printf("\nsrc:%d dst:%d weight:%d",E.src,E.dest,E.weight);
	Node* newNode;
	newNode = (Node*)(malloc(sizeof(Node)));
	newNode->value = E.dest;
	newNode->weight = E.weight;
	newNode->next = NULL;

	if(((G->adjList)[E.src]).next == NULL){
		printf("\nFirst time attachment");
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
	printList((G->adjList)[E.src]);
	printf("\nDone..");
}

//create a node for min heap array
//V->vertex Number,d->distance from dest,p->predecessor
minHeapNode* newMinHeapNode(int V,int d,int p){
	minHeapNode* newNode = (minHeapNode*)malloc(sizeof(minHeapNode));
	newNode->V = V;
	newNode->d = d;
	newNode->p = p;
	return newNode;
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
	//heapify(mH,1);

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
	printf("\nChild indx is c:%d",c);

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

void printRes(int distance[],int n){
	printf("\nDestination	Distance\n");
	for(int i = 0;i<n;i++){
		printf("%d\t%d\n",i,distance[i]);
	}
}

//creates a minimum Heap including its map and heap array
minHeap* createMinHeap(int numVert){
	printf("\nCreating min heap...");
	minHeap* newHeap = (minHeap*)malloc(sizeof(minHeap));
	newHeap->capacity = numVert;
	newHeap->size = 0; //start of with zero size
	newHeap->H = (minHeapNode**)malloc(sizeof(minHeapNode*)*(numVert + 1));
	newHeap->map = (int*)malloc(sizeof(int)*(numVert + 1));
	printf("\nCreated Heap....");
	return newHeap;
}

//function that calculates distance of shortest path from given src
//to all otehr vertices of the graph
void dijkstra(Graph* G,int dest){
	//dest == src here
	//create a min heap to represent distances from the dst vertex
	int numVert = G->V;
	printf("\nG->V is %d",numVert);
	minHeap* mH = createMinHeap(numVert);

	if(mH == NULL){
		printf("Err.."); return;
	}else{
		printf("\nAssigned Heap....");
	}

	//array to store minimum distance of each vertex from dst
	int distance[numVert + 1];

	//initially all vertices are at zero distance
	for(int i = 1;i<=numVert;i++){
		distance[i] = (int)INFINITY;
	}

	//initialize minimum heap array with min heap nodes and map with initial pos in heap
	minHeapNode** H = mH->H;
	int* map = mH->map;
	for(int i = 1;i<=numVert;i++){
		//let the predecessor of all nodes be "0" ie non existent in the beg
		H[i] = newMinHeapNode(i,distance[i],0);
		map[i] = i;
	}
	//print the map created
	printf("\nMap is :");
	for(int i = 1;i<=numVert;i++){
		printf("%d,",mH->map[i]);
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

void printGraph(Graph* G,int numVert){
	for(int i = 1;i<=numVert;i++){
		printList(G->adjList[i]);
	}
}

int main(){
	FILE* fptr;
	char* line = NULL;
	ssize_t read;
	size_t len = 0;
	char delim[] = " ";
	//iterator for an_arr
	int anArr_iter = 0;
	int num_vertices = 0;
	int** adjMatrix = NULL;


	fptr = fopen("adjacencylist.txt","r");
	if(fptr == NULL){
		printf("\nNothing to read from\n");
		return -1;
	}

	while((read = getline(&line,&len,fptr))!=-1){
		//printf("\nAccessed line of len %d characters",(int)read);
		printf("\n%s",line);

		//pointer to the word
		char* tempPtr = strtok(line,delim);

		//array to store the space seperated words
		int num_cntr = 0;//stores number of elements in an_arr
		int* an_Arr = (int*)malloc(sizeof(int));

		//printf("\nSpace seperated values are\n");

		while(tempPtr!=NULL){
			printf("\n%s",tempPtr);
			an_Arr[num_cntr] = atoi(tempPtr);
			if(tempPtr!=NULL){
				num_cntr++;
				an_Arr = (int*)realloc(an_Arr,sizeof(int)*(num_cntr+1));
			}
			tempPtr = strtok(NULL,delim);
		}

		printf("\nThe array with max indx %d is :",num_cntr);
		for(int i = 0;i<num_cntr;i++){
			printf("%d,",an_Arr[i]);
		}

		//first line tells number of vertices
		printf("\nLine counter %d",anArr_iter);
		if(anArr_iter == 0){
			num_vertices = an_Arr[anArr_iter];
			num_vertices++;//accounts for number of vertices when starting from 1 instead of 1
			printf("\nThe number of vertices are %d",num_vertices);
			adjMatrix = (int**)malloc(sizeof(int*)*num_vertices);
			for(int i = 0;i<num_vertices;i++){
				adjMatrix[i] = (int*)malloc(sizeof(int)*num_vertices);
			}

			//initialize with zeroes
			for(int i = 1;i<num_vertices;i++){
				for(int j = 1;j<num_vertices;j++){
					adjMatrix[i][j] = 0;
				}
			}
			printf("\nCreated 2d Array");
		}else{
			//all odd vertices are the neighbouring vertices
			int neigh = 1;
			int wei = 2;

			while(wei < num_cntr){
				adjMatrix[an_Arr[0]][an_Arr[neigh]] = an_Arr[wei];
				neigh = neigh + 2;
				wei = wei + 2;
			}
		}
		anArr_iter++;
	}

	fclose(fptr);
	if(line) free(line);

	//print the adj matrix
	printf("\nthe adj matrix is ");
	for(int i = 1;i<num_vertices;i++){
		printf("\n");
		for(int j = 1;j<num_vertices;j++){
			printf("%d ",adjMatrix[i][j]);
		}
	}

	//create Graph to store adjacency List
	//create graph increments num_vertices by itself
	num_vertices--;
	printf("\nThe number of vertices is : %d",num_vertices);
	Graph* G = createGraph(num_vertices);
	for(int i = 1;i<=num_vertices;i++){
		((G->adjList)[i]).value = i;
		int givenSrc = i;
		for(int j = 1;j<=num_vertices;j++){
			printf("\n(%d,%d)",i,j);
			int givenNeightbour = j;
			int givenWeight = adjMatrix[i][j];
			printf("\nadjMatrix[%d][%d] is %d",i,j,givenWeight);
			if(givenWeight > 0){
				printf("\nWeight greater than zero...");
				Edge E;
				E.src = givenSrc;
				E.dest = givenNeightbour;
				E.weight = givenWeight;
				addVertices(G,E);
			}
		}
		printf("\nouter loop..");
	}
	printf("\nFinished Making Graph....");
	//printGraph(G,num_vertices);
	dijkstra(G,num_vertices);
	return 0;
}