#include <stdio.h>
#include <stdlib.h>


#define set_color(A, B, C) {*(colors * (A) + (B)) = C;}
#define get_color(A, B) *(colors * (A) + (B))


/* Estruturas para conjuntos disjuntos */
typedef struct set VERTEX_SET;
typedef struct edge EDGE;

typedef struct set {
	int x, y;
	int rank;
	int P_value, C_value;
	char color;
	VERTEX_SET *p;
} VERTEX_SET;

typedef struct edge {
	int value;
	int con_value;
	char color_origin, color_dest;
	VERTEX_SET *origin;
	VERTEX_SET *dest;
} EDGE;



VERTEX_SET *Find_Set(VERTEX_SET *x);
void Union(VERTEX_SET *x, VERTEX_SET *y);
void Link(VERTEX_SET *x, VERTEX_SET *y);

void Kruskal(EDGE *edges, int size_graph, int size_edges);



char *colors;
int sum = 0, black = 0, white = 0;


int main(){
	


	return 0;
}


 /********************************************\
|                                              |
|           Operacoes sobre conjuntos          |
|                                              |
 \********************************************/

VERTEX_SET *Find_Set(VERTEX_SET *x){
	if(x != x->p){
		x->p = Find_Set(x->p);
	}

	return x->p;
}

void Union(VERTEX_SET *x, VERTEX_SET *y){
	Link(Find_Set(x), Find_Set(y));
}

void Link(VERTEX_SET *x, VERTEX_SET *y){
	if(x->rank > y->rank){
		y->p = x;
	}
	else{
		x->p = y;
		if(x->rank == y->rank){
			y->rank++;
		}
	}
}


 /********************************************\
|                                              |
|              Algoritmo de Kruskal            |
|                                              |
 \********************************************/

void Kruskal(EDGE *edges, int size_graph, int size_edges){
	VERTEX_SET *A = NULL;

	//merge_sort(edges);

	int i = 0;

	while(black + white < size_graph){
		if((edges[i].color_origin == edges[i].origin->color || edges[i].origin->color == -1) && (edges[i].color_dest == edges[i].dest->color || edges[i].dest->color == -1)){
			if(Find_Set(edges[i].origin) != Find_Set(edges[i].dest)){
				Union(edges[i].origin, edges[i].dest);

				/*Color vertexes of known edge*/
				edges[i].origin->color = edges[i].color_origin;
				edges[i].dest->color = edges[i].color_dest;

				black += (edges[i].color_origin == 'P') + (edges[i].color_dest == 'P');
				white += (edges[i].color_origin == 'C') + (edges[i].color_dest == 'C');

				sum += (edges[i].color_origin == 'P') * edges[i].origin->P_value + (edges[i].color_origin == 'C') * edges[i].origin->C_value + (edges[i].color_dest == 'P') * edges[i].dest->P_value + (edges[i].color_dest == 'C') * edges[i].dest->C_value;

				if(edges[i].color_origin != edges[i].color_dest){
					sum += edges[i].con_value;
				}
			}
		}
	}
}
