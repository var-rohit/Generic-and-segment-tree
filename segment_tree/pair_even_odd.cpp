#include<bits/stdc++.h>
using namespace std;

struct tree_node
{
    long long int even;
    long long int odd;
};

long long int query(tree_node *tree,int start,int end,int query_begin,int query_end,int treeIndex,int type)
{
    if(type == 1)
    {
    if(query_end < start || query_begin > end)
        {
            return 0;
        }

    if(query_begin <= start && query_end >= end)
    {
        return tree[treeIndex].even;
    }

    int mid = start + (end - start)/2;

    long long int ans1 = query(tree,start,mid,query_begin,query_end,2*treeIndex,type);
    long long int ans2 = query(tree,mid+1,end,query_begin,query_end,2*treeIndex+1,type);
    return ans1+ans2;

    }
    else
    {
        if(query_end < start || query_begin > end)
            {
                return 0;
            }

        if(query_begin <= start && query_end >= end)
        {
            return tree[treeIndex].odd;
        }

        int mid = start + (end - start)/2;

        int ans1 = query(tree,start,mid,query_begin,query_end,2*treeIndex,type);
        int ans2 = query(tree,mid+1,end,query_begin,query_end,2*treeIndex+1,type);
        return ans1+ans2;

    }
}

void update(int *arr,tree_node *tree,int start,int end,int index,int value,int treeIndex)
{

    if(start==end && start == index)
          {
              if(value&1)
                {
                    if(!(arr[start] & 1))
                        {
                            tree[treeIndex].even = 0;
                            tree[treeIndex].odd = 1;
                        }
                }
                else
                {

                        if(arr[start] & 1)
                            {
                                tree[treeIndex].even = 1;
                                tree[treeIndex].odd = 0;
                            }
                }
              return;
          }

    int mid = start+ (end-start)/2;
    if(index <= mid)
        update(arr,tree,start,mid,index,value,2*treeIndex);
    else
        update(arr,tree,mid+1,end,index,value,2*treeIndex+1);
    tree[treeIndex].even = tree[2*treeIndex].even + tree[2*treeIndex+1].even;
    tree[treeIndex].odd = tree[2*treeIndex].odd + tree[2*treeIndex+1].odd;
}

void build(int *arr,tree_node *tree,int start,int end,int treeIndex)
{
    if(start == end)
    {
        if(arr[start] & 1)
                ++tree[treeIndex].odd;
        else
                ++tree[treeIndex].even;

       return;
    }

    int mid = start + (end-start)/2;

    build(arr,tree,start,mid,2*treeIndex);
    build(arr,tree,mid+1,end,2*treeIndex+1);
    tree[treeIndex].even = tree[2*treeIndex].even + tree[2*treeIndex+1].even;
    tree[treeIndex].odd = tree[2*treeIndex].odd + tree[2*treeIndex+1].odd;
}

int main() {

	// Write your code here
    int n;
    cin>>n;

    int *arr = new int[n];
    for(int i=0;i<n;i++)
        cin>>arr[i];

    tree_node *tree = new tree_node[(4*n)];

    build(arr,tree,0,n-1,1);

    int q;
    cin>>q;



    while(q--)
    {
        int type,x,y;

        cin>>type>>x>>y;

        if(type == 0)
        {
          update(arr,tree,0,n-1,x-1,y,1);

        }
        else if(type == 1)
        {
            cout<<query(tree,0,n-1,x-1,y-1,1,1)<<"\n";
        }
        else
        {
            cout<<query(tree,0,n-1,x-1,y-1,1,2)<<"\n";
        }
    }
}
