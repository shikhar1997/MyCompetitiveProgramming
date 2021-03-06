/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Gasnice (GAS)                                             *
 *   Plik:     gasb2.cpp                                                 *
 *   Autor:    Piotr Niedzwiedz                                          *
 *   Opis:     Niepoprawny i nieefektywny algorytm zachlanny O(n^2)      *
 *                                                                       *
 *                                                                       *
 *************************************************************************/


// Headers {{{
#include<iostream>
#include<assert.h>
#include<cstdio>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<string>
#include<list>
#include<deque>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<utility>
#include<sstream>
#include<cstring>
#include<bitset>
#include<numeric>
using namespace std;


#define FOR(I,A,B) for(int I=(A);I<=(B);++I)
#define FORD(I,A,B) for(int I=(A);I>=(B);--I)
#define REP(I,N) for(int I=0;I<(N);++I)
#define VAR(V,init) __typeof(init) V=(init)
#define FORE(I,C) for(VAR(I,(C).begin());I!=(C).end();++I)
#define CLR(A,v) memset((A),v,sizeof((A)))

#define SIZE(x) ((int)((x).size()))
#define ALL(X) (X).begin(),(X).end()
#define PB push_back
#define MP make_pair
#define FI first
#define SE second

typedef vector<int> VI;
typedef pair<int,int> PI;
typedef long long LL;
typedef vector<string> VS;
// }}}

const int nmx=100000;
int n,k,D[nmx],result,Q[nmx],S[nmx];
VI PZ[nmx];
bool W[nmx];
VI E[nmx];
LL s;

void go(int v,int f,int l){
	if(l > k) return;
	if (!W[v]) PZ[D[v]].PB(v);
	FORE(t,E[v]) if(*t!=f) go(*t,v,l+1);
}
void go2(int v,int f,int g,int l){
	if(l > k) return;
	if (!W[v]) S[g]++;
	FORE(t,E[v]) if(*t!=f) go2(*t,v,g,l+1);
}



int main()
{
	scanf("%d%lld%d",&n,&s,&k);
	int a,b;
	REP(i,n-1){
		scanf("%d%d",&a,&b); --a;--b;
		E[a].PB(b),E[b].PB(a);
	}
	int h=0,q=1;
	while(h<n){
		a=Q[h++];	
		FORE(t,E[a]) if(*t && !D[*t]){
			D[*t]=D[a]+1;
			Q[q++]=*t;
		}
	}
	VI tmp;
	for(;;){
		CLR(S,0);
		REP(j,n) go2(j,-1,j,0);
		int best=-1;
		REP(i,n)	if(S[i] > best) { best=S[i];a=i;}
		if (best==0) break;
		go(a,-1,0);
		int f=min(D[a]+k,n-1);
		int t=max(0,D[a]-k);
		tmp.clear();
		FOR(j,t,f){
			while(!PZ[j].empty()){
				tmp.PB(PZ[j].back());
				PZ[j].pop_back();
			}
		}
		if(!tmp.empty()){
			result++;
			for(int j=0;j<s&&!tmp.empty();j++) {W[tmp.back()]=1; tmp.pop_back();}
		}
	}
	printf("%d\n",result);
	return 0;
}
