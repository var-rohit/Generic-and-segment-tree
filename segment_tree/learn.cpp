#include<bits/stdc++.h>
using namespace std;

struct tree_node
{
	int sos;
	int sum;
};


struct lazy_node
{
	int type;
	int num;
};


int lazy_query(tree_node *tree,lazy_node *lazy,int query_begin,int query_end,int start,int end,int treeIndex)
{
	if(lazy[treeIndex].num != 0)
	{

		if(lazy[treeIndex].type == 1)
			{
				tree[treeIndex].sos += lazy[treeIndex].num*lazy[treeIndex].num*(end-start+1)+2*(tree[treeIndex].sum)*lazy[treeIndex].num;
				tree[treeIndex].sum += lazy[treeIndex].num*(end-start+1);



			if(start != end)
			{
				lazy[2*treeIndex].num = lazy[treeIndex].num;
				lazy[2*treeIndex].type = 1;
				lazy[2*treeIndex+1].num = lazy[treeIndex].num;
				lazy[2*treeIndex+1].type = 1;
			}

		 }
		 else
		 {
			 tree[treeIndex].sos = lazy[treeIndex].num*lazy[treeIndex].num*(end-start+1);
			 tree[treeIndex].sum = lazy[treeIndex].num*(end-start+1);


			 if(start != end)
			{
				lazy[2*treeIndex].num = lazy[treeIndex].num;
				lazy[2*treeIndex].type = 0;
				lazy[2*treeIndex+1].num = lazy[treeIndex].num;
				lazy[2*treeIndex+1].type = 0;
			}
		 }

		lazy[treeIndex].num = 0;
		lazy[treeIndex].type = 2;
	}


	if(end < query_begin || start > query_end)
		return 0;

	if(start >= query_begin && end <= query_end)
		{
					return tree[treeIndex].sos;

		}

	int mid = start + (end - start)/2;

	int ans1 = lazy_query(tree,lazy,query_begin,query_end,start,mid,2*treeIndex);
	int ans2 = lazy_query(tree,lazy,query_begin,query_end,mid+1,end,2*treeIndex+1);
	return ans1+ans2;


}

void lazy_update(tree_node *tree,lazy_node *lazy,int update_begin,int update_end,int start,int end,int inc,int type,int treeIndex)
{


	if(lazy[treeIndex].num != 0)
	{

		if(lazy[treeIndex].type == 1)
			{
				tree[treeIndex].sos += lazy[treeIndex].num*lazy[treeIndex].num*(end-start+1)+2*(tree[treeIndex].sum)*lazy[treeIndex].num;
				tree[treeIndex].sum += lazy[treeIndex].num*(end-start+1);



 			if(start != end)
			{
				lazy[2*treeIndex].num = lazy[treeIndex].num;
				lazy[2*treeIndex].type = 1;
				lazy[2*treeIndex+1].num = lazy[treeIndex].num;
				lazy[2*treeIndex+1].type = 1;
			}

		 }
		 else
		 {
			 tree[treeIndex].sos = lazy[treeIndex].num*lazy[treeIndex].num*(end-start+1);
	 		 tree[treeIndex].sum = lazy[treeIndex].num*(end-start+1);


			 if(start != end)
 			{
 				lazy[2*treeIndex].num = lazy[treeIndex].num;
 				lazy[2*treeIndex].type = 0;
 				lazy[2*treeIndex+1].num = lazy[treeIndex].num;
 				lazy[2*treeIndex+1].type = 0;
 			}
		 }

		lazy[treeIndex].num = 0;
		lazy[treeIndex].type = 2;
	}



	if(end < update_begin || start > update_end)
		return;

	if(start >= update_begin && end <= update_end)
	{
		if(type == 0)
			{
				tree[treeIndex].sos = inc*inc*(end-start+1);
				tree[treeIndex].sum = inc*(end-start+1);

				if(start != end)
				{
					lazy[2*treeIndex].num = inc;
					lazy[2*treeIndex+1].num = inc;
					lazy[2*treeIndex].type = 0;
					lazy[2*treeIndex+1].type = 0;
 				}
			}
			else
			{
				tree[treeIndex].sos += inc*inc*(end-start+1) + 2*(tree[treeIndex].sum)*inc;
				tree[treeIndex].sum += inc*(end-start+1);

				if(start != end)
				{
					lazy[2*treeIndex].num = inc;
					lazy[2*treeIndex+1].num = inc;
					lazy[2*treeIndex].type = 1;
					lazy[2*treeIndex+1].type = 1;
				}

			}

			return;
	}

	int mid = start + (end - start)/2;

	lazy_update(tree,lazy,update_begin,update_end,start,mid,inc,type,2*treeIndex);
	lazy_update(tree,lazy,update_begin,update_end,mid+1,end,inc,type,2*treeIndex+1);
	tree[treeIndex].sos = tree[2*treeIndex].sos + tree[2*treeIndex+1].sos;
	tree[treeIndex].sum = tree[2*treeIndex].sum + tree[2*treeIndex+1].sum;


	return;
}

void build(int *arr,tree_node *tree,int start,int end,int treeIndex)
{

	if(start == end)
	{
			tree[treeIndex].sos = arr[start]*arr[start];
			tree[treeIndex].sum = arr[start];
			return;
	}

	int mid = start + (end-start)/2;

	build(arr,tree,start,mid,2*treeIndex);
	build(arr,tree,mid+1,end,2*treeIndex+1);
	tree[treeIndex].sos = tree[2*treeIndex].sos + tree[2*treeIndex+1].sos;
	tree[treeIndex].sum = tree[2*treeIndex].sum + tree[2*treeIndex+1].sum;
	return;

}

int main()
{
	int tc;
	cin>>tc;

	while(tc--)
	{
		int n,q;
		cin>>n>>q;

		int *arr = new int[n];
		for(int i=0;i<n;i++)
			cin>>arr[i];

		tree_node *tree = new tree_node[4*n];
		lazy_node *lazy = new lazy_node[4*n];

		build(arr,tree,0,n-1,1);

		cout<<"build...."<<"\n";
		for(int i=0;i<(4*n);i++)
			{
				cout<<tree[i].sos<<" "<<tree[i].sum<<"\n";
			}



		int type,st,end;
		for(int i=0;i<q;i++)
		{
			cin>>type>>st>>end;
			if(type == 0)  //change number
			{
				int inc;
				cin>>inc;
				lazy_update(tree,lazy,st-1,end-1,0,n-1,inc,type,1);

				cout<<"change num update"<<"\n";
				for(int i=0;i<(4*n);i++)
					{
						cout<<tree[i].sos<<" "<<tree[i].sum<<"\n";
					}

			}
			else if(type == 1) //inc
			{
				int inc;
				cin>>inc;
				lazy_update(tree,lazy,st-1,end-1,0,n-1,inc,type,1);

				cout<<"inc update"<<"\n";
				for(int i=0;i<(4*n);i++)
					{
						cout<<tree[i].sos<<" "<<tree[i].sum<<"\n";
					}

			}
			else //return sos
			{
				cout<<lazy_query(tree,lazy,st-1,end-1,0,n-1,1);
			}
		}
	}
	return 0;
}
