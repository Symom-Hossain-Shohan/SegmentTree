#include<bits/stdc++.h>
using namespace std;

typedef long long ll;


void buildTree(int *ar, int s, int e, int index, int *tree)
{
    if(s==e) 
    {
        tree[index] = ar[s];
        return; 
    }
    //Recursively build the left sub-tree and then the right sub-tree and finally merge
    int mid = (s+e)/2; 
    buildTree(ar, s, mid, 2*index, tree);   
    buildTree(ar, mid+1, e, 2*index + 1, tree);

    //merging
    tree[index] = min(tree[2*index], tree[2*index+1]); 
    return; 
}


int query(int *tree, int s, int e, int qs, int qe, int index)
{
    if(s>=qs and e<=qe)
    {
        return tree[index];
    }
    else if(e<qs or s>qe) return INT32_MAX;
    else 
    {
        int mid = (s+e)/2; 
        int left = query(tree, s, mid, qs, qe, 2*index); 
        int right = query(tree, mid+1, e, qs, qe, 2*index + 1);
        return min(left, right);
    } 
}

void update(int *tree, int s, int e, int l, int r, int increment, int index)
{
    if(r<s or l>e) 
    {
        return; 
    }
    else if(s==e)
    {
        tree[index] += increment; 
        return; 
    }
    else 
    {
        int mid = (s+e)/2; 

        update(tree, s, mid, l, r, increment, 2*index);
        update(tree, mid+1, e, l, r, increment,  2*index+1);
        tree[index] = min(tree[2*index], tree[2*index+1]); 
        return; 
    }
}


void solve()
{
    int n; 
    cin >> n; 
    int ar[n];
    for(auto &i: ar) cin >> i; 

    int *tree = new int(4*n+1);
    memset(tree, -10, sizeof(tree)); 
    buildTree(ar, 0, n-1, 1, tree);
    update(tree, 0, n-1, 3, 3, 8, 1);
    cout << query(tree, 0, n-1, 0, 5, 1);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll tc = 1;
    //cin >> tc;
    for (ll t = 1; t <= tc; t++)
    {
        solve();
    }
    return 0;
}