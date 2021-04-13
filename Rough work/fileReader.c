#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

		//printf("%d\n",(int)len);

		//int  num_words = ((read/sizeof(char))/2);
		//printf("\nThe number of words are %d",num_words);

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
		//account for zero getting added in the end
		//num_cntr--;

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

	//print the adj matrix
	printf("\nthe adj matrix is ");
	for(int i = 1;i<num_vertices;i++){
		printf("\n");
		for(int j = 1;j<num_vertices;j++){
			printf("%d ",adjMatrix[i][j]);
		}
	}

	fclose(fptr);
	if(line) free(line);
	return 0;
}