#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>

#define n 5
#define TRUE 1
#define FALSE 0

typedef struct{
	_Bool black;
	_Bool white;
	_Bool blue;
	int value;
	int parent;
}Node;

int arr[n][n];
Node node[n][n], node2[n][n];

void init(){//Initialize the ARRAY
	int count = 0;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			arr[i][j] = count;
			node[i][j].value = arr[i][j];
			node[i][j].parent = node[i][j].value;
			++count;
		}
	}
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			if(i == 0 && j == 0)
				printf("Array:\n"); //Prints the Array
			printf("%02d ", arr[i][j]);
		}
		printf("\n");
	}
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			if(i == 0 && j == 0)
				printf("Nodes:\n"); // Prints the Nodes
			printf("value:  %02d	", node[i][j].value);
			printf("parent: %02d\n", node[i][j].parent);
		}
	}
}

int findRoot(int i, int j){
	if(node[i][j].parent == node[0][j].parent && (node[0][j].white || node[0][j].blue))
		return node[0][j].parent;
	return findRoot(i, j);
}

_Bool isConnected(int i, int j){
	return findRoot(i, j) == findRoot(i, j);
}

_Bool isOpenSite(int i, int j){
	if(isConnected(i, j) && node[i][j].white)
			return TRUE;
	return FALSE;	
}

_Bool isBlockedSite(int i, int j){
		if(node[i][j].black)
			return TRUE;
		return FALSE;
}

_Bool isFullSite(int i, int j){
	if(isConnected(i, j) && node[i][j].blue)
		return TRUE;
	return FALSE;
}

_Bool isPercolated(int i, int j){
	if(isFullSite( i , j) && isConnected(i, j))
		return TRUE;
	return FALSE;
}
void Union(int i, int j){
	if(i > 0 && node[i][j].white && node[i-1][j].white)
		node[i][j].parent = node[i-1][j].parent;
	if(i < n-1 && node[i][j].white && node[i+1][j].white)
		node[i][j].parent = node[i+1][j].parent;
	if(j > 0 && node[i][j].white && node[i][j-1].white)
		node[i][j].parent = node[i][j-1].parent;
	if(j <n-1 && node[i][j].white && node[i][j+1].white)
		node[i][j].parent = node[i][j+1].parent;
}

int main(){
	init(node, node2);
	/**
	 *	This is another way to declare node and node2 by using --> malloc
	 **/
	/*Node **node = (Node **)malloc(n * sizeof(Node*));
	Node **node2 = (Node **)malloc(n * sizeof(Node*));
	for(int i = 0; i < n; ++i){
		node[i] = (Node *)malloc(n * sizeof(Node));
		node2[i] = (Node *)malloc(n * sizeof(Node));
	}*/
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			scanf("%d",&arr[i][j]);
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			if(i ==0 || j == 0)
				continue;
			if(!isPercolated(i, j)){
				if(isOpenSite(i, j) && !isConnected(i, j))
					Union(i, j);
			}
			if(isFullSite(i , j) && isPercolated(i , j)){
				printf("Percolated\n");
			}
			if(!isPercolated(i, j) && !isFullSite(i, j) && !isConnected(i, j) && !isOpenSite(i, j) && isBlockedSite(i, j)){
				printf("Not Percolated\n");
			}
		}
	}
	return 0;	
}
