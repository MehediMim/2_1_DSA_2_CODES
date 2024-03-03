#include <bits/stdc++.h>
using namespace std;

int V;

class Graph
{
public:
    vector<vector<pair<int, int>>> v;
    vector<int>weight;
    vector<int>parent;

    Graph(){
        v.resize(V+1);
        weight.resize(V+1,INT_MAX);
        parent.resize(V+1,-1);
    }

    int addEdge(int a, int b, int c)
    {
        v[a].push_back({b,c});
        v[b].push_back({a,c});
    }
    void shortestPath(int src){
        priority_queue<pair<int,int>,vector<pair<int, int>>,greater<pair<int,int>>>pq;
        weight[src]=0;
        pq.push({0,src});
        while(!pq.empty()){
            int u=pq.top().second;
            pq.pop();
            for(const auto &a: v[u]){
                if(a.second+weight[u]<weight[a.first]){
                    weight[a.first]=a.second+weight[u];
                    parent[a.first]=u;
                    pq.push({weight[a.first],a.first});
                }
            }
        }
        cout<<"Hello"<<endl;
        for (int i = 0; i < V; ++i)
        {
            cout<<i+1<<" "<<weight[i]<<" "<<parent[i]<<endl;
        }
    }

};

int main()
{

    V = 9;
    Graph g;

 
    // making above shown graph
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);
    cout<<"RUN"<<endl;
    g.shortestPath(0);
 

}