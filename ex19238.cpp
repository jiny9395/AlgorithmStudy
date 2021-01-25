#include <string.h>
#include <stdio.h>
#include <queue>
#define MAX 20
using namespace std;

typedef struct {
	int y, x;
}POS;

int N, M, G;
int A[MAX + 2][MAX + 2];	// 지도
POS S[MAX * MAX + 2];		// 출발지 
POS D[MAX * MAX + 2];		// 목적지
POS driver;			// 운전기사 위치
int distSD[MAX * MAX + 2];

int dy[] = { 0,0,-1,+1 };
int dx[] = { -1,+1,0,0 };

bool driverToclient() {		// 기사가 승객에게 갈 수 있는지 판별
	int cnt = 0;
	
	queue<POS> q;
	q.push(driver);

	bool visited[MAX + 2][MAX + 2] = { false, };

	while (!q.empty()) {
		POS cur = q.front();	q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int ny = cur.y + dy[dir];
			int nx = cur.x + dx[dir];

			if (ny < 1 || ny > N || nx < 1 || nx > N) continue;
			if (visited[ny][nx] || A[ny][nx] == 1) continue;
			
			if (A[ny][nx] < 0) cnt++;
			visited[ny][nx] = true;
			q.push({ ny,nx });
		}
	}

	if (cnt != M) return false;
	return true;
}

bool srcTodst() {		// 각 승객의 출발지에서 도착지 까지의 거리 및 갈 수 있는지 판별
	int cnt = 0;

	memset(distSD, -1, sizeof(distSD));
	for (int i = 1; i <= M; i++) {
		POS src = S[i];
		POS dst = D[i];

		queue<POS> q;
		int dist[MAX + 2][MAX + 2];
		memset(dist, -1, sizeof(dist));

		q.push(src);
		dist[src.y][src.x] = 0;

		while (!q.empty()) {
			POS cur = q.front();	q.pop();
			if (cur.y == dst.y && cur.x == dst.x) {		// 도착지인 경우
				distSD[i] = dist[dst.y][dst.x];		// 출발지에서 도착지 까지의 거리 저장
				cnt++;
				break;
			}

			for (int dir = 0; dir < 4; dir++) {		// 상하좌우 탐색
				int ny = cur.y + dy[dir];
				int nx = cur.x + dx[dir];

				if (ny < 1 || ny > N || nx < 1 || nx > N) continue; // 경계 밖
				if (dist[ny][nx] != -1 || A[ny][nx] == 1) continue; // 이미 방문 했거나 벽인 경우
				dist[ny][nx] = dist[cur.y][cur.x] + 1;
				q.push({ ny,nx });
			}
		}
	}

	if (cnt != M) return false;
	return true;
}

int Solve() {
	for (int i = 1; i <= M; i++) {
		
		queue<POS> q;
		int dist[MAX + 2][MAX + 2];
		memset(dist, -1, sizeof(dist));

		q.push(driver);
		dist[driver.y][driver.x] = 0;

		while (!q.empty()) {
			int size = q.size();
			POS client = { 0,0 };

			for (int i = 0; i < size; i++) {
				POS cur = q.front();	q.pop();
				if (A[cur.y][cur.x] < 0) {		// 승객의 위치
					if (client.y == 0 && client.x == 0)		client = cur;
					else if (client.y > cur.y)			client = cur;
					else if (client.y == cur.y && client.x > cur.x) client = cur;
				}

				for (int dir = 0; dir < 4; dir++) {
					int ny = cur.y + dy[dir];
					int nx = cur.x + dx[dir];

					if (ny < 1 || ny > N || nx < 1 || nx > N) continue;
					if (dist[ny][nx] != -1 || A[ny][nx] == 1) continue;
					dist[ny][nx] = dist[cur.y][cur.x] + 1;
					q.push({ ny,nx });
				}
			}

			if (client.y && client.x) {
				int idx = -A[client.y][client.x];	// 승객 idx
				int d1 = dist[client.y][client.x];	// 택시 기사 위치 ~ 출발지
				int d2 = distSD[idx];			// 출발지 ~ 목적지

				if (d1 + d2 > G) return -1;		// 연료가 부족한 경우, 실패
				else {					// 성공
					G -= d1 + d2;
					G += d2 * 2;
					driver = D[idx];		// 택시 기사 위치, 승객의 도착지 위치로 변경
					A[S[idx].y][S[idx].x] = 0;	// 지도에서 승객 위치 제거
				}
				break;
			}
		}
	}
	return G;
}

int main() {
	scanf("%d %d %d", &N, &M, &G);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &A[i][j]);
		}
	}
	scanf("%d %d", &driver.y, &driver.x);
	for (int i = 1; i <= M; i++) {
		scanf("%d %d %d %d", &S[i].y, &S[i].x, &D[i].y, &D[i].x);
		A[S[i].y][S[i].x] = -i;
	}

	if (driverToclient()) {
		if(srcTodst()) printf("%d\n", Solve()); 
		else			     printf("-1");
	}
	else printf("-1\n");
}
