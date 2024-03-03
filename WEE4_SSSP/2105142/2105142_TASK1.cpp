#include <bits/stdc++.h>
using namespace std;

int N, M, C; // N cities M roads C capacities

class state
{
public:
    int nowat, fuelLeft, cost;
    state(int x, int y, int z)
    {
        nowat = x;
        fuelLeft = y;
        cost = z;
    }
    bool operator < (const state& temp)const {
        return this->cost>temp.cost;
    }
};
class Graph
{
public:
    vector<vector<pair<int, int>>> edges_data;
    vector<int> price_city;
    vector<vector<int>> all_weight;
    priority_queue<state> pq;
    int src_v;
    int end_v;

    Graph(int x = 1)
    {
        edges_data.resize(N+1);
        price_city.resize(N+1);
        all_weight.resize(N+1, vector<int>(C+1, INT_MAX));
    }
    void addEdge(int a, int b, int c)
    {
        edges_data[a].push_back({b, c});
        edges_data[b].push_back({a, c});
    }

    int dijkstra(int from, int to)
    {
        src_v = from;
        end_v = to;
        all_weight[src_v][0]=0;
        state start(src_v, 0, 0);
        pq.push(start);

        while (!pq.empty())
        {
            state now = pq.top();
            pq.pop();
            int nowat_ = now.nowat;
            int fuelLeft_ = now.fuelLeft;
            int cost_ = now.cost;
            // cout<<"NOW at "<<nowat_<<endl;
            // cout<<"FUEL at "<<fuelLeft_<<endl;
            // cout<<"COST at "<<cost_<<endl;

            // cout<<"COST: "<<cost_<<" PQ: "<<pq.size()<<endl;
            if (nowat_ == end_v)
            {
                return cost_;
            }
            if ((fuelLeft_ + 1) <= C and all_weight[nowat_][fuelLeft_+1]>all_weight[nowat_][fuelLeft_]+price_city[nowat_]){
                all_weight[nowat_][fuelLeft_+1]=all_weight[nowat_][fuelLeft_]+price_city[nowat_];
                pq.push(state(nowat_,fuelLeft_+1,all_weight[nowat_][fuelLeft_]+price_city[nowat_]));
                // cout<<"COST: "<<all_weight[nowat_][fuelLeft_]<<" PQ: "<<pq.size()<<endl;
                // cout<<"ALL OKAY"<<" PQ: "<<pq.size()<<endl;
            }
            for(int i=0;i<edges_data[nowat_].size();i++){
                if(fuelLeft_>= edges_data[nowat_][i].second and all_weight[edges_data[nowat_][i].first][fuelLeft_-edges_data[nowat_][i].second]>cost_){
                    all_weight[edges_data[nowat_][i].first][fuelLeft_-edges_data[nowat_][i].second]=cost_;
                    pq.push(state(edges_data[nowat_][i].first,fuelLeft_-edges_data[nowat_][i].second,cost_));
                    //cout<<"here also Okay"<<" PQ: "<<pq.size()<<endl;
                }
            }
        }
        return -1;
    }
};

// int main()
// {
//     cin >> N >> M >> C;

//     Graph g;
//     for (int i = 0; i < N; i++)
//     {
//         int temp;
//         cin >> temp;
//         g.price_city[i+1] = temp;
//     }
//     for (int i = 0; i < M; i++)
//     {
//         int x, y, z;
//         cin >> x >> y >> z;
//         g.addEdge(x, y, z);
//     }
//     int x,y;
//     cin>>x>>y;
//     int res=g.dijkstra(x,y);
//     if(res==-1)cout<<"impossible"<<endl;
//     else cout<<res<<endl;
// }
// #include <bits/stdc++.h>
// using namespace std;

// int V;

// class Graph
// {
// public:
//     vector<vector<pair<int, int>>> v;
//     vector<int>weight;
//     vector<int>parent;

//     Graph(){
//         v.resize(V+1);
//         weight.resize(V+1,INT_MAX);
//         parent.resize(V+1,-1);
//     }

//     int addEdge(int a, int b, int c)
//     {
//         v[a].push_back({b,c});
//         v[b].push_back({a,c});
//     }
//     void shortestPath(int src){
//         priority_queue<pair<int,int>,vector<pair<int, int>>,greater<pair<int,int>>>pq;
//         weight[src]=0;
//         pq.push({0,src});
//         while(!pq.empty()){
//             int u=pq.top().second;
//             pq.pop();
//             for(const auto &a: v[u]){
//                 if(a.second+weight[u]<weight[a.first]){
//                     weight[a.first]=a.second+weight[u];
//                     parent[a.first]=u;
//                     pq.push({weight[a.first],a.first});
//                 }
//             }
//         }
//         cout<<"Hello"<<endl;
//         for (int i = 0; i < V; ++i)
//         {
//             cout<<i+1<<" "<<weight[i]<<" "<<parent[i]<<endl;
//         }
//     }

// };

// int main()
// {

//     V = 9;
//     Graph g;

 
//     // making above shown graph
//     g.addEdge(0, 1, 4);
//     g.addEdge(0, 7, 8);
//     g.addEdge(1, 2, 8);
//     g.addEdge(1, 7, 11);
//     g.addEdge(2, 3, 7);
//     g.addEdge(2, 8, 2);
//     g.addEdge(2, 5, 4);
//     g.addEdge(3, 4, 9);
//     g.addEdge(3, 5, 14);
//     g.addEdge(4, 5, 10);
//     g.addEdge(5, 6, 2);
//     g.addEdge(6, 7, 1);
//     g.addEdge(6, 8, 6);
//     g.addEdge(7, 8, 7);
//     cout<<"RUN"<<endl;
//     g.shortestPath(0);
 

// }