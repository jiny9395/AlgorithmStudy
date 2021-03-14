// 14501. 퇴사
#include <stdio.h>
#define MAX 15

int N, maxv;
int T[MAX + 1];
int P[MAX + 1];

void Solve(int day, int cost) {
	if (day > N + 1) return;
	if (cost > maxv) maxv = cost;

	for (int i = day; i <= N; i++) {
		Solve(i + T[i], cost + P[i]);
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &T[i], &P[i]);
	}

	Solve(1,0);
	printf("%d", maxv);
}
