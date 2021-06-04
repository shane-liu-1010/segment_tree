#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cmath>
#include<functional>
using namespace std;

#define endl '\n'
#define IO_optimization cin.tie(0),ios_base::sync_with_stdio(false)


auto func=[](auto a,auto b){
    return (a>b)?a:b;
};

template<class T>class SegmentTree{
private:
    int l_segment;
    int r_segment;
    T data;
    SegmentTree *l_son;
    SegmentTree *r_son;
    void build(int l,int r,vector<T>&v){
        l_segment=l,r_segment=r;
        if(l==r-1)data=v[l];
        else{
            l_son=new SegmentTree();
            r_son=new SegmentTree();
            l_son->build(l,(l+r)/2,v);
            r_son->build((l+r)/2,r,v);
            data=func(l_son->data,r_son->data);
        }
    }
public:
    SegmentTree(){l_son=r_son=nullptr;}
    SegmentTree(vector<T>&v){build(0,v.size(),v);}
    T query(int l,int r){
        if(l_segment==l && r_segment==r)return data;
        else{
            int mid=(l_segment+r_segment)/2;
            if(r<=mid)return l_son->query(l,r);
            else if(l>=mid)return r_son->query(l,r);
            else return func(l_son->query(l,mid),r_son->query(mid,r));
        }
    }
    void modify(int x,T value){
        if(l_segment==r_segment-1)data=value;
        else{
            int mid=(l_segment+r_segment)/2;
            if(x<mid)l_son->modify(x,value);
            else r_son->modify(x,value);
            data=func(l_son->data,r_son->data);
        }
    }
};

int main(){
    IO_optimization;

    vector<int>v;
    int n;
    cin>>n;
    v.resize(n);

    for(int i=0;i<n;i++)cin>>v[i];
    SegmentTree<int>st(v);

    int q;
    cin>>q;
    int l,r;
    for(int i=0;i<q;i++){
        cin>>l>>r;
        if(l>r){
            int temp=l;l=r;r=temp;
        }
        cout<<(st.query(l-1,r))<<endl;
    }
    return 0;
}
/*

10
3 2 4 5 6 8 1 2 9 7
7
1 5
3 5
1 10
5 8
6 6
2 4
2 9

*/
