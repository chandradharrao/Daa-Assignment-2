#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>

#define INFINITY 9999

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
	printf("\n--------------");
	printf("\nindx1 is: %d",p);
	printf("\nindx2 is: %d",target);
	printf("\n----------------");
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
	printf("\nCalled heapify on %d",target);
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

	printf("\n%d vs %d",p,target);
	//swap the node to target position
	if(p!=target){
		printf("\nParent != target");
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

	//replace root with last node
	//2,1,3,2
	(mH->H)[1] = (mH->H)[mH->size];
	//replace last node with extracted
	//2,1,3,4
	(mH->H)[mH->size] = root;

	//update map value 
	//ie heap array position of the last node
	(mH->map)[(mH->H)[1]->V] = 1;
	//update value of first node to the end of non -heap array
	(mH->map)[(mH->H)[mH->size]->V] = (mH->size);

	//reduce heap size
	mH->size = (mH->size) - 1;
	printf("\nNew Size is %d",mH->size);
	//heapify the heap from the new first node
	heapify(mH,1);

	return root;
}

//function to check if node is present in heap in O(1) time
bool doesContain(minHeap* mH,int V){
	//accounted for vetrex scheme of 1 to V
	if(mH->map[V] <= mH->size) return true;
	return false;
}

printHeapArr(minHeapNode** H,int numVert){
	printf("\nHeap is :");
	for(int i = 1;i<=numVert;i++){
		printf("(%d,%d,%d),",H[i]->V,H[i]->d,H[i]->p);
	}
}

intArrPrinter(int* arr,int n){
	for(int i = 1;i<=n;i++){
		printf("%d,",arr[i]);
	}
}

//reduce the dist value of the vertex v and reheapify
void decrease(minHeap* mH,int v,int newDst){
	//grab the index in heap array of node with value v from the map
	int* map = mH->map;
	int c = map[v];
	printf("\nmap is : ");
	intArrPrinter(map,mH->capacity);
	printf("\nmap indx of %d is c:%d",v,c);

	//grab the node at index c and update dist
	(mH->H)[c]->d = newDst;
	printHeapArr(mH->H,mH->size);

	float t = (float)(c-1)/2;
	int p = (int)ceil(t);
	printf("\nParent Index is : %d",p);

	int cVal = mH->H[c]->d ;
	int pVal = mH->H[p]->d;
	printf("\nThe d val of child and parent is %d,%d",cVal,pVal);

	while(p >= 1 && cVal< pVal){
		printf("\n child val lesser than parent val");
		printf("\nNew child and parent indx : (%d,%d)",c,p);

		//swap in map
		swapMapNodes(map,mH->H[p],mH->H[c]);
		intArrPrinter(map,mH->size);

		//swap child and parent
		swapMinHeapNodes(mH->H,p,c);
		printf("\nAfter swapping,heap is :");
		printHeapArr(mH->H,mH->size);
		printf("\nAfter swapping,map is : ");
		intArrPrinter(map,mH->capacity);
		
		//move child to parent pos
		c = p;
		//find new pparent index
		float t = (float)(c-1)/2;
		printf("\nt:%f",t);
		p = (int)ceil(t);
		printf("\np:%d",p);
		printf("\nC:%d",c);
		int cntrl;
		printf("\nPress 1 to continue");
		scanf("%d",&cntrl);
	}
	printf("\n***********Broken out of while loop of decrease function********************");
}

void printHeap(minHeapNode** H,int n){
	printHeapArr(H,n);
	printf("..................\n");
}

void printRes(int distance[],int n){
	printf("\nDestination	Distance\n");
	for(int i = 1;i<=n;i++){
		printf("\n%d\t%d",i,distance[i]);
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

void minHeapNodePrinter(minHeapNode* x){
	printf("(%d,%d,%d)",x->V,x->d,x->p);
}

void boolPrinter(bool x){
	if(x) printf("True");
	else printf("False");
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
		printf("\nAssigned Heap to mH....");
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
	printHeapArr(H,numVert);

	//print the map created
	printf("\nMap is :");
	intArrPrinter(map,numVert);

	//make the distance of dst vertex from itself zero
	distance[dest] = 0;
	printf("\nDistance array is :");
	intArrPrinter(distance,numVert);
		
	//hence find new position of dest vertex
	decrease(mH,dest,distance[dest]);
	mH->size = numVert;

	printf("\nBefore entering dijkstra,map is : ");
	intArrPrinter(map,mH->capacity);

	printf("\nEntering Dijkstras while loop............");
	//until there are nodes whose shortest distance is not yet finalized
	while(!isEmpty(mH->size)){
		//extract the vertes with minimum distance from dest vertex
		minHeapNode* x = extractminMode(mH);
		int xVal = x->V;
		printf("\nThe extracted minHeap node is :");
		minHeapNodePrinter(x);
		printf("\nThe heap after extraction is :");
		printHeapArr(mH->H,mH->size);
		printf("\nAfter extraction,map is : ");
		intArrPrinter(map,mH->capacity);
		
		//**********account for predecessor node**********************

		//update the distance of all adacent vertexes of extracted min node
		Node* first = G->adjList[xVal].next;
		Node* curr = first;
		printf("\nThe adj list of %d is:",xVal);
		printList(G->adjList[xVal]);

		if(curr!=NULL)
		{
			printf("\nStarting Curr Node in adjList is %d(%d)",curr->value,curr->weight);
		}
		else{
			printf("\nNull curr");
		}

		printf("\nTraversing through the adj list....");
		while(curr!=NULL){
			printf("\nThe Curr Node is %d",curr->value);
			int v = curr->value;

			//if shortest distance to curr node from head is not finalized
			//and  it Fis less than previously calc value
			printf("\nAll bools-------------------------------------------");
			//printf("\ndoesContain(mH,v): ");
			//boolPrinter(doesContain(mH,v));
			//printf("\ndistance[xVal] != INFINITY :");
			//boolPrinter(distance[xVal] != INFINITY);
			printf("\n%d<%d : ",distance[xVal] + curr->weight,distance[v]);
			boolPrinter(distance[xVal] + curr->weight < distance[v]);
			printf("\nEnd of bools------------------------------------------");

			//if(doesContain(mH,v) && distance[xVal] != INFINITY && distance[xVal] + curr->weight < distance[v]){
			if(distance[xVal] + curr->weight < distance[v]){
				printf("\nDist from ");minHeapNodePrinter(x);printf(" to %d is %d",curr->value,distance[xVal] + curr->weight);

				//calc new distance
				distance[curr->value] = distance[xVal] + curr->weight;
				printf("\nThe distance arr after updation is :\n");
				intArrPrinter(distance,mH->capacity);

				printf("\nCalling decrease function for vertex %d.....",curr->value);
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
				E.src = givenNeightbour;
				E.dest = givenSrc;
				E.weight = givenWeight;
				addVertices(G,E);
			}
		}
		printf("\nouter loop..");
	}
	printf("\nFinished Making Graph....");
	printGraph(G,num_vertices);
	dijkstra(G,num_vertices);
	return 0;
}