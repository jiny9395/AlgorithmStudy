// 14891. 톱니바퀴
#include <stdio.h>

int A[4][8];
int K;

int rotate(int idx, int d) {
	int tmp[8];
	if (d == 1) {
		tmp[0] = A[idx][7];
		for (int i = 0; i <= 6; i++) tmp[i + 1] = A[idx][i];
	}
	else if (d == -1) {
		tmp[7] = A[idx][0];
		for (int i = 0; i <= 6; i++) tmp[i] = A[idx][i + 1];
	}
	for (int i = 0; i < 8; i++) A[idx][i] = tmp[i];
	return d * -1;
}

void Solve(int n, int d) {
	bool S[3] = { false, };
	for (int i = 0; i < 3; i++) {
		if (A[i][2] == A[i + 1][6]) S[i] = true;
	}

	int dir = rotate(n, d);

	// left
	int c = dir;
	int a = n;
	int b = n - 1;
	while (b >= 0) {
		if (!S[b]) {	// 극이 다른 경우
			c = rotate(b, c);
			a--;
			b--;
		}
		else break;
	}

	// right
	c = dir;
	a = n;
	b = n + 1;
	while (b <= 3) {
		if (!S[a]) {	// 극이 다른 경우
			c = rotate(b, c);
			a++;
			b++;
		}
		else break;
	}
}

int main() {
	for (int i = 0; i < 4; i++) {
		for(int j = 0; j < 8; j++){
			scanf("%1d", &A[i][j]);
		}
	}
	scanf("%d", &K);
	for (int i = 1; i <= K; i++) {
		int n, d;
		scanf("%d %d", &n, &d); // 톱니바퀴 번호, 방향
		Solve(n - 1, d);
	}
	printf("%d", A[0][0] * 1 + A[1][0] * 2 + A[2][0] * 4 + A[3][0] * 8);
}
