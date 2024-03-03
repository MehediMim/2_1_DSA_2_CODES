#include <bits/stdc++.h>
using namespace std;

vector<int>mst;
vector<int>parent;
vector<bool>visited;
vector<int>value;
int final_ans=0;
class Graph{
    public:
    int V;
    vector<pair<int,int>>houses;


    Graph(int n=0){
        V=n;
        houses.resize(n);
    }
    int parentFinder(int i){
        if(parent[i]=-1)return i;
        return parent[i]=parentFinder(i);
    }

    int distanceFinder(pair<int,int> a,pair<int,int> b){
        return abs(a.first-b.first)+abs(a.second-b.second);
    }

    void merge(int a,int b){
        if(parentFinder(a)!=parentFinder(b)){
            parent[a]=parentFinder(b);
        }
    }

    void addEdges(int x,int y){
        houses.push_back({x,y});
    }
    void findmst(){
        parent.resize(V);
        value.resize(V);
        visited.resize(V);
        for(int i=0;i<V;i++){
            parent[i]=-1;
            value[i]=INT_MAX;
            visited[i]=false;
        }
        
        for(int i=0;i<V;i++){
            int distance=INT_MAX;
            for(int j=0;j<V;j++){
                if(distanceFinder(houses[i],houses[j])<distance){
                    if(parentFinder(i)!=parentFinder(j)){
                        // parent[j]=i;
                        // value[j]=distanceFinder(houses[i],houses[j]);
                        merge(i,j);
                        value[j]=distanceFinder(houses[i],houses[j]);
                        distance=value[j];
                    }
                }
            }
            if(distance!=INT_MAX){
                final_ans+=distance;
            }
        }

cout<<final_ans<<endl;
        // for(int i=0;i<V;i++){
        //     cout<<i<<" "<<parent[i]<<endl;
        // }
    }


};
int main()
{
    int n;
    cin>>n;
    Graph g(n);
    for(int i=0;i<n;i++){
        int a,b;
        cin>>a,b;
        g.addEdges(a,b);
    }
    g.findmst();

}