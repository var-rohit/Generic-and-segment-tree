#include<bits/stdc++.h>
using namespace std;

void build(int *tree,string str,string str1,int start,int end,int treeIndex)
{
    if(start == end)
    {
        int value = (int)str1[start] - 48;
		cout<<str1[start]<<" index is "<<start<<" \n";
        tree[treeIndex] = value%3;
        return;
    }

    int mid = start + (end - start)/2;
    build(tree,str1.substr(start,(mid-start+1)),str1,start,mid,2*treeIndex);
    build(tree,str1.substr(mid+1,(end-mid)),str1,mid+1,end,2*treeIndex+1);
    tree[treeIndex] = (tree[2*treeIndex+1] + ((int)pow(2,(end-mid))*(tree[2*treeIndex])))%3;
    return;

}

void update(int *tree,string str,string str1,int start,int end,int index,int treeIndex)
{
	if(start == end  )
    {
        int value = (int)str1[start] - 48;
		if( start == index && value == 0)
		{
			cout<<str1[start]<<" index is "<<start<<" \n";
        	tree[treeIndex] = (value+1)%3;
		}
        return;
    }


	int mid = start + (end - start)/2;
	update(tree,str1.substr(start,(mid-start+1)),str1,start,mid,index,2*treeIndex);
	update(tree,str1.substr(mid+1,(end-mid)),str1,mid+1,end,index,2*treeIndex+1);
	tree[treeIndex] = (tree[2*treeIndex+1] + ((int)pow(2,(end-mid))*(tree[2*treeIndex])))%3;
	return;


}

int query(int *tree,int query_begin,int query_end,int start,int end,int treeIndex)
{
	if(start > query_end || end < query_begin)
		return 0;

        int mid = start + (end - start)/2;

	if(query_begin <= start && end <= query_end)
	{
		return tree[treeIndex]*(int)(pow(2,query_end-mid));
	}

	int ans1 = query(tree,query_begin,query_end,start,mid,2*treeIndex);
	int ans2 = query(tree,query_begin,query_end,mid+1,end,2*treeIndex+1);
	return (ans2+ans1)%3;
}



int main() {

	// Write your code here
    int n;
    cin>>n;
    string str;
    cin>>str;
//	cout<<"h"<<"\n";
    int *tree = new int[4*n];
    build(tree,str,str,0,n-1,1);

    for(int i=1;i<(4*n);i++)
    {
    	cout<<tree[i]<<"\n";
    }

    int q;
    cin>>q;
    for(int i=0;i<q;i++)
    {
        int type,x,y;
		cin>>type;

	    if(type == 0)
        {
			cin>>x>>y;
			int res = query(tree,x-1,y-1,0,n-1,1);
			cout<<res<<"\n";
        }
        else
        {
			cin>>y;

			update(tree,str,str,0,n-1,y-1,1);
			for(int i=1;i<(4*n);i++)
			{
			  cout<<tree[i]<<"\n";
			}

        }
    }
}
