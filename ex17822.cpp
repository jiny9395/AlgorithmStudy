#include <stdio.h>
#include <queue>
#include <string.h>
#define MAX 50
using namespace std;

int N, M, T;
int circle[MAX + 2][MAX + 2];
bool visited[MAX + 2][MAX + 2];

int dy[] = { 0,0,-1,+1 };
int dx[] = { -1,+1,0,0 };

int getSum() {
	int sum = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			sum += circle[i][j];
		}
	}
	return sum;
}

double getAvg() {
	double avg = 0;
	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (circle[i][j] == 0) continue;
			cnt++;
			avg += circle[i][j];
		}
	}
	return avg / cnt;
}

void cw(int n) {
	int tmp[MAX + 2] = { 0, };
	tmp[1] = circle[n][M];
	for (int i = 1; i <= M - 1; i++) {
		tmp[i + 1] = circle[n][i];
	}

	for (int i = 1; i <= M; i++) {
		circle[n][i] = tmp[i];
	}
}

void ccw(int n) {
	int tmp[MAX + 2] = { 0, };
	tmp[M] = circle[n][1];
	for (int i = 2; i <= M; i++) {
		tmp[i - 1] = circle[n][i];
	}

	for (int i = 1; i <= M; i++) {
		circle[n][i] = tmp[i];
	}
}

void rotate(int n, int d, int k) {
	k %= M;
	if (d == 0) { // 시계방향 
		for (int i = 1; i <= k; i++) {
			cw(n);
		}
	}
	else {		 // 반시계방향
		for (int i = 1; i <= k; i++) {
			ccw(n);
		}
	}
}

bool removeNum(int y, int x, int n) {
	memset(visited, false, sizeof(visited));

	bool changed = false;
	queue<pair<int, int>> q;
	queue<pair<int, int>> zero;

	visited[y][x] = true;
	q.push({ y,x });

	while(!q.empty()){
		pair<int, int> cur = q.front();	q.pop();
		
		for (int dir = 0; dir < 4; dir++) {
			int ny = cur.first + dy[dir];
			int nx = cur.second + dx[dir];

			if (ny < 1 || ny > N) continue;
			if (nx < 1) nx = M;
			if (nx > M) nx = 1;

			if (visited[ny][nx]) continue;
			
			visited[ny][nx] = true;
			if (circle[ny][nx] == n) {
				q.push({ ny,nx });
				zero.push({ ny,nx });
			}
		}

		while (!zero.empty()) {
			pair<int, int> cur = zero.front();	zero.pop();
			circle[cur.first][cur.second] = 0;
			changed = true;
		}
	}

	if (changed) circle[y][x] = 0;

	return changed;
}

void findNum() {
	bool changed = false;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (circle[i][j] == 0) continue; // 숫자가 없는 경우
			bool ret = removeNum(i, j, circle[i][j]);
			if (ret) changed = true;
		}
	}

	if (changed == false) {
		double avg = getAvg();
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (!circle[i][j]) continue;
				if (avg < circle[i][j])		 circle[i][j]--;
				else if (avg > circle[i][j]) circle[i][j]++;
			}
		}
	}
}

int main() {
	scanf("%d %d %d", &N, &M, &T);

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%d", &circle[i][j]);
		}
	}

	for (int i = 1; i <= T; i++) {
		int x, d, k;
		scanf("%d %d %d", &x, &d, &k);

		for (int n = x; n <= N; n += x) {
			rotate(n, d, k);
		}
		findNum();
	}

	printf("%d\n", getSum());
}
