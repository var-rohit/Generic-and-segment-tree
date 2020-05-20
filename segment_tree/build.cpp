#include<bits/stdc++.h>
using namespace std;

int query(int *tree,int start,int end,int left,int right,int treeIndex)
{
	//totally out of range
	if(end<left || start>right)
	{
		return 0;
	}



	//totally inside range
	if(left<=start && right>=end)
	{
		return tree[treeIndex];
	}

	//partially
	int mid = start + (end - start)/2;
	int ans1 = query(tree,start,mid,left,right,2*treeIndex);
	int ans2 = query(tree,mid+1,end,left,right,2*treeIndex+1);
	return ans1+ans2;
}

void update_segment_tree(int *arr,int *tree,int start,int end,int treeIndex,int index,int value)
{
	if(start == end)
	{
		arr[index] = value;
		tree[treeIndex] = value;
		return;
	}

	int mid  = start + (end - start)/2;
	if(index > mid)
		update_segment_tree(arr,tree,mid+1,end,2*treeIndex+1,index,value);
	else
		update_segment_tree(arr,tree,start,mid,2*treeIndex,index,value);

	tree[treeIndex] = tree[2*treeIndex] + tree[2*treeIndex+1];
}

void build_segment_tree(int *arr,int *tree,int start,int end,int treeIndex)
{
	if(start == end)
	{
		tree[treeIndex] = arr[start];
		return;
	}

	int mid = start + (end - start)/2;
	build_segment_tree(arr,tree,start,mid,2*treeIndex);
	build_segment_tree(arr,tree,mid+1,end,2*treeIndex+1);
	tree[treeIndex] = tree[2*treeIndex] + tree[(2*treeIndex)+1];

}

int main()
{
	int arr[] = {1,2,3,4,5};
	int *tree = new int[50];

	build_segment_tree(arr,tree,0,4,1);

	//cout<<"hello"<<endl;

	update_segment_tree(arr,tree,0,4,1,2,10);

	/*for(int i=1;i<26;i++)
	{
		cout<< tree[i] << endl;
	}*/

	cout<<query(tree,0,4,1,3,1)<<endl;

	return 0;
}
