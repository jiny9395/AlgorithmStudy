#include <stdio.h>
#include <vector>
#include <queue>
#define MAX 50
#define INF 0x7fffffff
using namespace std;

typedef struct {
	int y, x, t;
}POS;

int N, M, minv, blank;
int map[MAX + 2][MAX + 2];
vector<POS> virus, pick;

int dy[] = { 0,0,-1,+1 };
int dx[] = { -1,+1,0,0 };

int spreadVirus() {
	bool visited[MAX + 2][MAX + 2] = { false, };
	int blank_cnt = blank;

	if (blank_cnt == 0) return 0;

	queue<POS> q;
	for (int i = 0; i < pick.size(); i++) {
		POS cur = pick[i];
		visited[cur.y][cur.x] = true;
		q.push(cur);
	}

	while (!q.empty()) {
		POS cur = q.front();	q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int ny = cur.y + dy[dir];
			int nx = cur.x + dx[dir];

			if (ny < 1 || ny > N || nx < 1 || nx > N) continue;
			if (map[ny][nx] == 1 || visited[ny][nx]) continue;

			if (map[ny][nx] == 0) {
				blank_cnt--;
				if (blank_cnt == 0) return cur.t + 1;
			}

			visited[ny][nx] = true;
			q.push({ ny,nx,cur.t + 1 });
		}
	}

	return INF;
}

void Solve(int pos) {
	if (pick.size() == M) {
		int val = spreadVirus();
		if (minv > val) minv = val;
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
			scanf("%d", &map[i][j]);
			if (map[i][j] == 0) blank++;
			else if (map[i][j] == 2) virus.push_back({ i,j });
		}
	}

	minv = INF;
	Solve(0);
	if (minv == INF) printf("-1\n");
	else printf("%d\n", minv);
}
