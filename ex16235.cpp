// 16235. 나무 재테크
#include <stdio.h>
#include <vector>
#define MAX 10
using namespace std;

typedef struct {
	int y, x, z;
}TREE;

int N, M, K;
int A[MAX + 2][MAX + 2];			    // 추가되는 양분의 양
int B[MAX + 2][MAX + 2];			    // 현재 양분의 양
vector<TREE> T[MAX + 2][MAX + 2];	// 나무 정보

int dy[] = { -1,-1,-1,0,0,+1,+1,+1 };
int dx[] = { -1,0,+1,-1,+1,-1,0,+1 };

bool comp(TREE a, TREE b){
	return a.z < b.z;
}

void Solve() {
	vector<TREE> breed;	// 번식할 나무

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (T[i][j].size() == 0) {	// 나무가 없는 경우
				B[i][j] += A[i][j];		    // 겨울: 양분 추가
				continue;
			}

			int dead = 0;

			// 봄: 양분섭취
			int idx = T[i][j].size() - 1;
			for (int k = idx; k >= 0; k--) {
				TREE cur = T[i][j][k];

				if (cur.z > B[i][j]) { // 양분 부족: 죽음
					dead += cur.z / 2;
					T[i][j].erase(T[i][j].begin() + k);
				}
				else {
					B[i][j] -= cur.z;	// 양분섭취
					T[i][j][k].z++;		// 나이 1증가
					if (!(T[i][j][k].z % 5)) breed.push_back(T[i][j][k]);
				}
			}

			// 여름: 죽은 나무 양분으로 변화 + 겨울: 양분 추가
			B[i][j] += (dead + A[i][j]);
		}
	}

	// 가을: 나이 5의 배수 나무 번식
	for (int i = 0; i < breed.size(); i++) {
		TREE cur = breed[i];
		for (int dir = 0; dir < 8; dir++) {
			int ny = cur.y + dy[dir];
			int nx = cur.x + dx[dir];

			if (ny < 1 || ny > N || nx < 1 || nx > N) continue; // 경계 밖
			T[ny][nx].push_back({ ny,nx,1 });
		}
	}
}

int countTree() {
	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cnt += T[i][j].size();
		}
	}
	return cnt;
}

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &A[i][j]);
			B[i][j] = 5;
		}
	}

	for (int i = 1; i <= M; i++) {
		TREE cur;
		scanf("%d %d %d", &cur.y, &cur.x, &cur.z);
		T[cur.y][cur.x].push_back(cur);
	}

	while (K--) {
		Solve();
	}

	printf("%d\n", countTree());
}
