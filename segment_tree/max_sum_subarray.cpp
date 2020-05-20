#include<bits/stdc++.h>
using namespace std;

struct node
{
    long long int maxsum;
    long long int bps;
    long long int bss;
    long long int sum;
};

long long int maximum(long long int a,long long int b,long long int c,long long int d,long long int e)
{
    return max(a,max(b,max(c,max(d,e))));
}


node query(node *tree,long long int left,long long int right,long long int start,long long int end,long long int treeIndex)
{
    if(right < start || left > end)
    {
        node temp ;
        temp.maxsum = INT_MIN;
        temp.bps = INT_MIN;
        temp.bss = INT_MIN;
        temp.sum = INT_MIN;
        return temp;
    }

    if(left <= start && right >= end)
    {
        return tree[treeIndex];
	}

    long long int mid = start + (end - start)/2;
    node left_  = query(tree,left,right,start,mid,2*treeIndex);
    node right_ = query(tree,left,right,mid+1,end,2*treeIndex+1);

	node ans;
    ans.sum = left_.sum + right_.sum;
    ans.bps = max(left_.sum+right_.bps,left_.bps);
    ans.bss = max(right_.sum+left_.bss,right_.bss);
    ans.maxsum = maximum (left_.maxsum,right_.maxsum,left_.bss+right_.sum,left_.sum+right_.bps,left_.bss+right_.bps);
    return ans;


}





void build(int *arr,node *tree,int treeIndex,int start,int end)
{
    if(start == end)
    {
        tree[treeIndex].sum = arr[start];
        tree[treeIndex].bps = arr[start];
		tree[treeIndex].bss = arr[start];
		tree[treeIndex].maxsum = arr[start];

        return;
     }

     int mid = start + (end-start)/2;
    build(arr,tree,2*treeIndex,start,mid);
    build(arr,tree,2*treeIndex+1,mid+1,end);
    node left = tree[2*treeIndex];
    node right = tree[2*treeIndex+1];
    tree[treeIndex].sum = left.sum + right.sum;
    tree[treeIndex].bps = max(left.sum+right.bps,left.bps);
    tree[treeIndex].bss = max(right.sum+left.bss,right.bss);
    tree[treeIndex].maxsum = maximum (left.maxsum,right.maxsum,left.bss+right.sum,left.sum+right.bps,left.bss+right.bps);
     return ;


}

int main() {

	// Write your code here
    int n,que;


    cin>>n;

    int *arr = new int[n];
    node *tree = new node[4*n];

    for(long long int i=0;i<n;i++)
        cin>>arr[i];

    cin>>que;

    build(arr,tree,1,0,n-1);

	/*for(long long int i=0;i<(4*n);i++)
		cout<<tree[i].maxsum<<" "<<tree[i].sum<<" "<<tree[i].bps<<" "<<tree[i].bss<<"\n";
*/

    while(que--)
    {
        int x,y;
        cin>>x>>y;

            node ans = query(tree,x-1,y-1,0,n-1,1);
        	cout<<ans.maxsum<<"\n";

    }

    delete []arr;
    delete []tree;
    return 0;
}
