#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int n, r;
int visited[26];
char alphabet[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
char sort[26];

void dfs(int depth, int start) {
	
	if (depth == r) {
		for (int i = 0; i < n; i++)
		{
			if (visited[i] != 0) {
				sort[visited[i]] = alphabet[i];
			}
		}
		for (int i = 0; i < n; i++)
		{
			if (sort[i] != NULL) {
				printf("%c", sort[i]);
			}
		}
		printf("\n");
		return;
	}


	for (int i = 0; i < n; i++)
	{
		if (visited[i] == 0) {
			visited[i] = depth+1;
			dfs(depth + 1, i);
			visited[i] = 0;
		}
	}
}

int main() {
	
	scanf("%d %d", &n, &r);

	for (int i = 0; i < n; i++)
	{
		visited[i] = 1;
		dfs(1, i);
		visited[i] = 0;
	}
}
