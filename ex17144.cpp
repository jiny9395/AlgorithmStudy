// 17144. 미세먼지 안녕!
#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
#define MAX 50
using namespace std;

typedef struct {
	int y, x;
}POS;

int R, C, T;
int A[MAX + 2][MAX + 2];
int B[MAX + 2][MAX + 2];

int dy[] = { 0,0,-1,+1 };
int dx[] = { -1,+1,0,0 };

vector<POS> cleaner;

void spreadDust() {
	memset(B, 0, sizeof(B));

	for (int y = 1; y <= R; y++) {
		for (int x = 1; x <= C; x++) {
			if (A[y][x] == -1 || A[y][x] == 0) continue;			    // 공기 청정기 or 먼지 X

			int remain = A[y][x];
			for (int dir = 0; dir < 4; dir++) {
				int ny = y + dy[dir];
				int nx = x + dx[dir];

				if (ny < 1 || ny > R || nx < 1 || nx > C) continue;	// 경계 밖
				if (A[ny][nx] == -1) continue;						          // 공기 청정기

				B[ny][nx] += A[y][x] / 5;
				remain -= A[y][x] / 5;
			}
			B[y][x] += remain;
		}
	}
	
	for (int i = 0; i < cleaner.size(); i++) { 
		POS cur = cleaner[i];
		B[cur.y][cur.x] = -1;
	}
	memcpy(A, B, sizeof(A));
}

void topCleaner(POS pos) {
	int dy[] = { -1,0,+1,0 };	// 상우하좌
	int dx[] = { 0,+1,0,-1 };
	
	int dir = 0;
	int y = pos.y + dy[dir];
	int x = pos.x + dx[dir];
	A[y][x] = 0;

	for(int dir = 0; dir < 4; ){
		int ny = y + dy[dir];
		int nx = x + dx[dir];

		if (ny < 1 || ny > pos.y || nx < 1 || nx > C) {
			ny -= dy[dir];
			nx -= dx[dir];
			dir++;
			ny += dy[dir];
			nx += dx[dir];
		}

		if (A[ny][nx] == -1) break;

		swap(A[y][x], A[ny][nx]);
		y = ny;
		x = nx;
	}
}

void bottomCleaner(POS pos) {
	int dy[] = { +1,0,-1,0 };	// 하우상좌
	int dx[] = { 0,+1,0,-1 };

	int dir = 0;
	int y = pos.y + dy[dir];
	int x = pos.x + dx[dir];
	A[y][x] = 0;

	for (int dir = 0; dir < 4; ) {
		int ny = y + dy[dir];
		int nx = x + dx[dir];

		if (ny <  pos.y || ny > R || nx < 1 || nx > C) {
			ny -= dy[dir];
			nx -= dx[dir];
			dir++;
			ny += dy[dir];
			nx += dx[dir];
		}

		if (A[ny][nx] == -1) break;

		swap(A[y][x], A[ny][nx]);
		y = ny;
		x = nx;
	}
}

void rotateDust() {
	// top cleaner: CCW
	topCleaner(cleaner[0]);
	// bottom cleaner: CW
	bottomCleaner(cleaner[1]);
}

int amountDust() {
	int total = 0;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			total += A[i][j];
		}
	}
	return total + 2;
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d %d", &R, &C, &T);
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			scanf("%d", &A[i][j]);
			if (A[i][j] == -1) cleaner.push_back({ i,j });
		}
	}

	while (T--) {
		spreadDust();
		rotateDust();
	}

	printf("%d\n", amountDust());
}
