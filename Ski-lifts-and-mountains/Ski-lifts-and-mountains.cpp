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

	// Checking whether our left or child element
	// is at right index or not to avoid index error
	if (left >= h->size || left < 0)
		left = -1;
	if (right >= h->size || right < 0)
		right = -1;

	// store left or right element in min if
	// any of these is smaller that its parent
	if (left != -1 && h->arr[left].dist < h->arr[index].dist)
		min = left;
	if (right != -1 && h->arr[right].dist < h->arr[min].dist)
		min = right;

	// Swapping the nodes
	if (min != index) {
		HeapNode temp = h->arr[min];
		h->arr[min] = h->arr[index];
		h->arr[index] = temp;

		heapify(h, min);
	}
}

HeapNode extractMin(heap* h){
	HeapNode deleteItem = {-2,-1,-37};
	// Checking if the heap is empty or not
	if (h->size == 0) {
		printf("\nHeap id empty.");
		return deleteItem;
	}

	// Store the node in deleteItem that
	// is to be deleted.
	deleteItem = h->arr[0];

	// Replace the deleted node with the last node
	h->arr[0] = h->arr[h->size - 1];
	// Decrement the size of heap
	h->size--;
	heapify(h, 0);
	return deleteItem;
}


void insert(heap* h, HeapNode data)
{
	if (h->size < h->capacity) {
		h->arr[h->size] = data;
		insertHelper(h, h->size);
		h->size++;
	}
}


Node map[MAX_HEIGHT][MAX_WIDTH];
int distances[MAX_HEIGHT][MAX_WIDTH];


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


void addEdge(Node map[][MAX_WIDTH], heap* queue, int y,int x, int vy, int vx, int width, int height) {
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


void addEgdesToQueue(Node map[][MAX_WIDTH], heap* queue, int x, int y, int width, int height) {
	int vx = x;
	int vy = y-1;
	addEdge(map, queue,y,x, vy, vx, width,height); //x y-1
	vx++;
	vy++;
	addEdge(map, queue, y, x, vy, vx, width, height);//x+1 y	
	vx--;
	vy++;
	addEdge(map, queue, y, x, vy, vx, width, height);//x y+1
	vy--;
	vx--;
	addEdge(map, queue, y, x, vy, vx, width, height);//x-1 y
}



int dijkstra(Node map[][MAX_WIDTH], int sx,int sy ,int ex,int ey, int width, int height) {
	heap* pq = createHeap(width * height);
	distances[sy][sx] = 0;
	HeapNode hn = { 0,sx,sy };
	insert(pq, hn);
	while (true) {
		 hn = extractMin(pq);
		if (hn.dist != distances[hn.y][hn.x]) continue;
		if (hn.x == ex && hn.y == ey) {
			return hn.dist;
		}// wynik
		addEgdesToQueue(map, pq,hn.x,hn.y, width, height);		
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

