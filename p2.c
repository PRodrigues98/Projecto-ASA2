#include <stdio.h>
#include <stdlib.h>


#define set_color(A, B, C) {*(colors + t_l * (A) + (B)) = C;}
#define get_color(A, B) *(colors + t_l * (A) + (B))


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

void Kruskal(int size_edges);

void merge_sort(int l, int r);
void merge(int l, int m, int r);
int less(EDGE a, EDGE b);

void printColors();



char *colors;
int sum = 0, black = 0, white = 0, lines, columns;
EDGE *edges, *edges_aux;
VERTEX_SET *graph;


int main(){
	
	int i, j;

	graph = (VERTEX_SET*)malloc(sizeof(VERTEX_SET) * m * n);

	scanf("%d %d", &lines, &columns);

	colors = (char*)malloc(sizeof(char) * m * n);

	for(i = 0; i < lines; i++){
		for(j = 0; j < columns; j++){

			scanf("%d ", ->)
		}
	}

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

void Kruskal(int size_edges){
	VERTEX_SET *A = NULL;

	merge_sort(0, size_edges - 1);

	int i = 0;

	while(black + white < size_graph){
		if((edges[i].color_origin == edges[i].origin->color || edges[i].origin->color == -1) && (edges[i].color_dest == edges[i].dest->color || edges[i].dest->color == -1)){
			if(Find_Set(edges[i].origin) != Find_Set(edges[i].dest)){
				Union(edges[i].origin, edges[i].dest);

				/*Color vertexes of known edge*/
				edges[i].origin->color = edges[i].color_origin;
				set_color(edges[i].origin->x, edges[i].origin->y, edges[i].color_origin);

				edges[i].dest->color = edges[i].color_dest;
				set_color(edges[i].dest->x, edges[i].dest->y, edges[i].color_dest);

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


 /********************************************\
|                                              |
|                  Merge Sort                  |
|                                              |
 \********************************************/

void merge_sort(int l, int r){
	int m = (r + l) / 2;

	if (r <= l) 
		return;

	merge_sort(l, m);
	merge_sort(m + 1, r);
	merge(l, m, r);
}

void merge(int l, int m, int r){
	int i, j, k;

	for(i = m + 1; i > l; i--) {
		edges_aux[i - 1] = edges[i - 1];
	}

	for(j = m; j < r; j++) {
		edges_aux[r + m - j] = edges[j + 1];
	}

	for(k = l; k <= r; k++) {
		if(less(edges_aux[j], edges_aux[i])) {
    		edges[k] = edges_aux[j--];
		}
		else {
			edges[k] = edges_aux[i++];
		}
	}
}

int less(EDGE a, EDGE b){
	if(a.value <= b.value){
		if(a.value == b.value){
			int a_black_count = (a.color_origin == 'P') + (a.color_dest == 'P');
			int b_black_count = (b.color_origin == 'P') + (b.color_origin == 'P');

			if(b_black_count < a_black_count){
				return 0;
			}
		}

		return 1;
	}

	return 0;
}


 /********************************************\
|                                              |
|                    Colors                    |
|                                              |
 \********************************************/

void printColors(int ){
	int i, j;

	for(i = 0; i < lines; i++){
		for(j = 0; j < lines; j++){
			
		}
	}
}