#include <bits/stdc++.h>
using namespace std;


class Graph{
    int V;
    vector<vector<pair<int,int>>>data;

    public:
    Graph(int x=1){
        V=x;
        data.resize(x);
    }
    void addEdge(int a ,int b,int c){
        data[a].push_back({b,c});
    }
    void shortestPath(int from);
    int minFinder(vector<int>value,vector<bool>visited);
};

int Graph::minFinder(vector<int>value,vector<bool>visited){
    int min=INT_MAX;
    int min_index=-1;
    for(int i=0;i<value.size();i++){
        if(value[i]<min and visited[i]==false){
            min=value[i];
            min_index=i;
        }
    }
    return min_index;
}

void Graph::shortestPath(int from){
    vector<int>value(V);
    vector<bool>visited(V);
    vector<int>parent(V);

    for(int i=0;i<V;i++){
        value[i]=INT_MAX;
        visited[i]=false;
        parent[i]=-1;
    }

    value[from]=0;
    
    for(int i=0;i<V-1;i++){
        int u=minFinder(value,visited);
        for(int j=0;j<data[u].size();j++){
            cout<<data[u][j].first<<" ";
            if(visited[data[u][j].first]==false and value[data[u][j].first]>(data[u][j].second+value[u])){
                value[data[u][j].first]=data[u][j].second+value[u];
                parent[data[u][j].first]=u;
            }
        }
        visited[u]=true;
        cout<<"_"<<u<<endl;
    }
    for(int i=0;i<V;i++){
        cout<<value[i]<<" ";
    }
}

int main()
{
    int tempV=7;
    //cin>>tempV;
    Graph G(tempV);
    G.addEdge(0, 1, 2);
    G.addEdge(0, 2, 6);
    G.addEdge(1, 3, 5);
    G.addEdge(2, 3, 8);
    G.addEdge(3, 4, 10);
    G.addEdge(3, 5, 15);
    G.addEdge(4, 6, 2);
    G.addEdge(5, 6, 6);
    G.shortestPath(0);
}