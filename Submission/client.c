#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "server.h"

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
		//printf("\nNothing to read from\n");
		return -1;
	}

	while((read = getline(&line,&len,fptr))!=-1){
		////printf("\nAccessed line of len %d characters",(int)read);
		//printf("\n%s",line);

		//pointer to the word
		char* tempPtr = strtok(line,delim);

		//array to store the space seperated words
		int num_cntr = 0;//stores number of elements in an_arr
		int* an_Arr = (int*)malloc(sizeof(int));

		////printf("\nSpace seperated values are\n");

		while(tempPtr!=NULL){
			//printf("\n%s",tempPtr);
			an_Arr[num_cntr] = atoi(tempPtr);
			if(tempPtr!=NULL){
				num_cntr++;
				an_Arr = (int*)realloc(an_Arr,sizeof(int)*(num_cntr+1));
			}
			tempPtr = strtok(NULL,delim);
		}

		//printf("\nThe array with max indx %d is :",num_cntr);
		for(int i = 0;i<num_cntr;i++){
			//printf("%d,",an_Arr[i]);
		}

		//first line tells number of vertices
		//printf("\nLine counter %d",anArr_iter);
		if(anArr_iter == 0){
			num_vertices = an_Arr[anArr_iter];
			num_vertices++;//accounts for number of vertices when starting from 1 instead of 1
			//printf("\nThe number of vertices are %d",num_vertices);
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
			//printf("\nCreated 2d Array");
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

	////print the adj matrix
	//printf("\nthe adj matrix is ");
	for(int i = 1;i<num_vertices;i++){
		//printf("\n");
		for(int j = 1;j<num_vertices;j++){
			//printf("%d ",adjMatrix[i][j]);
		}
	}

	//create Graph to store adjacency List
	//create graph increments num_vertices by itself
	num_vertices--;
	//printf("\nThe number of vertices is : %d",num_vertices);
	Graph* G = createGraph(num_vertices);
	for(int i = 1;i<=num_vertices;i++){
		((G->adjList)[i]).value = i;
		int givenSrc = i;
		for(int j = 1;j<=num_vertices;j++){
			//printf("\n(%d,%d)",i,j);
			int givenNeightbour = j;
			int givenWeight = adjMatrix[i][j];
			//("\nadjMatrix[%d][%d] is %d",i,j,givenWeight);
			if(givenWeight > 0){
				////printf("\nWeight greater than zero...");
				Edge E;
				//add in reverse order in order to account for dest and src reversal
				E.src = givenNeightbour;
				E.dest = givenSrc;
				E.weight = givenWeight;
				addVertices(G,E);
			}
		}
		////printf("\nouter loop..");
	}
	////printf("\nFinished Making Graph....");
	////printGraph(G,num_vertices);
	dijkstra(G,num_vertices);
	return 0;
}