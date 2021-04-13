#include <stdio.h>
#include <stdlib.h>
#include<math.h>

//account for parent vertex

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
		//let the parent of all nodes be "0" ie non existent in the beg
		H[i] = newMinHeapNode(i,distance[i],0);
		map[i] = i;
	}
	//make the distance of dst vertex from itself zero
	distance[dest] = 0;
	//hence find new position of dest vertex
	decrease(mH,dst,distance[dst]);
	mH->size = numVert;

	//consideration abut parent node

	//until there are nodes whose shortest distance is not yet finalized
	while(!isEmpty(mH->size)){
		//extract the vertes with minimum distance from dest vertex
		minHeapNode* x = extractminMode(mH);
		int xVal = x->V;

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

	//print the distance

}