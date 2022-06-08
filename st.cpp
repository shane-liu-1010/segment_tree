#include<iostream>
#include<sstream>
#include<vector>
using namespace std;

#define int long long

vector<int>st;
vector<int>lazy;
vector<int>a;

void build(int l,int r,int v){
    if(l==r-1){
        st[v]=a[l];
        return;
    }
    int m = (l+r)/2;
    build(l,m,v<<1);
    build(m,r,v<<1|1);
    st[v] = st[v<<1] + st[v<<1|1];
}

void pushDown(int v,int l,int r){
    if(lazy[v]){
        int m = (l+r)>>1;
        st[v<<1]+=lazy[v]*(m-l);
        lazy[v<<1]+=lazy[v];
        st[v<<1|1]+=lazy[v]*(r-m);
        lazy[v<<1|1]+=lazy[v];
        lazy[v]=0;
    }
}

void modify(int l,int r,int n_l,int n_r,int v,int k){
    if(l==r)return;
    if(l==n_l && r==n_r){
        st[v] += k*(r-l);
        lazy[v] += k;
        return;
    }
    pushDown(v,n_l,n_r);
    int m = (n_r+n_l)>>1;
    if(r<=m){
        modify(l,r,n_l,m,v<<1,k);
    }
    else if(l>m){
        modify(l,r,m,n_r,v<<1|1,k);
    }
    else{
        modify(l,m,n_l,m,v<<1,k);
        modify(m,r,m,n_r,v<<1|1,k);
    }
    st[v] = st[v<<1]+st[v<<1|1];
}

int query(int l,int r,int n_l,int n_r,int v){
    if(l==r)return 0;
    if(l==n_l && r==n_r)return st[v];
    int m = (n_l+n_r)>>1;
    pushDown(v,n_l,n_r);
    if(r<=m){
        return query(l,r,n_l,m,v<<1);
    }
    else if(l>m){
        return query(l,r,m,n_r,v<<1|1);
    }
    else{
        return query(l,m,n_l,m,v<<1)+query(m,r,m,n_r,v<<1|1);
    }
}

int32_t main(){
    int n,m;
    cin>>n>>m;
    st.resize(4*n);
    lazy.resize(4*n);
    a.resize(n);
    for(int &i:a)cin>>i;
    build(0,n,1);
    int x,y,k,c;
    for(int i=0;i<m;i++){
        cin>>c;
        if(c==1){
            cin>>x>>y>>k;
            modify(x-1,y,0,n,1,k);
        }
        else{
            cin>>x>>y;
            cout<<query(x-1,y,0,n,1)<<endl;
        }
    }
    return 0;
}
