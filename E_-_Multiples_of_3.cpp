#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mx = 1e5+1; 

ll tree[4*mx][3], prop[4*mx];

void buildTree(int s, int e, int index)
{
    if(s==e)
    {
        tree[index][0] = 1; 
         
        return; 
    }
    else 
    {
        ll mid = (s+e)/2; 
        buildTree(s, mid, 2*index); 
        buildTree(mid+1, e, 2*index+1); 

        tree[index][0] = tree[2*index][0] + tree[2*index+1][0]; 
        return;
    }
}

void update(int s, int e, int index, int i, int j)
{
    if(prop[index]!=0)
    {
        int x = prop[index]%3; 
        while(x--)
        {
            int two = tree[index][2], one = tree[index][1], zero = tree[index][0]; 
            tree[index][0] = two; 
            tree[index][1] = zero; 
            tree[index][2] = one;
        }
        
        if(s!=e)
        {
            prop[2*index] += prop[index];
            prop[2*index+1] += prop[index];
        }
        prop[index] = 0; 
    }
    if(j<s or i>e) return; 
    else if(s>=i and e<=j)
    {
        int two = tree[index][2], one = tree[index][1], zero = tree[index][0]; 
        tree[index][0] = two; 
        tree[index][1] = zero; 
        tree[index][2] = one;
        if(s!=e)
        {
            prop[2*index]++; 
            prop[2*index+1]++;
        }
        return; 
    }
    else 
    {
        ll mid = (s+e)/2; 
        update(s, mid, 2*index, i, j);
        update(mid+1, e, 2*index+1, i, j);
        tree[index][0] = tree[2*index][0] + tree[2*index+1][0]; 
        tree[index][1] = tree[2*index][1] + tree[2*index+1][1]; 
        tree[index][2] = tree[2*index][2] + tree[2*index+1][2];
        return; 
    }
}

ll query(int s, int e, int index, int l, int r)
{
    if(prop[index]!=0)
    {
        int x = prop[index]%3; 
        while(x--)
        {
            int two = tree[index][2], one = tree[index][1], zero = tree[index][0]; 
            tree[index][0] = two; 
            tree[index][1] = zero; 
            tree[index][2] = one;
        }
        if(s!=e)
        {
            prop[2*index] += prop[index];
            prop[2*index+1] += prop[index];
        }
        prop[index] = 0; 
    }
    if(r<s or l>e) return 0; 
    else if(s>=l and e<=r)
    {
        return tree[index][0];
    }
    else 
    {
        int mid  = (s+e)/2; 
        return query(s, mid, 2*index, l, r) + query(mid+1, e, 2*index+1, l, r);
    }
}


void solve()
{
    ll n, q; 
    cin >> n >> q; 
    memset(tree, 0, sizeof(tree)); 
    memset(prop, 0, sizeof(prop));
    buildTree(0, n-1, 1); 
    while(q--)
    {
        int ch; 
        cin >> ch; 
        if(ch==0)
        {
            int i, j; 
            cin >> i >> j; 
            update(0, n-1, 1, i, j);
        }
        else 
        {
            int i, j; 
            cin >> i >> j; 
            cout << query(0, n-1, 1, i, j) << endl; 
        }
    }
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