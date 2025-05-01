#include <iostream>
using namespace std;

#define MAX_WIDTH  2001   
#define MAX_HEIGHT 2001   

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


void addLiftToNode(Node* node,Lift* lift) {
	if (node->lift_count == 0) {
		lift->next_lift = nullptr;
		node->lifts = lift;
	}
	else {
		lift->next_lift = node->lifts;
		node->lifts = lift;
	}
	node->lift_count++;
}


int costCount(Node* B, Node* A) { // przejscie z B na A
	if (A->height <= B->height) return 1;
	else return (A->height) - (B->height) + 1;
}

Node map[MAX_HEIGHT][MAX_WIDTH];
Node nodePrevNode[MAX_HEIGHT * MAX_WIDTH][2];
int distances[MAX_HEIGHT * MAX_WIDTH];


void dijkstra(int w, int h, Node* start) {
	
}

int main() {
	for (int r = 0; r < MAX_HEIGHT; ++r) {
		for (int c = 0; c < MAX_WIDTH; ++c) {
			map[r][c].lift_count = 0;
		}
	}
	for (int i = 0; i < MAX_HEIGHT*MAX_WIDTH; i++) {
		distances[i] = INT_MAX;
	}

	int width, height;
	int start_col, start_row;
	int end_col, end_row;
	int lift_numb;
	//TODO: wyciagi
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
		addLiftToNode(&map[start_col][start_row], lift);
	}

	for (int r = 0; r < height; ++r) {
		for (int c = 0; c < width; ++c) {
			int input;
			scanf_s("%d", &input);
			map[r][c].height = input;
		}
	}
	distances[start_row * width + start_col] = 0;

	
	

	printf("0");

	return 0;
}

