#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
#include <iomanip>
using namespace std;
// type alias
typedef long long LL;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<vector<int>> VVI;
typedef unordered_map<int,int> MAPII;
typedef unordered_set<int> SETI;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// collection
#define ALL(c) (c).begin(),(c).end()
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))

// stdout
#define println(args...) fprintf(stdout, ##args),putchar('\n');

// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stderr, ##args); putchar('\n'); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; } }

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address x.cpp && ./a.out
int N=8;

typedef vector<string> BD;
deque<BD> Q;

void show(BD cur) {
  REP(_,N+8) cout<<'-';
  cout<<endl;
  
  cout<<string(2,' ');
  REP(i,N) cout<<i;
  cout<<endl;
  REP(i,N) cout<<i<<" "<<cur[i]<<endl;
  
  REP(_,N+8) cout<<'-';
  cout<<endl;
}

void show() {
  BD cur=Q.back();
  show(cur);
}

bool inside(int r, int c) {
  return 0<=r&&r<N&&0<=c&&c<N;
}
bool inside(II p) {
  return inside(p.first,p.second);
}

int doturn(int r, int c, int cl, int di, int dj, BD &cur) {
  char my='0'+cl,op='0'+(1-cl);
  
  auto dpos=[&](int d)->II {
    return {
      r+di*d,
      c+dj*d
    };
  };

  int res=0;
  int d=1;
  while(inside(dpos(d))&&cur[dpos(d).first][dpos(d).second]==op) ++d;
  II p=dpos(d);
  
  if(inside(p)&&cur[p.first][p.second]==my) FOR(x,1,d) {
    cur[dpos(x).first][dpos(x).second]=my,++res;
  }
  return res;
}

pair<int,BD> put(int r, int c, int cl, BD cur, bool msg=true) {
  BD res=cur;
  char my='0'+cl;
  res[r][c]=my;
  
  int cs[3]={0};
  
  int cnt=0;
  int vert1[2]={1,-1};
  int vert2[2]={0, 0};
  REP(i,2)cnt+=doturn(r,c,cl,vert1[i],vert2[i],res);
  cs[0]=cnt;
  if(msg)cout<<"vertical "<<cnt<<endl;
  
  cnt=0;
  int hor1[2]={0, 0};
  int hor2[2]={1,-1};
  
  REP(i,2)cnt+=doturn(r,c,cl,hor1[i],hor2[i],res);
  
  cs[1]=cnt;
  
  if(msg)cout<<"horizontal "<<cnt<<endl;
  
  cnt=0;
  int diag1[4]={1, 1,-1,-1};
  int diag2[4]={1,-1,-1, 1};

  REP(i,4) cnt+=doturn(r,c,cl,diag1[i],diag2[i],res);
  
  if(msg)cout<<"diagonal "<<cnt<<endl;

  cs[2]=cnt;
  if(msg&&cs[0]==0&&cs[1]==0&&cs[2]==0) cout<<"!!! warn: no reverse"<<endl;
  
  return {cs[0]+cs[1]+cs[2],res};
}

int nextTurn() {
  BD cur=Q.back();
  int p=0;
  REP(i,N) p+=count(ALL(cur[i]),'.');
  int t=(p%2);
  
  return t;
}

void info() {
  show();
  cout<<"next turn: "<<nextTurn()<<endl;
  
  BD cur=Q.back();
  int c0=0;
  REP(i,N) c0+=count(ALL(cur[i]),'0');
  int c1=0;
  REP(i,N) c1+=count(ALL(cur[i]),'1');

  cout<<c0<<" vs "<<c1<<endl;
}

void test() {
  vector<string> b1={
    "........",
    ".1111111",
    ".1000001",
    ".1000001",
    ".100.001",
    ".1000001",
    ".1000001",
    ".1111111"
  };
  
  vector<string> b1e={
    "........",
    ".1111111",
    ".1101011",
    ".1011101",
    ".1111111",
    ".1011101",
    ".1101011",
    ".1111111"
  };
  auto p1=put(4,4,1,b1);
  assert(p1.first==16);
  assert(p1.second==b1e);
}

II solve() {
  BD cur=Q.back();
  
  set<III> S;
  
  REP(i,N)REP(j,N) if(cur[i][j]=='.') {
    auto p=put(i,j,nextTurn(),cur,false);
    if(p.first>0) S.emplace(p.first,i,j);
  }
  if(SZ(S)==0) {
    return {-1,-1};
  }
  
  auto it=S.rbegin();
  int x,r,c; tie(x,r,c)=*it;
  
  cout<<"optimal move: "<<r<<", "<<c<<" ("<<x<<" turns)"<<endl;
  
  return {r,c};
}

int main() {
  test();
  
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  BD cur(N,string(N,'.'));
  cur[3][3]=cur[4][4]='0';
  cur[3][4]=cur[4][3]='1';
  
  Q.push_back(cur);
  
  info();

  while(true) {
    char com; cin>>com;
    if(com=='P') {
      int r,c; cin>>r>>c;
      
      BD cur=Q.back();
      if(cur[r][c]!='.') {
        cout<<"!!! warn already exists at "<<r<<","<<c<<endl;
        continue;
      }
      
      auto p=put(r,c,nextTurn(),Q.back());
      BD nex=p.second;
      Q.push_back(nex);
    } else if(com=='C') {
      Q.pop_back();
    } else if(com=='S') {
      auto p=solve();
      if(p.first==-1) cout<<"!!! No more turn. "<<nextTurn()<<" lost."<<endl;
    }
    if(SZ(Q)>10) Q.pop_front();
    
    info();
  }
  
  return 0;
}
