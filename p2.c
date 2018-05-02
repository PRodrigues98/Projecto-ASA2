#include <stdio.h>
#include <stdlib.h>


#define SOURCE_X -2
#define SOURCE_Y -2
#define SINK_X -1
#define SINK_Y -1


typedef struct vertex VERTEX;
typedef struct edge EDGE;
typedef struct stack STACK;
typedef struct queue QUEUE;
typedef struct queue_elem QUEUE_ELEM;


typedef struct stack {
	EDGE *edge;
	STACK *next;
} STACK;

typedef struct vertex {
	EDGE *pred;

	int bfs_count;

	STACK *edges;
} VERTEX;

typedef struct edge {
	int origin_x, origin_y;
	int dest_x, dest_y;

	/* flux denotes a backwards edge */
	int flux;
	/* cap_res denotes a forwards edge */
	int cap_res;
} EDGE;



void edmondsKarp();
int bfs();

STACK* push(EDGE *e, STACK *q);

void printColors();



int flow = 0, lines, columns, bfs_count = 0;
VERTEX source, sink;
VERTEX *graph;



int main(){
	
	int i, j, tmp;
	EDGE *e1;
	EDGE *e2;

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
	source.bfs_count = 0;

	sink.pred = NULL;
	sink.edges = NULL;
	source.bfs_count = 0;


	for(i = 0; i < lines; i++){
		for(j = 0; j < columns; j++){
			scanf("%d ", &tmp);

			graph[i * columns + j].bfs_count = 0;
			graph[i * columns + j].pred = NULL;
			graph[i * columns + j].edges = NULL;

			if(tmp_P_values[i * columns + j] != tmp){

				e1 = (EDGE*)malloc(sizeof(EDGE));

				if(tmp_P_values[i * columns + j] > tmp){
					e1->origin_x = SOURCE_X;
					e1->origin_y = SOURCE_Y;

					e1->dest_x = i;
					e1->dest_y = j;

					e1->flux = tmp;
					e1->cap_res = tmp_P_values[i * columns + j] - tmp;

					source.edges = push(e1, source.edges);
				}
				else{
					e1->origin_x = i;
					e1->origin_y = j;

					e1->dest_x = SINK_X;
					e1->dest_y = SINK_Y;

					e1->flux = tmp_P_values[i * columns + j];
					e1->cap_res = tmp - tmp_P_values[i * columns + j];

					sink.edges = push(e1, sink.edges);
				}

				graph[i * columns + j].edges = push(e1, graph[i * columns + j].edges);

				flow += e1->flux;
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
				e1 = (EDGE*)malloc(sizeof(EDGE));
				e2 = (EDGE*)malloc(sizeof(EDGE));

				e1->origin_x = i;
				e1->origin_y = j;

				e1->dest_x = i;
				e1->dest_y = j + 1;

				e1->flux = 0;
				e1->cap_res = tmp;


				e2->origin_x = i;
				e2->origin_y = j + 1;

				e2->dest_x = i;
				e2->dest_y = j;

				e2->flux = 0;
				e2->cap_res = tmp;

				graph[i * columns + j].edges = push(e1, graph[i * columns + j].edges);
				graph[i * columns + j].edges = push(e2, graph[i * columns + j].edges);

				graph[i * columns + j + 1].edges = push(e1, graph[i * columns + j + 1].edges);
				graph[i * columns + j + 1].edges = push(e2, graph[i * columns + j + 1].edges);
			}
		}

		scanf("\n");
	}


	for(i = 0; i < lines - 1; i++){
		for(j = 0; j < columns; j++){
			scanf("%d ", &tmp);

			if(tmp != 0){
				e1 = (EDGE*)malloc(sizeof(EDGE));
				e2 = (EDGE*)malloc(sizeof(EDGE));

				e1->origin_x = i;
				e1->origin_y = j;

				e1->dest_x = i + 1;
				e1->dest_y = j;

				e1->flux = 0;
				e1->cap_res = tmp;


				e2->origin_x = i + 1;
				e2->origin_y = j;

				e2->dest_x = i;
				e2->dest_y = j;

				e2->flux = 0;
				e2->cap_res = tmp;

				graph[i * columns + j].edges = push(e1, graph[i * columns + j].edges);
				graph[i * columns + j].edges = push(e2, graph[i * columns + j].edges);

				graph[(i + 1) * columns + j].edges = push(e1, graph[(i + 1) * columns + j].edges);
				graph[(i + 1) * columns + j].edges = push(e2, graph[(i + 1) * columns + j].edges);
			}
		}

		scanf("\n");
	}

	edmondsKarp();

	printf("%d\n\n", flow);

	printColors();

	return 0;
}





 /********************************************\
|                                              |
|                 Edmonds-Karp                 |
|                                              |
 \********************************************/

void edmondsKarp(){
	EDGE *e;
	STACK *s = NULL, *tmp = NULL;
	VERTEX *u;
	int minCapRes = 0;
	int cur_x, cur_y;


	while(bfs() != 0){

		e = sink.pred;

		u = &graph[e->origin_x * columns + e->origin_y];

		cur_x = e->origin_x;
		cur_y = e->origin_y;

		minCapRes = e->cap_res;

		s = push(e, s);

		e = u->pred;

		s = push(e, s);

		while(e->origin_x != SOURCE_X){

			/* go to origin */
			if(e->dest_x == cur_x && e->dest_y == cur_y){
				if(e->cap_res < minCapRes){
					minCapRes = e->cap_res;
				}

				u = &graph[e->origin_x * columns + e->origin_y];

				cur_x = e->origin_x;
				cur_y = e->origin_y;
			}
			/* go to destination */
			else{ 
				if(e->flux < minCapRes){
					minCapRes = e->flux;
				}

				u = &graph[e->dest_x * columns + e->dest_y];

				cur_x = e->dest_x;
				cur_y = e->dest_y;
			}

			u = &graph[cur_x * columns + cur_y];

			e = u->pred;

			s = push(e, s);
		}

		e = s->edge;

		e->cap_res -= minCapRes;
		e->flux += minCapRes;

		cur_x = e->dest_x;
		cur_y = e->dest_y;

		flow += minCapRes;

		tmp = s;
		s = s->next;
		free(tmp);


		while(s != NULL){
			
			e = s->edge;

			/* edge from origin to destination */
			if(e->origin_x == cur_x && e->origin_y == cur_y){
				e->cap_res -= minCapRes;
				e->flux += minCapRes;

				cur_x = e->dest_x;
				cur_y = e->dest_y;
			}
			/* edge from destination to origin */
			else{
				e->cap_res += minCapRes;
				e->flux -= minCapRes;

				cur_x = e->origin_x;
				cur_y = e->origin_y;
			}



			tmp = s;
			s = s->next;
			free(tmp);
		}
	}
}



 /********************************************\
|                                              |
|             Breadth-First Search             |
|                                              |
 \********************************************/

int bfs(){
	bfs_count++;

	int *q = (int*)malloc(sizeof(int) * (lines * columns + 2));

	int beg = 0, end = 0;

	q[end++] = SOURCE_X;

	source.bfs_count = bfs_count;

	EDGE *e;
	VERTEX *v, *u;
	STACK *s;

	while(beg < end){

		if(q[beg] == SOURCE_X){
			u = &source;
		}
		else if(q[beg] == SINK_X){
			u = &sink; /* Not supposed to be possible */
		}
		else{
			u = &graph[q[beg]];
		}

		s = u->edges;

		while(s != NULL){

			e = s->edge;

			if(e->dest_x == SINK_X){
				if(e->cap_res > 0){
					sink.pred = e;

					sink.bfs_count = bfs_count;

					free(q);

					return 1;
				}
				else{
					s = s->next;

					continue;
				}
			}

			if(e->origin_x == SOURCE_X || (e->origin_x == (int)(q[beg] / columns) && e->origin_y == (q[beg] % columns))){
		
				v = &graph[e->dest_x * columns + e->dest_y];

				/* Forwards */
				if(v->bfs_count != bfs_count && e->cap_res > 0){

					q[end++] = e->dest_x * columns + e->dest_y;

					v->bfs_count = bfs_count;

					v->pred = e;
				}
			}
			else{

				v = &graph[e->origin_x * columns + e->origin_y];

				/* Backwards */
				if(v->bfs_count != bfs_count && e->flux > 0){

					q[end++] = e->origin_x * columns + e->origin_y;

					v->bfs_count = bfs_count;
					v->pred = e;
				}
			}
			

			s = s->next;
		}

		beg++;
	}

	free(q);

	return 0;
}



 /********************************************\
|                                              |
|               Stack Operations               |
|                                              |
 \********************************************/

STACK* push(EDGE *e, STACK *q){

	STACK *tmp = (STACK*)malloc(sizeof(STACK));

	tmp->edge = e;
	tmp->next = q;

	return tmp;
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
			if(graph[i * columns + j].bfs_count != bfs_count){
				printf("%c ", 'P');
			}
			else{
				printf("%c ", 'C');
			}
		}
		printf("\n");
	}
}

