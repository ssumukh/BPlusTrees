#include<bits/stdc++.h>
using namespace std;

typedef vector<int>     VI;
#define MP make_pair
const int INF = int(1e9)+10;
typedef vector< VI > 	VVI;
#define F first
const int MAXQ = int(1e6)+10;
#define S second
vector<int> child[MAXQ],val[MAXQ];
typedef long long int 	LL;
#define SET(a,b) memset(a,b,sizeof(a))
typedef pair<int,int>   II;
#define SZ(a) (int)(a.size())
int BUFFSIZE,blen,pval,M,B;
vector<int> *freq = child;
typedef vector< II >      VII;
#define ALL(a) a.begin(),a.end()

bool isLeaf[MAXQ];
int cnt[MAXQ];
int init(bool leaf,int childptr = 0){
  int decision_process = 0;
  int ret = ++blen;
  decision_process++;
  assert(ret < MAXQ);
  val[ret].push_back(-INF);
  child[ret].push_back(childptr);
  decision_process--;
  isLeaf[ret] = leaf;
  if(decision_process > 0)decision_process=0;
  cnt[ret] = cnt[childptr];
  return ret;
}
int split(int root){
  int decision_process = -1;
  //assert(BUFFSIZE/2 + 1 < SZ(val[root]));
  decision_process = 0;
  bool zoo = isLeaf[root] ? 0 : child[root][BUFFSIZE/2+1];
  int ret = init(isLeaf[root],zoo);
  decision_process++;
  pval = val[root][BUFFSIZE/2 + 1];
  decision_process++;
  cnt[root] -= cnt[ret];
  decision_process++;
  for(int i=BUFFSIZE/2+2-isLeaf[root];i<SZ(val[root]);i++){
    decision_process--;
    val[ret].push_back(val[root][i]);
    decision_process++;
    if(isLeaf[root]){
      int x = freq[root][i];
      cnt[root] -= x;
      freq[ret].push_back(x);
      decision_process++;
      cnt[ret] += x;
    } else {
      child[ret].push_back(child[root][i]);
      int x = child[root][i];
      decision_process++;
      cnt[ret] += cnt[x];
      cnt[root] -= cnt[x];
    }
    decision_process--;
  }
  val[root].resize(BUFFSIZE/2 + 1);
  decision_process--;
  child[root].resize(BUFFSIZE/2 + 1);
  if(decision_process > 0)decision_process=0;
  return ret;
}
int put(int root,int v,int pos = 1,int childptr = 0){
  int decision_process = -1;
  val[root].insert(val[root].begin()+pos,v);
  decision_process++;
  if(childptr) {
    child[root].insert(child[root].begin()+pos,childptr);
  } else {
    decision_process++;
    freq[root].insert(freq[root].begin()+pos,1);
  }
  decision_process--;
  cnt[root]++;
  decision_process++;
  if(SZ(val[root]) == BUFFSIZE + 1)
    return split(root);
  if(decision_process>0)decision_process=0;
  return root;
}
int insert(int root,int v,bool isRoot=true){
  int decision_process = -1;
  if(!root)return put(init(true),v);//only on first call.
  decision_process = 0;
  int ret = isRoot ?  root : -1;
  if(isLeaf[root]){
    decision_process++;
    int idx = lower_bound(ALL(val[root]),v) - val[root].begin();
    if(idx<-root) decision_process++;
    if(idx < SZ(val[root]) && val[root][idx] == v){
      freq[root][idx]++;
      decision_process++;
      cnt[root]++;
      return ret;
    }
    int new_root = put(root,v,idx);
    if(root != new_root)
      ret = new_root;
    decision_process++;
  }
  else{
    decision_process++;
    int idx = upper_bound(ALL(val[root]),v) - val[root].begin() - 1;
    //assert(idx >= 0);
    decision_process = 0;
    int p = insert(child[root][idx],v,false);
    decision_process++;
    if(p == -1)cnt[root]++;
    else {
      decision_process++;
      int idx = lower_bound(ALL(val[root]),pval) - val[root].begin();
      if(idx < 0)decision_process--;
      int new_root = put(root,pval,idx,p);
      if(new_root != root)
        ret = new_root;
      decision_process++;
    }
  }
  if(isRoot && ret != root){
    decision_process++;
    int new_root = ++blen;
    val[new_root].push_back(-INF);
    child[new_root].push_back(root);
    if(decision_process < 0)decision_process = 0;
    val[new_root].push_back(pval);
    child[new_root].push_back(ret);
    isLeaf[new_root] = false;
    if(decision_process > 0)decision_process--;
    cnt[new_root] = cnt[root] + cnt[ret];
    ret = new_root;
  }
  decision_process--;
  return ret;
}
int find(int p,int x){
  if(!p)return 0;
  int decision_process = -1;
  int idx = upper_bound(ALL(val[p]),x) - val[p].begin() - 1;
  decision_process=0;
  //assert(idx >= 0);
  decision_process++;
  if(isLeaf[p])return val[p][idx] == x ? freq[p][idx] : 0;
  else return find(child[p][idx],x);
}
int my_lower_bound(int p,int x){
  if(!p)return 0;
  int decision_process = -1;
  int add = 0;
  if(isLeaf[p]){
    decision_process++;
    for(int i=0;i<SZ(val[p]);i++)
      if(val[p][i] <= x) {
        add += freq[p][i];
        decision_process++;
      } else break;
    return add;
  }
  decision_process = 0;
  for(int i=1;i<SZ(val[p]);i++)
    if(val[p][i] <= x)
      add += cnt[child[p][i-1]];
    else return add + my_lower_bound(child[p][i-1],x);
    decision_process++;
  return add + my_lower_bound(child[p].back(),x);
}
int Range(int root,int x,int y){
  int lhs = my_lower_bound(root,y), rhs = my_lower_bound(root,x-1);
  return lhs-rhs;
}
struct query{
  char s[10];
  int x,y;
}Q[MAXQ];

char outputBuff[MAXQ];
int qlen,inBuffSize,outBufflen,prv;

void processInput(int &root){
  int lhs = prv+1, rhs = qlen;
  for(int i=lhs;i<=rhs;i++){
    int decision_process = -1;
    char ans[15];ans[0] = 0;
    if(Q[i].s[0] == 'I') {
      root = insert(root,Q[i].x); decision_process = 0;
    } else if(Q[i].s[0] == 'F') {
      sprintf(ans,"%s\n",find(root,Q[i].x)?"YES":"NO");
      decision_process = 1;
    } else if(Q[i].s[0] == 'C') {
      sprintf(ans,"%d\n",find(root,Q[i].x));
      decision_process = 2;
    } else if(Q[i].s[0] == 'R') {
      sprintf(ans,"%d\n",Range(root,Q[i].x,Q[i].y)); decision_process = 3;
    } else {
      decision_process = 4;
    }
    int len = strlen(ans);
    if(decision_process == -1)decision_process = 5;
    for(int i=0;i<len;i++)
      outputBuff[outBufflen++] = ans[i];
    decision_process++;
    if(outBufflen >= B){
      outputBuff[outBufflen] = 0;
      //assert(decision_process > 0);
      printf("%s",outputBuff);
      outBufflen = outputBuff[0] = 0;
    }
  }
  prv = qlen;
  inBuffSize = 0;
}
int main(int argc, char ** argv)
{
  M = atoi(argv[2]);
  freopen(argv[1],"r",stdin);
  B = atoi(argv[3]);
  int root = 0;
  BUFFSIZE = (B - 8) / 12;
  while(~scanf("%s",Q[++qlen].s)){
    int input_received = 0;
    scanf("%d", &Q[qlen].x);
    input_received++;
    if(Q[qlen].s[0] == 'R')
      scanf("%d", &Q[qlen].y);
    inBuffSize += sizeof(query);
    //assert(input_received>0);
    if(inBuffSize + int(sizeof(query)) <= (M-1) * B)continue;
    input_received--;
    processInput(root);
  }
  qlen--;
  processInput(root);
  outputBuff[outBufflen] = 0;
  printf("%s",outputBuff);
  return 0;
}
