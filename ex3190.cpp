#include <stdio.h>
#define MAX 100

typedef struct {
	int hy, hx;
	int ty, tx;
	int d;
}SNAKE;

typedef struct {
	int x;
	char c;
}CMD;

int N, K, L;
int map[MAX + 2][MAX + 2];
CMD cmd[MAX + 2];
SNAKE snake;

int dy[] = { -1,0,+1,0 };
int dx[] = { 0,+1,0,-1 };

int Solve() {
	int cmdIdx = 1;
	int time = 0;

	while (1) {
		int ny = snake.hy + dy[snake.d];
		int nx = snake.hx + dx[snake.d];
	
		if (ny < 1 || ny > N || nx < 1 || nx > N || map[ny][nx] < 0) break;

		if (map[ny][nx] == 0) { // 빈 공간
			map[ny][nx] = map[snake.hy][snake.hx] - 1;
			snake.hy = ny;
			snake.hx = nx;

			for (int dir = 0; dir < 4; dir++) {
				int yy = snake.ty + dy[dir];
				int xx = snake.tx + dx[dir];

				if (yy < 1 || yy > N || xx < 1 || xx > N) continue;
				if (map[yy][xx] >= 0) continue;
				if (map[yy][xx] == map[snake.ty][snake.tx] - 1) {
					map[snake.ty][snake.tx] = 0;
					snake.ty = yy;
					snake.tx = xx;
					break;
				}
			}
		}
		else if (map[ny][nx] == 1) { // 사과
			map[ny][nx] = map[snake.hy][snake.hx] - 1;
			snake.hy = ny;
			snake.hx = nx;
		}

		time++;
		if (cmd[cmdIdx].x == time) {
			if (cmd[cmdIdx].c == 'L') {
				snake.d--;
				if (snake.d == -1) snake.d = 3;
			}
			else if (cmd[cmdIdx].c == 'D') {
				snake.d++;
				if (snake.d ==  4) snake.d = 0;
			}
			cmdIdx++;
		}
	}
	return time + 1;
}

int main() {
	scanf("%d", &N);
	
	scanf("%d", &K);
	for (int i = 1; i <= K; i++) {
		int y, x;
		scanf("%d %d", &y, &x);
		map[y][x] = 1;
	}

	scanf("%d", &L);
	for (int i = 1; i <= L; i++) {
		scanf("%d %c ", &cmd[i].x, &cmd[i].c);
	}

	map[1][1] = -1;
	snake = { 1,1,1,1,1 };
	printf("%d\n", Solve());
}
