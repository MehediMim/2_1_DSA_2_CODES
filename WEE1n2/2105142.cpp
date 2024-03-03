#include <bits/stdc++.h>
using namespace std;

int data[100][100];
int visited[100];
int N ,M;
stack<int>stck;

void topo_sort(int i){
    visited[i]=1;
    //cout<<i<<" ";
    for(int j=1;j<10;j++){
        if(data[i][j]==1 and visited[j]!=1){
            //cout<<"All right"<<i<<endl;
            topo_sort(j);
        }
    }
    stck.push(i);
}
int main()
{
    cin>>N>>M;
    int x,y;
    for(int i=0;i<M;i++){
        cin>>x>>y;
        data[x][y]=1;
    }

    for(int i=1;i<=N;i++){
        if(visited[i]==0){
            topo_sort(i);
        //cout<<"hall e net nai"<<endl;
        }
    }
    //cout<<"Print"<<endl;
    int yy=stck.size();
     for(int i=0;i<yy;i++){
        int x= stck.top();
        stck.pop();
        cout<<x<<" ";
    }

}