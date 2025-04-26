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

Node map[MAX_HEIGHT][MAX_WIDTH];

int main() {

	for (int r = 0; r < MAX_HEIGHT; ++r) {
		for (int c = 0; c < MAX_WIDTH; ++c) {
			map[r][c].lift_count = 0;
		}
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

	printf("0");

	return 0;
}

