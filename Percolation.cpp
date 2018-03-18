#include <bits/stdc++.h>
#include <random>
using namespace std;
int a,b,n,v=0;
random_device rand_dev;
mt19937 generator(rand_dev());
bool unionFind(int r[],int a1,int b1)
{
	//cout<<a<<" UF "<<b<<endl;
	while(r[a1]!=a1||r[b1]!=b1)
	{
		a1=r[a1];
		b1=r[b1];
	}
	return(r[a1]==r[b1]);
}
void connect(bool g[],int s[], int r[], int a1,int b1)
{
	//cout<<b1<<" CONNECT "<<a1<<endl;
	if(g[a1]==0||g[b1]==0||unionFind(r,a,b))
		return;
	while(r[a1]!=a1||r[b1]!=b1)
	{
		a1=r[a1];
		b1=r[b1];
	}
	if(s[r[a1]]<s[r[b1]])
	{
		
		r[a1]=r[b1];
		s[r[b1]]+=s[r[a1]];
	}
	else
	{
		r[b1]=r[a1];
		s[r[a1]]+=s[r[b1]];
	}
}
void unions(bool g[],int s[],int r[],int n,int t)
{
	//cout<<"UNIONS "<<t<<endl;
	if(t%n<n-1)
		connect(g,s,r,t,t+1);
	if(t%n>0)
		connect(g,s,r,t,t-1);
	if(t/n>0)
		connect(g,s,r,t,t-n);
	if(t/n<n-1)
		connect(g,s,r,t,t+n);
}
float percolate(bool g[], int s[],int r[],int n)
{
	//cout<<"PERCOLATE"<<endl;
	uniform_int_distribution<int> distr(0, n*n-1);

	int i=0,t=0;
	srand(time(NULL));
	while(!unionFind(r,a,b))
	{
		//srand(time(NULL));
		//t= (n)*(rand()%n)+rand()%(n);
		//cout<<t<<" ";
		int t= distr(generator);
		if(g[t]==0)
			i++;
		g[t]=1;
		unions(g,s,r,n,t);
	}
	//v=t;
	//cout<<endl;
	//cout<<"DONE"<<endl;
	//cout<<i<<"/"<<n*n<<endl;
	return 1.0*i/(n*n);
}

void reset(bool grid[], int size[], int root[],int n)
{
	//cout<<"RESET"<<endl;

	for(int i=0;i<n*n+2;i++)
	{
		grid[i]=0;
		size[i]=1;
		root[i]=i;
		if(i<n)
			root[i]=a;
		else if(i>n*n-n-1)
			root[i]=b;
		//root[a]=a;
	}
	root[a]=a;
	size[a]=n+1;
	size[b]=n+1;
	grid[a]=1;
	grid[b]=1;
}

int main()
{
	//int n;
	float sum=0;
	cin>>n;
	a=n*n,b=n*n+1;
	bool grid[n*n+2];
	int size[n*n+2],root[n*n+2];
	reset(grid,size,root,n);
	int k;
	cin>>k;
	//srand(time(NULL));
	for(int i=0;i<k;i++)
	{
		//srand(time(NULL));
		sum+=percolate(grid,size,root,n);
		reset(grid,size,root,n);
	}
	cout<<1.0*sum/k<<endl;
	return 0;
}