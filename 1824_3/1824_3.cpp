#include <stdio.h>

#define MAX_QUEUE?? (1<<5)

enum DIRECTION {
	north,
	east,
	south,
	west
};

enum STATE {
	normal,
	end,
	quetion
};

typedef struct info {
	int x;
	int y;
	int dir;
	int num;
}Info;

int R, C;
char arr[20][20];
int visited[20][20][16];
int dir_x[4] = { 0, 1, 0, -1 };
int dir_y[4] = { -1, 0, 1, 0 };
Info queue[MAX_QUEUE];
int front, rear;

void push(Info data) {
	if ((rear + 1) % MAX_QUEUE == front) {
		printf("full\n");
		return;
	}

	queue[rear] = data;
	rear = (rear + 1) % MAX_QUEUE;
}

Info pop(void) {
	Info data;

	data.dir = data.num = data.x = data.y = 0;

	if (front == rear) {
		printf("empty\n");
		return data;
	}

	data = queue[front];
	front = (front + 1) % MAX_QUEUE;

	return data;
}

Info nextLocation(Info data, int dir) {
	data.x = (data.x + dir_x[dir]) % C;
	if (data.x < 0) data.x = C - 1;

	data.y = (data.y + dir_y[dir]) % R;
	if (data.y < 0) data.y = R - 1;

	return data;
}

Info run(Info temp, int * result) {
	*result = normal;

	switch (arr[temp.y][temp.x]) {
	case '<':
		temp.dir = west;
		break;
	case '>':
		temp.dir = east;
		break;
	case '^':
		temp.dir = north;
		break;
	case 'v':
		temp.dir = south;
		break;
	case '_':
		if (temp.num == 0) temp.dir = east;
		else temp.dir = west;
		break;
	case '|':
		if (temp.num == 0) temp.dir = south;
		else temp.dir = north;
		break;
	case '?':
		*result = quetion;
		break;
	case '.':
		break;
	case '@':
		*result = end;
		break;
	case '+':
		temp.num++;
		if (temp.num > 15) temp.num = 0;
		break;
	case '-':
		temp.num--;
		if (temp.num < 0) temp.num = 15;
		break;
	default:
		temp.num = arr[temp.y][temp.x] - '0';
		break;
	}

	return temp;
}

int checkRecur(Info temp) {
	if (visited[temp.y][temp.x][temp.num] == temp.dir) return 1;
	visited[temp.y][temp.x][temp.num] = temp.dir;
	return 0;
}

int solve(void) {
	Info temp, next;
	int result;

	temp.x = temp.y = 0;
	temp.dir = east;
	temp.num = 0;

	push(temp);

	while (front != rear) {
		temp = pop();

		if (checkRecur(temp) == 1) continue;

		temp = run(temp, &result);

		if (result == end) return 1;
		else if (result == quetion) {
			for (int dir = 0; dir < 4; dir++) {
				next = nextLocation(temp, dir);
				next.dir = dir;

				if ((rear + 1) % MAX_QUEUE == front) return 0;
				push(next);
			}
		}
		else {
			temp = nextLocation(temp, temp.dir);

			if ((rear + 1) % MAX_QUEUE == front) return 0;
			push(temp);
		}
	}

	return 0;
}

int deleteCheck(Info * temp) {
	switch (arr[temp->y][temp->x]) {
	case '<':
		temp->dir = east;
		break;
	case '>':
		temp->dir = west;
		break;
	case '^':
		temp->dir = south;
		break;
	case 'v':
		temp->dir = north;
		break;
	case '_':
		return -1;
	case '|':
		return -1;
	case '@':
		return -1;
	case '?':
		return 1;
	}

	return 0;
}

void deleteQuetion(int x, int y) {
	Info temp, next;
	int r;

	temp.x = x;
	temp.y = y;
	temp.num = 0;
	for (int dir = 0; dir < 4; dir++) {
		next = nextLocation(temp, dir);
		next.dir = dir;
		push(next);
	}

	while (front != rear) {
		next = temp = pop();

		r = deleteCheck(&temp);

		if ((next.dir + 2) % 4 == temp.dir) continue;

		if (r == 0) {
			temp = nextLocation(temp, temp.dir);
			push(temp);
		}
		else if (r == 1) {
			arr[temp.y][temp.x] = '@';

			for (int dir = 0; dir < 4; dir++) {
				next = nextLocation(temp, dir);
				next.dir = dir;
				push(next);
			}
		}
	}

	front = rear = 0;
}

int main(void) {
	int T, testcase;
	int x, y, flag = 0;

	scanf("%d", &T);

	for (testcase = 1; testcase <= T; testcase++) {
		scanf("%d%d", &R, &C);
		front = rear = 0;

		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				scanf(" %c", &arr[i][j]);
				for (int k = 0; k <= 15; k++) visited[i][j][k] = -1;

				if (arr[i][j] == '@') {
					x = j;
					y = i;
					flag = 1;
				}
			}
		}

		//if(flag == 1) deleteQuetion(x, y);
		//else {
		//? printf("#%d NO\n", testcase);
		//? continue;
		//}

		printf("#%d ", testcase);
		if (solve() == 1) printf("YES\n");
		else printf("NO\n");
	}

	return 0;
}