#include<bits/stdc++.h>
using namespace std;

#define MOD 1000000007LL

int n,ans,x,y;
char s[5007];
int dp[5007][5007],suff[5007][5007],lcp[5007][5007];

int main() {
	scanf("%s",&s);
	n = strlen(s);
	
	for (int i = n; i >= 0; i--) {
		for (int j = n; j > i; j--) {
			if (i == n || j == n || s[i] != s[j]) {
				lcp[i][j] = 0;
			} else {
				lcp[i][j] = 1 + lcp[i+1][j+1];
			}				
		}
	}
	
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			dp[i][j] = -999999999;
		}
	}
	
	for (int i = n-1; i >= 0; i--) {
		for (int j = n-1; j >= i; j--) {
			if (j == n-1) {
				dp[i][j] = 1;
				suff[i][j] = 1;
			} else {
				int len = min(j-i+1,lcp[i][j+1]);
				
				if (j+len+1 >= n) {
					dp[i][j] = -999999999;
				} else if (i+len > j || s[i+len] < s[j+len+1]) {
					dp[i][j] = 1 + suff[j+1][j+len+1];
				} else {
					dp[i][j] = -999999999;
				}
				suff[i][j] = max(dp[i][j],suff[i][j+1]);
			}
		}
	}
	
	ans = -999999999;
	x = 0;
	y = 0;
	for (int i = 0; i < n; i++) {
		if (dp[0][i] > ans) {
			ans = max(ans,dp[0][i]);
			y = i;
		}
	}
	printf("%d\n",ans);
	
	while (ans > 2) {
		for (int i = x; i <= y; i++) printf("%c",s[i]);
		printf("\n");
		
		int len = 0;
		while (x+len <= y && s[x+len] == s[y+len+1]) len++;
		for (int i = y+len+1; i < n; i++) {
			if (dp[y+1][i] == ans - 1) {
				x = y+1;
				y = i;
				break;
			}
		}
		ans--;
	}
	if (ans == 2) {
		for (int i = x; i <= y; i++) printf("%c",s[i]);
		printf("\n");
		for (int i = y+1; i <= n-1; i++) printf("%c",s[i]);
		printf("\n");
	} else {
		for (int i = x; i <= y; i++) printf("%c",s[i]);
		printf("\n");
	}
}
