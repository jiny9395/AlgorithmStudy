#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>
#define MAX 100
using namespace std;

typedef struct {
	int r, c, s, d, z; // 위치, 이동방향, 크기
}SHARK;

int R, C, M, S;
vector<SHARK> shark;
SHARK map[MAX + 2][MAX + 2];

int dy[] = { 0,-1,+1,0,0 }; // 상하우좌
int dx[] = { 0,0,0,+1,-1 };

bool COMP(SHARK a, SHARK b) {
	return a.z > b.z;
}

void moveShark() {
	sort(shark.begin(), shark.end(), COMP);	// 상어 사이즈에 따른 정렬(why? 사이즈가 큰 상어부터 이동)
	bool V[MAX + 2][MAX + 2] = { false, };

	for (int i = 0; i < shark.size(); i++) {
		SHARK cur = shark[i];
		if (!map[cur.r][cur.c].z) {
			shark.erase(shark.begin() + i);	// 잡힌 상어
			i--;
			continue;
		}

		int sp = cur.s;
		if (cur.d == 1 || cur.d == 2) sp %= (R * 2 - 2);
		else sp %= (C * 2 - 2);

		for (int s = 1; s <= sp; s++) {
			int ny = cur.r + dy[cur.d];
			int nx = cur.c + dx[cur.d];

			if (ny < 1 || ny > R || nx < 1 || nx > C) {
				if (cur.d == 1)		 cur.d = 2;
				else if (cur.d == 2) cur.d = 1;
				else if (cur.d == 3) cur.d = 4;
				else if (cur.d == 4) cur.d = 3;
			}
			ny = cur.r + dy[cur.d];
			nx = cur.c + dx[cur.d];

			cur.r = ny;
			cur.c = nx;
		}

		if (V[cur.r][cur.c]) { // 이미 사이즈가 큰 상어가 있는 경우
			shark.erase(shark.begin() + i);
			i--;
		}
		else {
			V[cur.r][cur.c] = true;
			shark[i] = cur;
		}
	}

	memset(map, 0, sizeof(map));
	for (int i = 0; i < shark.size(); i++) {
		SHARK cur = shark[i];
		map[cur.r][cur.c] = cur;
	}
}

void Solve() {
	for (int c = 1; c <= C; c++) {		// 낚시왕 이동	
		for (int r = 1; r <= R; r++) {	// 가까운 상어 잡기
			if (!map[r][c].z) continue;
			S += map[r][c].z;
			map[r][c] = { 0,0,0,0,0 };
			break;
		}
		moveShark();					// 상어 이동
	}
}

int main() {
	scanf("%d %d %d", &R, &C, &M);
	for (int idx = 0; idx < M; idx++) {
		SHARK cur;
		scanf("%d %d %d %d %d", &cur.r, &cur.c, &cur.s, &cur.d, &cur.z);
		map[cur.r][cur.c] = cur;
		shark.push_back(cur);
	}
	Solve();
	printf("%d\n", S);
}
