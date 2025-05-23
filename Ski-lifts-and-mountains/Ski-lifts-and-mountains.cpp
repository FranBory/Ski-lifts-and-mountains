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

// kod na kopiec zostal napisany na podstawie kodu z tego artykułu
//https://www.geeksforgeeks.org/c-program-to-implement-min-heap/

struct HeapNode {
	int dist;
	int x;
	int y;
};
struct Heap {
	HeapNode* arr;
	int size;
	int capacity;
};

typedef struct Heap heap;

heap* createHeap(int capacity) {
	heap* h = (heap*)malloc(sizeof(heap));
	if (h == NULL) {
		printf("Memory error");
		return NULL;
	}
	h->size = 0;
	h->capacity = capacity;
	h->arr = (HeapNode*)malloc(capacity * sizeof(HeapNode));
	return h;
}

void insertHelper(heap* h, int index) {
	int parent = (index - 1) / 2;

	if (h->arr[parent].dist > h->arr[index].dist) {
		HeapNode temp = h->arr[parent];
		h->arr[parent] = h->arr[index];
		h->arr[index] = temp;

		insertHelper(h, parent);
	}
}

void heapify(heap* h, int index)
{
	int left = index * 2 + 1;
	int right = index * 2 + 2;
	int min = index;

	if (left >= h->size || left < 0)
		left = -1;
	if (right >= h->size || right < 0)
		right = -1;
	
	if (left != -1 && h->arr[left].dist < h->arr[index].dist)
		min = left;
	if (right != -1 && h->arr[right].dist < h->arr[min].dist)
		min = right;
	
	if (min != index) {
		HeapNode temp = h->arr[min];
		h->arr[min] = h->arr[index];
		h->arr[index] = temp;

		heapify(h, min);
	}
}

HeapNode extractMin(heap* h){
	HeapNode deleteItem = {-2,-1,-37};

	if (h->size == 0) {
		printf("\nHeap id empty.");
		return deleteItem;
	}

	deleteItem = h->arr[0];
	h->arr[0] = h->arr[h->size - 1];
	h->size--;
	heapify(h, 0);
	return deleteItem;
}

void insert(heap* h, HeapNode data) {
	if (h->size < h->capacity) {
		h->arr[h->size] = data;
		insertHelper(h, h->size);
		h->size++;
	}
}

int costCount(Node* B, Node* A) { 
	int cost;
	if (A->height <= B->height) {
		cost = 1;
	}
	else {
		cost =  (A->height) - (B->height) + 1;
	}
	return cost;
}


void addEdge(int** distances,Node** map, heap* queue, int y,int x, int vy, int vx, int width, int height) {
	if (vy < 0 || vx < 0 || vy >= height || vx >= width) return;
	else {
		int cost = costCount(&map[y][x], &map[vy][vx]);
		int newDist = distances[y][x] + cost;
		if (newDist < distances[vy][vx]) {
			distances[vy][vx] = newDist;
			HeapNode node = { newDist, vx,vy };
			insert(queue, node);
		}
	}
}

int liftCost(Lift* lf, int curT) {
	int wait = (lf->time - (curT % lf->time)) % lf->time;
	return wait + lf->cost;
}

void addEdgeLifts(Node** map, int** dist, Heap* pq, int ux, int uy, int width, int height){
	for (Lift* lf = map[uy][ux].lifts; lf; lf = lf->next_lift) {

		int newd = dist[uy][ux] + liftCost(lf, dist[uy][ux]);

		int vx = lf->end_col, vy = lf->end_row;
		if (vy < 0 || vx < 0 || vy >= height || vx >= width) continue;

		if (newd < dist[vy][vx]) {
			dist[vy][vx] = newd;
			HeapNode n = { newd, vx, vy };
			insert(pq, n);
		}
	}
}
void addEgdesToQueue(int** distances,Node** map, heap* queue, int x, int y, int width, int height) {
	int vx = x;
	int vy = y-1;
	addEdge(distances,map, queue,y,x, vy, vx, width,height); 
	vx++;
	vy++;
	addEdge(distances, map, queue, y, x, vy, vx, width, height);
	vx--;
	vy++;
	addEdge(distances, map, queue, y, x, vy, vx, width, height);
	vy--;
	vx--;
	addEdge(distances, map, queue, y, x, vy, vx, width, height);
	addEdgeLifts(map, distances, queue, x, y, width, height);
}
void freeHeap(heap* h) {
	if (!h) return;
	free(h->arr);
	free(h);
}
int dijkstra(int** distances, Node** map, int sx,int sy ,int ex,int ey, int width, int height) {
	heap* pq = createHeap(width * height);
	distances[sy][sx] = 0;
	HeapNode hn = { 0,sx,sy };
	insert(pq, hn);
	while (true) {
		 hn = extractMin(pq);
		if (hn.dist != distances[hn.y][hn.x]) continue;
		if (hn.x == ex && hn.y == ey) {
			freeHeap(pq);
			return hn.dist;
		}
		addEgdesToQueue(distances,map, pq,hn.x,hn.y, width, height);		
	}
	return -2;
}

void addLiftToNode(Node* node, Lift* lf) {
	lf->next_lift = node->lifts;
	node->lifts = lf;
}

void initMap(int H, int W, Node*** map_out,int*** dist_out) {
	size_t bytes_map = sizeof(Node*) * H          
		+ sizeof(Node) * H * W;     

	Node** map = (Node**)malloc(bytes_map);
	if (!map) { perror("malloc map"); exit(EXIT_FAILURE); }

	Node* map_data = (Node*)(map + H);             

	for (int y = 0; y < H; ++y)
		map[y] = map_data + y * W;                 
	
	size_t bytes_dist = sizeof(int*) * H + sizeof(int) * H * W;

	int** dist = (int**)malloc(bytes_dist);
	if (!dist) { perror("malloc dist"); exit(EXIT_FAILURE); }

	int* dist_data = (int*)(dist + H);

	for (int y = 0; y < H; ++y)
		dist[y] = dist_data + y * W;

	
	for (int y = 0; y < H; ++y)
		for (int x = 0; x < W; ++x) {
			map[y][x].height = INT_MAX;
			map[y][x].lifts = NULL;
			dist[y][x] = INT_MAX;
		}
	*map_out = map;
	*dist_out = dist;
}

void freeMap(Node** map, int** dist) {
	free(map);    
	free(dist);   
}
void freeAllLifts(Node** map, int height, int width) {
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			Lift* cur = map[y][x].lifts;
			while (cur) {
				Lift* next = cur->next_lift;
				free(cur);
				cur = next;
			}
			map[y][x].lifts = nullptr;
		}
	}
}

int main() {
	int width, height;
	int start_col, start_row;
	int end_col, end_row;
	int lift_numb;
	Node** map;
	int** dist;
	
	scanf_s("%d %d", &width, &height);
	scanf_s("%d %d", &start_col, &start_row);
	scanf_s("%d %d", &end_col, &end_row);
	scanf_s("%d", &lift_numb);

	initMap(height, width, &map, &dist);
	
	for (int i = 0; i < lift_numb; i++) {
		Lift* lift = (Lift*)malloc(sizeof(Lift));
		int r, c;
		scanf_s("%d %d", &c, &r);
		scanf_s("%d %d", &(lift->end_col), &(lift->end_row));
		scanf_s("%d %d", &(lift->cost), &(lift->time));
		addLiftToNode(&map[r][c], lift);
	}

	for (int r = 0; r < height; ++r) {
		for (int c = 0; c < width; ++c) {
			int input;
			scanf_s("%d", &input);
			map[r][c].height = input;
			dist[r][c] = INT_MAX;
		}
	}
	int oby_dobry_wynik = dijkstra(dist, map, start_col, start_row,end_col,end_row, width, height);
	cout << oby_dobry_wynik;
	freeAllLifts(map, height, width);
	freeMap(map, dist);
	return 0;
}

