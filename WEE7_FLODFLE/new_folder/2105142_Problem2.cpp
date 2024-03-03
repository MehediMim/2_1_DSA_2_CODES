#include <bits/stdc++.h>
using namespace std;
int V, E;

bool bfs(vector<vector<int>> &rdata, int s, int t, int parent[])
{
    vector<bool> visited;
    visited.resize(V, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 0; v < V; v++)
        {
            if (visited[v] == false and rdata[u][v] > 0)
            {
                if (v == t)
                {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;
}

class Graph
{
public:
    vector<vector<int>> data;
    Graph()
    {
        data.resize(V + 1);
        for (int i = 0; i <= V; i++)
        {
            data[i].resize(V + 1, 0);
        }
    }

    void addEdge(int a, int b, int c)
    {
        data[a][b] = c;
    }

    int fordFulkerson(int s, int t)
    {
        int maxFlow = 0;
        int parent[V + 1];
        vector<bool> visited;
        int nodeValue[V + 1];
        vector<vector<int>> rdata;
        rdata.resize(V + 1);
        visited.resize(V + 1, false);
        for (int i = 0; i <= V; i++)
        {
            rdata[i].resize(V + 1, 0);
            nodeValue[i] = 0;
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
                nodeValue[u] += pathFlow;
            }
            maxFlow += pathFlow;
        }

        cout << maxFlow << endl;
        return maxFlow;
    }
};
int main()
{
    vector<tuple<int, int, int>> mainData;
    int m, n;
    cin >> m >> n;
    V = n + m + 2;
    Graph g;
    for (int i = 1; i <= n; i++)
        g.data[0][i] = 1;
    for (int i = n + 1; i <= n + m; i++)
        g.data[i][V - 1] = 1;
    int x, y, z;
    for (int i = 0; i < n + m; i++)
    {
        cin >> x >> y >> z;
        mainData.push_back(make_tuple(x, y, z));
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = n; j < n + m; j++)
        {
            if ((abs(get<0>(mainData[i]) - get<0>(mainData[j])) <= 10) &&
                (abs(get<1>(mainData[i]) - get<1>(mainData[j])) <= 5) &&
                get<2>(mainData[i]) == get<2>(mainData[j]))
            {

                g.data[i + 1][j + 1] = 1;
            }
        }
    }

    g.fordFulkerson(0, V - 1);
}