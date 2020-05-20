#include<bits/stdc++.h>
using namespace std;

int query_lazy(int *tree,int *lazy,int start,int end,int query_begin,int query_end,int treeIndex)
{
	if(lazy[treeIndex] != 0)
	{
		tree[treeIndex] += lazy[treeIndex];
		if(start != end)
			{
				lazy[2*treeIndex] += lazy[treeIndex];
				lazy[2*treeIndex+1] += lazy[treeIndex];
			}

			lazy[treeIndex] = 0;

	}

	if(start > query_end || end < query_begin)
		return INT_MAX;

	if(start >= query_begin && end <= query_end)
			return tree[treeIndex];

	int mid = start + (end-start)/2;

	int ans1 = query_lazy(tree,lazy,start,mid,query_begin,query_end,2*treeIndex);
	int ans2 = query_lazy(tree,lazy,mid+1,end,query_begin,query_end,2*treeIndex+1);
	return min(ans1,ans2);
}

void update_lazy(int *arr,int *lazy,int *tree,int start,int end,int update_begin,int update_end,int inc,int treeIndex)
{
	if(lazy[treeIndex] != 0)
	{
		tree[treeIndex] += lazy[treeIndex];
		if(start != end)
			{
				lazy[2*treeIndex] += lazy[treeIndex];
				lazy[2*treeIndex+1] += lazy[treeIndex];
			}

			lazy[treeIndex] = 0;

	}

	if(start > update_end || end < update_begin)
		return;

	if(start >= update_begin && end <= update_end)
	{
		tree[treeIndex] += inc;
		if(start != end)
		{
			lazy[2*treeIndex] += inc;
			lazy[2*treeIndex+1] += inc;
		}

		return;
	}

	int mid = start + (end - start)/2;
	update_lazy(arr,lazy,tree,start,mid,update_begin,update_end,inc,2*treeIndex);
	update_lazy(arr,lazy,tree,mid+1,end,update_begin,update_end,inc,2*treeIndex+1);
	tree[treeIndex] =  min(tree[2*treeIndex],tree[2*treeIndex+1]);

}

void build(int *arr,int *tree,int start,int end,int treeIndex)
{

	if(start == end)
	{
		tree[treeIndex] = arr[start];
		return;
	}

	int mid = start + (end - start)/2;

	build(arr,tree,start,mid,2*treeIndex);
	build(arr,tree,mid+1,end,2*treeIndex+1);
	tree[treeIndex] = min(tree[2*treeIndex],tree[2*treeIndex+1]);
	return;
}

int main()
{
	int n;
	cin>>n;
	int arr[n];

	for(int i=0;i<n;i++)
		cin>>arr[i];

	int *tree = new int[4*n];
	build(arr,tree,0,n-1,1);

	/*for(int i=1;i<(4*n);i++)
		cout<<tree[i]<<"\n";*/

	int *lazy = new int[4*n];


	/*cout<<"lazy propagated inc "<<"\n";

		for(int i=1;i<(4*n);i++)
			cout<<lazy[i]<<"\n";

	cout<<"segment tree "<<"\n";


			for(int i=1;i<(4*n);i++)
				cout<<tree[i]<<"\n";
*/

	cout<<query_lazy(tree,lazy,0,n-1,2,3,1)<<"\n";
	update_lazy(arr,lazy,tree,0,n-1,2,3,-30,1);

	cout<<query_lazy(tree,lazy,0,n-1,0,3,1)<<"\n";
//	update_lazy(arr,lazy,tree,0,n-1,0,1,2,1);

}
