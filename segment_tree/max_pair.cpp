#include<bits/stdc++.h>
using namespace std;

struct node
{
    int max;
    int smax;
};


node query(node *tree,int left,int right,int start,int end,int treeIndex)
{
    if(right < start || left > end)
    {
        node temp ;
        temp.max = INT_MIN;
        temp.smax = INT_MIN;
        return temp;
    }

    if(left <= start && right >= end)
    {
            	return tree[treeIndex];
	}

    int mid = start + (end - start)/2;
    node left_  = query(tree,left,right,start,mid,2*treeIndex);
    node right_ = query(tree,left,right,mid+1,end,2*treeIndex+1);

	node ans;
    ans.max = max(left_.max,right_.max);
    ans.smax = min(max(left_.max,right_.smax),max(right_.max,left_.smax));
    return ans;


}



void update(int *arr,node *tree,int treeIndex,int start,int end,int value,int index)
{

    if(start == end)
    {
        arr[start] = value;
        tree[treeIndex].max = value;
        tree[treeIndex].smax = INT_MIN;

        return;
    }


    int mid = start + (end-start)/2;
    if(index <= mid)
    {
        update(arr,tree,2*treeIndex,start,mid,value,index);
    }
    else
    {

        update(arr,tree,2*treeIndex+1,mid+1,end,value,index);

    }

    node left = tree[2*treeIndex];
    node right = tree[2*treeIndex+1];
    tree[treeIndex].max = max(left.max,right.max);
    tree[treeIndex].smax = min(max(left.max,right.smax),max(right.max,left.smax));
    return;



}


void build(int *arr,node *tree,int treeIndex,int start,int end)
{
    if(start == end)
    {
        tree[treeIndex].max = arr[start];
        tree[treeIndex].smax = INT_MIN;//arr[end];

        return;
     }

    int mid = start + (end-start)/2;
    build(arr,tree,2*treeIndex,start,mid);
    build(arr,tree,2*treeIndex+1,mid+1,end);
    node left = tree[2*treeIndex];
    node right = tree[2*treeIndex+1];
    tree[treeIndex].max = max(left.max,right.max);
    tree[treeIndex].smax = min(max(left.max,right.smax),max(right.max,left.smax));
    return;


}

int main() {

	// Write your code here
    int n,que;
    char c;

    cin>>n;

    int *arr = new int[n];
    node *tree = new node[4*n];

    for(int i=0;i<n;i++)
        cin>>arr[i];

    cin>>que;

    build(arr,tree,1,0,n-1);


    while(que--)
    {
        cin>>c;
        int x,y;
        cin>>x>>y;

        if(c=='Q')
        {
            node ans = query(tree,x-1,y-1,0,n-1,1);
            cout<<ans.max+ans.smax<<endl;
        }
        else
        {
            update(arr,tree,1,0,n-1,y,x-1);

        }
    }

    delete []arr;
    delete []tree;
    return 0;
}
