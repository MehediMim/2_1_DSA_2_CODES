#include <bits/stdc++.h>
using namespace std;
 
int V,E;
class Graph{
    public:
    vector<vector<pair<int,int>>>v;
    vector<int>parent;
    vector<int>value;
    vector<int>valueatNode;

    Graph(){
        v.resize(V+1);
        parent.resize(V+1,-1);
        value.resize(V+1,INT_MAX);
        valueatNode.resize(V+1,INT_MAX);
    }
    void addEdge(int a, int b, int c)
    {
        v[a].push_back({b,c});
        v[b].push_back({a,c});
    }
    int shortestPath(int src, int dis){
        priority_queue<pair<int,int>,vector<pair<int, int>>,greater<pair<int,int>>>pq;
        value[src]=0;
        pq.push({0,src});
        while(!pq.empty()){
            int u=pq.top().second;
            pq.pop();
            for(const auto& a:v[u]){
                if(a.second+valueatNode[a.first]<value[a.first]){
                    value[a.first]=a.second+valueatNode[u];
                    parent[a.first]=u;
                    pq.push({value[a.first],a.first});
                }
            }
        }
        return value[dis];
    }


};
int main()
{
    cin>>V>>E;
    Graph g;
    for(int i=0;i<V;i++){
        int x;
        cin>>x;
        g.valueatNode[i+1]=x;
    }
    for(int i=0;i<E;i++){
        int x,y;
        cin>>x>>y;
        g.addEdge(x,y,g.valueatNode[y]);
    }
    int res=g.shortestPath(1,V);
    cout<<res;

}