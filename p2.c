#include <stdio.h>
#include <stdlib.h>


#define SOURCE_X -2
#define SOURCE_Y -2
#define SINK_X -2
#define SINK_Y -2


/* Estruturas para conjuntos disjuntos */
typedef struct vertex VERTEX;
typedef struct edge EDGE;
typedef struct queue QUEUE;


typedef struct queue {
	EDGE *edge;
	QUEUE *prev;
	QUEUE *next;
} QUEUE;

typedef struct vertex {
	EDGE *pred;

	int bfs_count;

	QUEUE *edges;
} VERTEX;

typedef struct edge {
	int origin_x, origin_y;
	int dest_x, dest_y;

	/* flux denotes a backwards edge */
	int flux;
	/* cap_res denotes a forwards edge */
	int cap_res;
} EDGE;



int bfs();
QUEUE* enqueue(EDGE *e, QUEUE *q);
QUEUE* enqueueQ(QUEUE *e, QUEUE *q);
void printColors();



int flow = 0, lines, columns, bfs_count = 0;
VERTEX source, sink;
VERTEX *graph;



int main(){
	
	int i, j, tmp;

	scanf("%d %d\n", &lines, &columns);

	graph = (VERTEX*)malloc(sizeof(VERTEX) * lines * columns);

	int *tmp_P_values = (int*)malloc(sizeof(int) * lines * columns);

	for(i = 0; i < lines; i++){
		for(j = 0; j < columns; j++){
			scanf("%d ", &tmp_P_values[i * columns + j]);
		}

		scanf("\n");
	}


	source.pred = NULL;
	source.edges = NULL;

	sink.pred = NULL;
	sink.edges = NULL;


	for(i = 0; i < lines; i++){
		for(j = 0; j < columns; j++){
			scanf("%d ", &tmp);

			graph[i * lines + j].bfs_count = 0;
			graph[i * lines + j].pred = NULL;
			graph[i * lines + j].edges = NULL;

			if(tmp_P_values[i * lines + j] != tmp){
				EDGE e;

				if(tmp_P_values[i * lines + j] > tmp){
					e.origin_x = SOURCE_X;
					e.origin_y = SOURCE_Y;

					e.dest_x = j;
					e.dest_y = i;

					e.flux = tmp;
					e.cap_res = tmp_P_values[i * lines + j] - tmp;
				}
				else if(tmp > tmp_P_values[i * lines + j]){
					e.origin_x = j;
					e.origin_y = i;

					e.dest_x = SINK_X;
					e.dest_y = SINK_Y;

					e.flux = tmp_P_values[i * lines + j];
					e.cap_res = tmp - tmp_P_values[i * lines + j];
				}


				source.edges = enqueue(&e, source.edges);
				graph[i * lines + j].edges = enqueue(&e, graph[i * lines + j].edges);

				flow += e.flux;
			}
			else{
				flow += tmp;
			}
		}

		scanf("\n");
	}

	scanf("\n");


	free(tmp_P_values);


	for(i = 0; i < lines; i++){
		for(j = 0; j < columns - 1; j++){
			scanf("%d ", &tmp);

			if(tmp != 0){
				EDGE e1, e2;

				e1.origin_x = j;
				e1.origin_y = i;

				e1.dest_x = j + 1;
				e1.dest_y = i;

				e1.flux = 0;
				e1.cap_res = tmp;


				e2.origin_x = j + 1;
				e2.origin_y = i;

				e2.dest_x = j;
				e2.dest_y = i;

				e2.flux = 0;
				e2.cap_res = tmp;

				graph[i * lines + j].edges = enqueue(&e1, graph[i * lines + j].edges);
				graph[i * lines + j].edges = enqueue(&e2, graph[i * lines + j].edges);

				graph[i * lines + j + 1].edges = enqueue(&e1, graph[i * lines + j + 1].edges);
				graph[i * lines + j + 1].edges = enqueue(&e2, graph[i * lines + j + 1].edges);
			}
		}

		scanf("\n");
	}


	for(i = 0; i < lines - 1; i++){
		for(j = 0; j < columns; j++){
			scanf("%d ", &tmp);

			if(tmp != 0){
				EDGE e1, e2;

				e1.origin_x = j;
				e1.origin_y = i;

				e1.dest_x = j;
				e1.dest_y = i + 1;

				e1.flux = 0;
				e1.cap_res = tmp;


				e2.origin_x = j;
				e2.origin_y = i + 1;

				e2.dest_x = j;
				e2.dest_y = i;

				e2.flux = 0;
				e2.cap_res = tmp;

				graph[i * lines + j].edges = enqueue(&e1, graph[i * lines + j].edges);
				graph[i * lines + j].edges = enqueue(&e2, graph[i * lines + j].edges);

				graph[(i + 1) * lines + j].edges = enqueue(&e1, graph[(i + 1) * lines + j].edges);
				graph[(i + 1) * lines + j].edges = enqueue(&e2, graph[(i + 1) * lines + j].edges);
			}
		}

		scanf("\n");
	}



	return 0;
}



 /********************************************\
|                                              |
|                 Edmonds-Karp                 |
|                                              |
 \********************************************/



/*typedef struct edge {
	int origin_x, origin_y;
	int dest_x, dest_y;

	/* flux denotes a backwards edge */
	/*int flux;
	/* cap_res denotes a forwards edge */
	/*int cap_res;
} EDGE;*/



 /********************************************\
|                                              |
|             Breadth-First Search             |
|                                              |
 \********************************************/

int bfs(){
	bfs_count++;

	QUEUE *Q = source.edges;

	source.bfs_count = bfs_count;

	EDGE *tmp;
	VERTEX *v;

	while(Q != NULL && Q->edge->dest_x != SINK_X){
		tmp = Q->edge;

		/* Forwards */
		if(tmp->cap_res > 0){
			v = &graph[tmp->dest_x * lines + tmp->dest_y];
		}

		/* Backwards */
		if(tmp->flux > 0){
			v = &graph[tmp->origin_x * lines + tmp->origin_y];
		}

		Q = Q->next;


	}
}



 /********************************************\
|                                              |
|               Queue Operations               |
|                                              |
 \********************************************/

QUEUE* enqueue(EDGE *e, QUEUE *q){

	QUEUE *tmp = (QUEUE*)malloc(sizeof(QUEUE));

	tmp->edge = e;
	tmp->next = NULL;
	tmp->prev = NULL;

	return enqueueQ(tmp, q);
}

QUEUE* enqueueQ(QUEUE *e, QUEUE *q){

	if(q != NULL){
		if(q->prev != NULL){
			q->prev->next = e;
		}

		q->prev = e->prev;

		return q;
	}

	return e;
}



 /********************************************\
|                                              |
|                    Colors                    |
|                                              |
 \********************************************/

void printColors(){
	int i, j;

	for(i = 0; i < lines; i++){
		for(j = 0; j < columns; j++){
			
		}
	}
}

