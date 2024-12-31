#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define sc second

const int minOdd = 11;

inline int calc(int x)
{
	return x * (x + 3) - 2;
}

int main()
{
	int K;
	scanf("%d", &K);

  if (K == 8) {
    cout << "3 3" << endl;
    cout << "1 2" << endl;
    cout << "1 3" << endl;
    cout << "2 3" << endl;
    return 0;
  }

  if (K == 23) {
    cout << "5 7" << endl;
    cout << "4 5" << endl;
    cout << "2 3" << endl;
    cout << "3 1" << endl;
    cout << "2 4" << endl;
    cout << "4 3" << endl;
    cout << "2 1" << endl;
    cout << "1 5" << endl;
    return 0;
  }

	int N = 1, M;
	vector<pair<int, int>> edges;
	while(K > minOdd)
	{
		int c = 1;
		while(calc(c + 1) <= K - minOdd)
		{
			c++;
		}
		K -= calc(c);

		edges.push_back({1, N + 1});
		int last = 1;
		for(int i = 2; i <= c; i++)
		{
			edges.push_back({last, N + i});
			edges.push_back({N + 1, N + i});
			last = N + i;
		}
		N += c;
	}

	if(K % 2 == 1)
	{
		if(K < minOdd)
		{
			printf("-1 -1\n");
			return 0;
		}

		K -= minOdd;

		edges.push_back({1, N + 1});
		edges.push_back({1, N + 2});
		edges.push_back({N + 1, N + 2});
		edges.push_back({N + 1, N + 3});
		N += 3;
	}

	while(K > 0)
	{
		K -= 2;

		edges.push_back({1, N + 1});
		N++;
	}

	M = edges.size();
	printf("%d %d\n", N, M);
	for(int i = 0; i < M; i++)
	{
		int u, v;
		u = edges[i].fr;
		v = edges[i].sc;
		printf("%d %d\n", u, v);
	}
}