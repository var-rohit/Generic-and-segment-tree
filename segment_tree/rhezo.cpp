#include<bits/stdc++.h>
using namespace std;

struct tree_node
{
		int index;
		int a;
		int b;
};

tree_node query(tree_node *tree,int query_begin,int query_end,int start,int end,int treeIndex)
{
	if(start > query_end || end < query_begin)
		{
			tree_node temp ;
			temp.index = INT_MIN;
			temp.a = INT_MIN;
			temp.b = INT_MIN;
			return temp;
		}

	if(start >= query_begin && end <= query_end)
	{
		return tree[treeIndex];
	}

	int mid = start + (end-start)/2;

	tree_node ans1 = query(tree,query_begin,query_end,start,mid,2*treeIndex);
	tree_node ans2 = query(tree,query_begin,query_end,mid+1,end,2*treeIndex+1);
	tree_node res;
	if(ans1.a > ans2.a)
	{
		res.index = ans1.index;
		res.a = ans1.a;
		res.b = ans1.b;
	}
	else if(ans1.a < ans2.a)
	{
		res.index = ans2.index;
		res.a = ans2.a;
		res.b = ans2.b;
	}
	else
	{
		if(ans1.b <= ans2.b)
		{
			res.index = ans1.index;
			res.a = ans1.a;
			res.b = ans1.b;

		}
		else{
			res.index = ans2.index;
			res.a = ans2.a;
			res.b = ans2.b;

		}
	}

	return res;

}

void build(int *A,int *B,tree_node *tree,int start,int end,int treeIndex)
{
	if(start == end)
	{
		tree[treeIndex].index = start;
		tree[treeIndex].a = A[start];
		tree[treeIndex].b = B[start];
		return;
	}

	int mid = start + (end - start)/2;

	build(A,B,tree,start,mid,2*treeIndex);
	build(A,B,tree,mid+1,end,2*treeIndex+1);
	if(tree[2*treeIndex].a > tree[2*treeIndex+1].a)
	{
		tree[treeIndex].index = tree[2*treeIndex].index;
		tree[treeIndex].a = tree[2*treeIndex].a;
		tree[treeIndex].b = tree[2*treeIndex].b;
	}
	else if(tree[2*treeIndex].a < tree[2*treeIndex+1].a)
	{
		tree[treeIndex].index = tree[2*treeIndex+1].index;
		tree[treeIndex].a = tree[2*treeIndex+1].a;
		tree[treeIndex].b = tree[2*treeIndex+1].b;
	}
	else
	{
		if(tree[2*treeIndex].b <= tree[2*treeIndex+1].b)
		{
			tree[treeIndex].index = tree[2*treeIndex].index;
			tree[treeIndex].a = tree[2*treeIndex].a;
			tree[treeIndex].b = tree[2*treeIndex].b;

		}
		else{
			tree[treeIndex].index = tree[2*treeIndex+1].index;
			tree[treeIndex].a = tree[2*treeIndex+1].a;
			tree[treeIndex].b = tree[2*treeIndex+1].b;

		}
	}
}


int main() {

	// Write your code here
	int n;
	cin>>n;
	int *A = new int[n];
	int *B = new int[n];

	for(int i=0;i<n;i++)
		cin>>A[i];


	for(int i=0;i<n;i++)
		cin>>B[i];




		tree_node *tree = new tree_node[(4*n)];
		build(A,B,tree,0,n-1,1);

	/*	for(int i=0;i<(4*n);i++)
			cout<<tree[i].index<<" "<<tree[i].a<<" "<<tree[i].b<<"\n";
*/
		int q;
		cin>>q;

		while(q--)
		{
			int st,end;
			cin>>st>>end;
			tree_node ans = query(tree,st-1,end-1,0,n-1,1);
			cout<<ans.index+1<<"\n";
		}



}
