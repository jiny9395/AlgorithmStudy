// 16236. 
#include <stdio.h>
#include <queue>
#define MAX 20
using namespace std;

typedef struct {
	int y, x, s, c;			    // 상어 위치, 크기, 먹은 물고기개수
}SHARK;

typedef struct {
	int y, x;
}POS;

int N;						        // 크기의 공간 N x N
int A[MAX + 2][MAX + 2];	// 공간 정보
SHARK shark;				      // 상어 정보

int dy[] = { 0,0,-1,+1 };
int dx[] = { -1,+1,0,0 };

int findFish() {
	int dist[MAX + 2][MAX + 2];
	queue<POS> q;	
	POS catchFish = { 0,0 };

	for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) dist[i][j] = -1;
	
	dist[shark.y][shark.x] = 0;
	q.push({ shark.y,shark.x });

	while (!q.empty()) {
		
		POS cur = q.front();	q.pop();
		if ((catchFish.y && catchFish.x) && dist[cur.y][cur.x] >= dist[catchFish.y][catchFish.x]) continue; 
		
		for (int dir = 0; dir < 4; dir++) {
			int ny = cur.y + dy[dir];
			int nx = cur.x + dx[dir];

			if (ny < 1 || ny > N || nx < 1 || nx > N) continue;	// 경계 밖
			if (A[ny][nx] > shark.s) continue;					        // 물고기의 크기 > 상어의 크기
			if (dist[ny][nx] != -1) continue;					          // 이미 방문한 곳
				
			if (A[ny][nx] && A[ny][nx] < shark.s) {
				if (!catchFish.y && !catchFish.x) catchFish = { ny,nx };
				else if (catchFish.y > ny) catchFish = { ny,nx };
				else if (catchFish.y == ny && catchFish.x > nx) catchFish = { ny,nx };
			}

			dist[ny][nx] = dist[cur.y][cur.x] + 1;
			q.push({ ny,nx });
		}	
	}

	if (catchFish.y && catchFish.x) {			// 물고기를 잡았을 경우
		A[catchFish.y][catchFish.x] = 0;		// 잡은 물고기 자리 0

		shark.c++;								          // 상어가 잡은 물고기 개수 1증가
		if (shark.s == shark.c) {				    // 자신의 크기와 같은 수의 물고기를 먹은 경우, 크기 1증가
			shark.c = 0;
			shark.s++;
		}

		shark.y = catchFish.y;					        // 상어 위치, 잡은 물고기 위치로 변경
		shark.x = catchFish.x;
		return dist[catchFish.y][catchFish.x];	// 잡은 물고기까지의 거리 리턴
	}

	return 0;	// 물고기를 못잡은 경우, 0 리턴
}

int Solve() {
	int total = 0;
	while (1) {
		int time = findFish();
		total += time;
		if (!time) break;
	}
	return total;
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &A[i][j]);
			if (A[i][j] == 9) shark = { i,j,2,0}, A[i][j] = 0;
		}
	}

	printf("%d\n", Solve());
}
