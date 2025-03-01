#include<bits/stdc++.h>
using namespace std;

#define ll long long
//#define int ll
constexpr int inf=0x3f3f3f3f;
constexpr ll INF=0x3f3f3f3f3f3f3f3f;

const int N = 100005;

struct Splay
{
	int rt,tot,fa[N],ch[N][2],val[N],cnt[N],sz[N];
	void maintain(int x){sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+cnt[x];}
	bool get(int x){return x==ch[fa[x]][1];}
	void clear(int x){ch[x][0]=ch[x][1]=fa[x]=val[x]=sz[x]=cnt[x]=0;}
	void rotate(int x)
	{
		int y=fa[x],z=fa[y],chk=get(x);
		ch[y][chk]=ch[x][chk^1];
		if(ch[x][chk^1])fa[ch[x][chk^1]]=y;
		ch[x][chk^1]=y;
		fa[y]=x;
		fa[x]=z;
		if(z)ch[z][y==ch[z][1]]=x;
		maintain(x);
		maintain(y);
	}
	void splay(int x)
	{
		for(int f=fa[x];f=fa[x],f; rotate(x))
		if(fa[f])rotate(get(x)==get(f)?f:x);
		rt=x;
	}
	void ins(int k)//插入操作
	{
		if(!rt)
		{
			val[++tot]=k;
			cnt[tot]++;
			rt=tot;
			maintain(rt);
			return;
		}
		int cur=rt,f=0;
		while(1)
		{
			if(val[cur]==k)
			{
				cnt[cur]++;
				maintain(cur);
				maintain(f);
				splay(cur);
				break;
			}
			f=cur;
			cur=ch[cur][val[cur]<k];
			if(!cur)
			{
				val[++tot]=k;
				cnt[tot]++;
				fa[tot]=f;
				ch[f][val[f]<k]=tot;
				maintain(tot);
				maintain(f);
				splay(tot);
				break;
			}
		}
	}
	int rk(int k)//查询x的排名
	{
		int res=0,cur=rt;
		while(1)
		{
			if(k<val[cur])
			{
				cur=ch[cur][0];
			}
			else
			{
				res+=sz[ch[cur][0]];
				if(k==val[cur])
				{
					splay(cur);
					return res+1;
				}
				res+=cnt[cur];
				cur=ch[cur][1];
			}
		}
	}
	
	int kth(int k)//查询排名x的数
	{
		int cur=rt;
		while(1)
		{
			if(ch[cur][0]&&k<=sz[ch[cur][0]])
			{
				cur=ch[cur][0];
			}
			else
			{
				k-=cnt[cur]+sz[ch[cur][0]];
				if(k<=0)
				{
					splay(cur);
					return val[cur];
				}
				cur=ch[cur][1];
			}
		}
	}
	int pre()//查询前驱
	{
		int cur=ch[rt][0];
		if(!cur)return cur;
		while(ch[cur][1])cur=ch[cur][1];
		splay(cur);
		return cur;
	}
	int nxt()//查询后继
	{
		int cur=ch[rt][1];
		if(!cur)return cur;
		while(ch[cur][0])cur=ch[cur][0];
		splay(cur);
		return cur;
	}
	void del(int k)//删除操作
	{
		rk(k);
		if(cnt[rt]>1)
		{
			cnt[rt]--;
			maintain(rt);
			return;
		}
		if(!ch[rt][0]&&!ch[rt][1])
		{
			clear(rt);
			rt=0;
			return;
		}
		if(!ch[rt][0])
		{
			int cur=rt;
			rt=ch[rt][1];
			fa[rt]=0;
			clear(cur);
			return;
		}
		if(!ch[rt][1])
		{
			int cur=rt;
			rt=ch[rt][0];
			fa[rt]=0;
			clear(cur);
			return;
		}
		int cur=rt;
		int x=pre();
		fa[ch[cur][1]]=x;
		ch[x][1]=ch[cur][1];
		clear(cur);
		maintain(rt);
	}
}tree;


void solve()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int op,x;
		scanf("%d%d",&op,&x);
		if(op==1)tree.ins(x);
		else if(op==2)tree.del(x);
		else if(op==3)printf("%d\n",tree.rk(x));
		else if(op==4)printf("%d\n",tree.kth(x));
		else if(op==5)
		{
			tree.ins(x);
			printf("%d\n",tree.val[tree.pre()]);
			tree.del(x);
		}
		else if(op==6)
		{
			tree.ins(x);
			printf("%d\n",tree.val[tree.nxt()]);
			tree.del(x);
		}
	}
}

signed main()
{
	//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	
	
	//	int _;scanf("%d",&_);while(_--)
	solve();
	return 0;
}