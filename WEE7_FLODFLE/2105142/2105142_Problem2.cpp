#include <bits/stdc++.h>
using namespace std;
int V, E;

struct conditions
{
    int height;
    int age;
    bool status;
};

bool bfs(vector<vector<int>> &rdata, int s, int t, int parent[])
{
    vector<bool> visited;
    visited.resize(V, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    // parent[s] = -1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 0; v < V; v++)
        {
            if (visited[v] == false and rdata[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    // return false;
    return visited[t];
}

class Graph
{
public:
    vector<vector<int>> data;
    Graph()
    {
        // data.resize(V );
        // for (int i = 0; i <= V; i++)
        // {
        //     data[i].resize(V , 0);
        // }
        vector<vector<int>>temp(V,vector<int>(V,0));
        data=temp;
    }

    void addEdge(int a, int b, int c)
    {
        data[a][b] = c;
    }

    int fordFulkerson(int s, int t)
    {
        int maxFlow = 0;
        int parent[V+1 ];
        vector<bool> visited;
        int nodeValue[V+1 ];
        vector<vector<int>> rdata;
        rdata.resize(V );
        visited.resize(V , false);
        for (int i = 0; i <= V; i++)
        {
            rdata[i].resize(V , 0);
        }
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                rdata[i][j] = data[i][j];
            }
        }
        while (bfs(rdata, s, t, parent))
        {
            int u, v;
            int pathFlow = INT_MAX;
            for (v = t; v != s; v = parent[v])
            {
                u = parent[v];
                pathFlow = min(rdata[u][v], pathFlow);
            }
            for (v = t; v != s; v = parent[v])
            {
                u = parent[v];
                rdata[u][v] -= pathFlow;
                rdata[v][u] += pathFlow;
            }
            maxFlow += pathFlow;
        }

        cout << maxFlow << endl;
    }
};
int main()
{
    int m, n;
    cin >> n >> m;

    V = n + m + 2;
    Graph g;
    // vector<tuple<int, int, int>> mainData;
    // mainData.resize(V, make_tuple(0, 0, 0));
    vector<conditions> _conditions(V);
    for (int i = 1; i <= n; i++)
        g.data[0][i] = 1;
    for (int i = n + 1; i <= n + m; i++)
        g.data[i][V - 1] = 1;
    for (int i = 1; i <= n + m; i++)
    {
        // mainData.push_back(make_tuple(x, y, z));
        cin >> _conditions[i].height >> _conditions[i].age >> _conditions[i].status;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = n + 1; j <= n + m; j++)
        {
            if ((abs(_conditions[i].height - _conditions[j].height) <= 10) and
                (abs(_conditions[i].age - _conditions[j].age) <= 5) and _conditions[i].status == _conditions[j].status)
            {

                g.data[i][j] = 1;
            }
        }
    }
    // for (int  i = 0; i < V; i++)
    // {
    //     for (int j = 0; j < V; j++)
    //     {
    //         cout<<g.data[i][j]<<" ";  
    //     }
    //     cout<<endl;
    // }
    
    g.fordFulkerson(0, V-1 );
}