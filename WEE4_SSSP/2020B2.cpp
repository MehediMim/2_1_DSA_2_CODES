#include <bits/stdc++.h>
using namespace std;
int V,E;
class Graph
{
public:
    vector<vector<pair<int, int>>> v;
    vector<int>weight;
    vector<int>parent;
    vector<int>timeinnode;

    Graph(){
        v.resize(V+1);
        weight.resize(V+1,INT_MAX);
        parent.resize(V+1,-1);
        timeinnode.resize(V+1,0);
    }

    int addEdge(int a, int b, int c)
    {
        v[a].push_back({b,c});
        v[b].push_back({a,c});
    }
    int shortestPath(int src,int des){
        priority_queue<pair<int,int>,vector<pair<int, int>>,greater<pair<int,int>>>pq;
        weight[src]=0;
        pq.push({0,src});
        while(!pq.empty()){
            int u=pq.top().second;
            pq.pop();
            for(const auto &a: v[u]){
                if(a.second+weight[u]+timeinnode[a.first]<weight[a.first]){
                    weight[a.first]=a.second+weight[u]+timeinnode[a.first];
                    parent[a.first]=u;
                    pq.push({weight[a.first],a.first});
                }
            }
        }
        cout<<"Result"<<endl;
        for (int i = 0; i < V; ++i)
        {
            cout<<i+1<<" "<<weight[i]<<" "<<parent[i]<<endl;
        }
        return weight[des];
        cout<<src<<" "<<des;
    }

};
 
int main()
{
    unordered_map<string,int>strtoint;
    unordered_map<int,string>inttostr;
    cin>>V>>E;
    Graph g;
    for(int i=0;i<V;i++){
        string s;
        int a;
        cin>>s>>a;
        strtoint[s]=i;
        inttostr[i]=s;
        g.timeinnode[i]=a;
    }
    // for(int i=0;i<V;i++){
    //     cout<<inttostr[i]<<" "<<endl;
    // }
    // for(const auto& a:strtoint){
    //     cout<<a.first<<a.second<<endl;
    // }
    for(int i=0;i<E;i++){
        string s1,s2;
        int a;
        cin>>s1>>s2>>a;
        g.addEdge(strtoint[s1],strtoint[s2],a);
    }
    string s3,s4;
    cin>>s3>>s4;
    int res = g.shortestPath(strtoint[s3],strtoint[s4]);
    cout<<res<<endl;
    int i=strtoint[s4];
    stack<string>stck;
    while(1){
        //cout<<inttostr[i]<<" ";
        stck.push(inttostr[i]);
        i=g.parent[i];
        if(g.parent[i]==-1){
            //i=g.parent[i];
            //cout<<inttostr[i]<<" ";
            stck.push(inttostr[i]);
            break;
        }
    }
    while(!stck.empty()){
        cout<<stck.top()<<" ";
        stck.pop();
    }

}