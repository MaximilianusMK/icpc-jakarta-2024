#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define sc second

const int MXA = 26, INF = 1e9;

int main()
{
	string S, T;
	cin >> S >> T;
	
	int N, M;
	N = S.length();
	M = T.length();
	
	int minS[MXA + 69];
	for(int i = 0; i < MXA; i++)
	{
		minS[i] = INF;
	}
	for(int i = 2; i <= N; i++)
	{
		int k = S[i - 1] - 'a';
		minS[k] = min(minS[k], i);
	}
	
	int minT[MXA + 69];
	for(int i = 0; i < MXA; i++)
	{
		minT[i] = INF;
	}
	for(int i = 1; i <= M - 1; i++)
	{
		int k = T[i - 1] - 'a';
		minT[k] = min(minT[k], M + 1 - i);
	}
	
	pair<int, int> ans;
	ans.fr = INF;
	for(int i = 0; i < MXA; i++)
	{
		ans = min(ans, {minS[i] + minT[i] - 1, -i});
	}
	
	if(ans.fr != INF)
	{
		int e = -ans.sc;
		string Z = S.substr(0, minS[e]) + T.substr(M - minT[e] + 1, minT[e] - 1);
		printf("%s\n", Z.c_str());
	}
	else
	{
		printf("-1\n");
	}
}
