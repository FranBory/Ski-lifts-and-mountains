#include <iostream>
#include <cstdlib>
using namespace std;

#define MAX_WIDTH  2003   
#define MAX_HEIGHT 2003   


typedef struct Lift {
	int end_row;
	int end_col;
	int cost;
	int time;
	struct Lift* next_lift;
} Lift;

typedef struct {
	int height;
	int lift_count;
	Lift* lifts;
} Node;

typedef struct Queue {
	int x;
	int y;
	int priority;
	struct Queue* next;
	struct Queue* prev;
}Queue;

Node map[MAX_HEIGHT][MAX_WIDTH];
int distances[MAX_HEIGHT][MAX_WIDTH];

Queue* pushQueue(Queue* head, int x,int y, int prio) {
	Queue* node = (Queue*)malloc(sizeof * node);
	if (!node) return head;
	node->x = x;
	node->y = y;
	node->priority = prio;
	node->next = node->prev = NULL;
	if (!head)                          
		return node;
	if (prio <= head->priority) {
		node->next = head;
		head->prev = node;
		return node;                     
	}
	Queue* cur = head;
	while (cur->next && cur->next->priority < prio) cur = cur->next;
	node->next = cur->next;
	node->prev = cur;
	if (cur->next) cur->next->prev = node;
	cur->next = node;
	return head;                         
}

Queue* pop(Queue* head, int* x_out, int* y_out, int* prio_out) {
	Queue* node = head;
	*x_out = node->x;
	*y_out = node->y;
	*prio_out = node->priority;
	head = head->next;
	if (head) head->prev = NULL;
	free(node);
	return head;
}


//void addLiftToNode(Node* node,Lift* lift) {
//	if (node->lift_count == 0) {
//		lift->next_lift = nullptr;
//		node->lifts = lift;
//	}
//	else {
//		lift->next_lift = node->lifts;
//		node->lifts = lift;
//	}
//	node->lift_count++;
//}



int costCount(Node* B, Node* A) { // przejscie z B na A
	int cost;
	if (A->height <= B->height) {
		cost = 1;
	}
	else {
		cost =  (A->height) - (B->height) + 1;
	}
	return cost;
}


Queue* addEdge(Node map[][MAX_WIDTH], Queue* queue, int y,int x, int vy, int vx, int width, int height) {
	if (vy < 0 || vx < 0 || vy >= height || vx >= width) return queue;
	else {
		int cost = costCount(&map[y][x], &map[vy][vx]);
		int newDist = distances[y][x] + cost;
		if (newDist < distances[vy][vx]) {
			distances[vy][vx] = newDist;
			queue = pushQueue(queue, vx, vy, newDist);
		}
		return queue;
	}
}
static void dumpQueue(const char* tag, const Queue* head)
{
	printf("[queue %s] ", tag);
	for (const Queue* p = head; p; p = p->next)
		printf("(%d:%d) ", p->x, p->priority);
	puts("");
}

Queue* addEgdesToQueue(Node map[][MAX_WIDTH], Queue* queue, int x, int y, int width, int height) {
	int vx = x;
	int vy = y-1;
	queue = addEdge(map, queue,y,x, vy, vx, width,height); //x y-1
	vx++;
	vy++;
	queue = addEdge(map, queue, y, x, vy, vx, width, height);//x+1 y	
	vx--;
	vy++;
	queue = addEdge(map, queue, y, x, vy, vx, width, height);//x y+1
	vy--;
	vx--;
	queue = addEdge(map, queue, y, x, vy, vx, width, height);//x-1 y
	return queue;
}



int dijkstra(Node map[][MAX_WIDTH], int sx,int sy ,int ex,int ey, int width, int height) {
	Queue* pq = nullptr;
	distances[sy][sx] = 0;
	pq = pushQueue(pq, sx,sy, 0);
	while (true) {
		int x,y, dist;
		pq = pop(pq, &x, &y, &dist);
		if (dist != distances[y][x]) continue;
		if (x == ex && y == ey) {
			return dist;
		}// wynik
		pq = addEgdesToQueue(map, pq,x,y, width, height);		
		//dumpQueue("after  push", pq);
	}
	return -2137;
}



int main() {

	int width, height;
	int start_col, start_row;
	int end_col, end_row;
	int lift_numb;
	
	scanf_s("%d %d", &width, &height);
	scanf_s("%d %d", &start_col, &start_row);
	scanf_s("%d %d", &end_col, &end_row);
	scanf_s("%d", &lift_numb);

	for (int i = 0; i < lift_numb; i++) {
		int time,cost;
		scanf_s("%d %d", &start_col, &start_row);
		scanf_s("%d %d", &end_col, &end_row);
		scanf_s("%d %d", &time, &cost);
		Lift* lift = (Lift*)malloc(sizeof(Lift));
		//addLiftToNode(&map[start_col][start_row], lift);
	}


	for (int r = 0; r < height; ++r) {
		for (int c = 0; c < width; ++c) {
			int input;
			scanf_s("%d", &input);
			map[r][c].height = input;
			distances[r][c] = INT_MAX;
		}
	}

	/*for (int r = 0; r < height; ++r) {
		for (int c = 0; c < width; ++c) {
			if (r==start_row && c==start_col)
			{
				printf("S ");
			}
			else if (r == end_row && c == end_col)
			{
				printf("E ");
			}
			else printf("%d ", distances[r][c]);
		}
		cout << endl;
	}*/

	int oby_dobry_wynik = dijkstra(map, start_col, start_row,end_col,end_row, width, height);

	cout << oby_dobry_wynik;

	
	
	return 0;
}

