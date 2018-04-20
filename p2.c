#include <stdio.h>
#include <stdlib.h>


/* Estruturas para grafos */
typedef struct edge Edge;
typedef struct vertex Vertex;

typedef struct vertex {
	int cor, d, low, **SCCRoot, inList;
	Edge *head;
} Vertex;

typedef struct edge {
	Vertex *destVertex;
	Edge *next;
} Edge;


typedef struct set{

}




int main()
{
	


	return 0;
}
