// 17142. 연구소 3
#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>
#define MAX 50
#define INF 0x7fffffff
using namespace std;

typedef struct {
	int y, x;
}POS;

int N, M, blank, minv;
int A[MAX + 2][MAX + 2];
vector<POS> virus, pick;

int dy[] = { 0,0,-1,+1 };
int dx[] = { -1,+1,0,0 };

int spreadVirus() {
	int size = blank;
	int dist[MAX + 2][MAX + 2];
	memset(dist, -1, sizeof(dist));

	queue<POS> q;
	for (int i = 0; i < pick.size(); i++) {
		POS cur = pick[i];
		dist[cur.y][cur.x] = 0;
		q.push(cur);
	}

	while (!q.empty()) {
		POS cur = q.front();	q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int ny = cur.y + dy[dir];
			int nx = cur.x + dx[dir];

			if (ny < 1 || ny > N || nx < 1 || nx > N) continue;
			if (A[ny][nx] == 1 || dist[ny][nx] != -1) continue; // 벽 or 이미 방문한 칸
			if(A[ny][nx] == 0) size--;

			dist[ny][nx] = dist[cur.y][cur.x] + 1;
			q.push({ ny,nx });

			if (!size) return dist[ny][nx];
		}
	}

	return INF;
}

void Solve(int pos) {
	if (pick.size() == M) {
		int val = spreadVirus();
		minv = minv > val ? val : minv;
		return;
	}

	for (int i = pos; i < virus.size(); i++) {
		pick.push_back(virus[i]);
		Solve(i + 1);
		pick.pop_back();
	}
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &A[i][j]);
			if (A[i][j] == 2)		virus.push_back({ i,j });
			else if (A[i][j] == 0)	blank++;
		}
	}

	if (blank == 0) printf("0\n");
	else {
		minv = INF;
		Solve(0);
		if (minv == INF) printf("-1\n");
		else			 printf("%d\n", minv);
	}
}
