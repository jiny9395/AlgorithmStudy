// 20058. 마법사 상어와 파이어스톰
#include <stdio.h>
#include <queue>
#define MAX 64
using namespace std;

typedef struct {
	int y, x;
}POS;

int N, Q, L;
int A[MAX + 2][MAX + 2];
int B[MAX + 2][MAX + 2];
bool V[MAX + 2][MAX + 2];

int dy[] = { 0,0,-1,+1 };
int dx[] = { -1,+1,0,0 };

void mapCopy() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			A[i][j] = B[i][j];
		}
	}
}

void melt() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (!A[i][j]) {
				B[i][j] = 0;
				continue;
			}

			int cnt = 0;
			for (int dir = 0; dir < 4; dir++) {
				int ny = i + dy[dir];
				int nx = j + dx[dir];

				if (ny < 1 || ny > N || nx < 1 || nx > N) continue;
				if (A[ny][nx]) cnt++;
			}

			if (cnt < 3) B[i][j] = A[i][j] - 1;
			else		 B[i][j] = A[i][j];
		}
	}
}

void rotate(int sy, int sx) {
	int ey = sy + L - 1;
	int ex = sx + L - 1;

	int i = sy;
	int j = sx;

	// rotate
	for (int x = ex; x >= sx; x--, i++) {
		for (int y = sy, j = sx; y <= ey; y++, j++) {
			B[y][x] = A[i][j];
		}
	}
}

void Solve() {
	for (int i = 1; i <= N; i += L) {
		for (int j = 1; j <= N; j += L) {
			rotate(i, j);
		}
	}
	mapCopy();
	melt();
	mapCopy();	
}

int bfs(int y, int x) {
	queue<POS> q;
	int cnt = 1;
	V[y][x] = true;
	q.push({ y,x });

	while (!q.empty()) {
		POS cur = q.front();	q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int ny = cur.y + dy[dir];
			int nx = cur.x + dx[dir];

			if (ny < 1 || ny > N || nx < 1 || nx > N) continue;
			if (V[ny][nx] || !A[ny][nx]) continue;
			
			cnt++;
			V[ny][nx] = true;
			q.push({ ny,nx });
		}
	}

	return cnt;
}

int totalICE() {
	int total = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			total += A[i][j];
		}
	}
	return total;
}

int bigICE() {
	int maxv = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (!A[i][j] || V[i][j]) continue;
			int val = bfs(i, j);
			maxv = maxv < val ? val : maxv;
		}
	}
	return maxv;
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &N, &Q);
	N = 1 << N;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &A[i][j]);
		}
	}

	for (int i = 1; i <= Q; i++) {
		scanf("%d", &L);
		L = 1 << L;
		Solve();
	}

	printf("%d\n%d\n", totalICE(), bigICE());
}
