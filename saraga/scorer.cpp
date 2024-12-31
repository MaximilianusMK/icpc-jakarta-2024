#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define fr first
#define sc second

void ac()
{
	printf("AC\n");
	exit(0);
}

void wa()
{
	printf("WA\n");
	exit(0);
}

int main(int argc, char* argv[])
{
	ifstream inp(argv[1]);
	ifstream out(argv[2]);
	ifstream con(argv[3]);
	
	string S, T;
	inp >> S >> T;
	
	string outAns;
	out >> outAns;
	
	string ans;
	if(!(con >> ans))
	{
		wa();
	}
	
	string dummy;
	if(con >> dummy)
	{
		wa();
	}
	
	if(outAns == "-1")
	{
		if(ans != "-1")
		{
			wa();
		}
		
		ac();
	}
	else
	{
		if(ans.length() != outAns.length())
		{
			wa();
		}
		
		int pref = 0;
		while(pref < (int)min(S.length(), ans.length() - 1) && S[pref] == ans[pref])
		{
			pref++;
		}
		
		int suff = 0;
		while(suff < (int)min(T.length(), ans.length() - 1) && T[T.length() - 1 - suff] == ans[ans.length() - 1 - suff])
		{
			suff++;
		}
		
		if(pref + suff <= (int)ans.length())
		{
			wa();
		}
		
		ac();
	}
}
