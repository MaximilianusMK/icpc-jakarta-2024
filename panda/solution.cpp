#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define sc second

const long long INF = 1e18;

int main()
{
	int N, S;
	scanf("%d%d", &N, &S);
	
	int mn = S, mx = S;
	vector<pair<int, int>> pairs[2];
	for(int i = 1; i <= N; i++)
	{
		int A, B;
		scanf("%d%d", &A, &B);
		
		mn = min({mn, A, B});
		mx = max({mx, A, B});
		
		if(A < S && B > S)
		{
			pairs[0].push_back({S - A, B - S});
		}
		else if(A > S && B < S)
		{
			pairs[1].push_back({A - S, S - B});
		}
	}
	
	long long ans = INF;
	for(int ii = 0; ii < 2; ii++)
	{
		sort(pairs[ii].begin(), pairs[ii].end());
		
		int maxB = 0;
		for(int i = pairs[ii].size() - 1; i >= 0; i--)
		{
			int a, b;
			a = pairs[ii][i].fr;
			b = pairs[ii][i].sc;
			
			ans = min(ans, (long long)a + maxB);
			maxB = max(maxB, b);
		}
		ans = min(ans, (long long)maxB);
	}
	ans = (ans + mx - mn) * 2;
	printf("%lld\n", ans);
}
