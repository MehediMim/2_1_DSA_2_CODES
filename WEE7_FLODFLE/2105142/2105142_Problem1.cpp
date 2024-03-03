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

void dfs(vector<vector<int>> &rdata, int s, vector<bool> &visited)
{
    visited[s] = true;
    for (int i = 0; i < V; i++)
    {
        if (rdata[s][i] > 0 && !visited[i])
        {
            dfs(rdata, i, visited);
        }
    }
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

        /////////// a ///////////////////////////////////////
        int nodeIndex;
        int maxValueOfNode = INT_MIN;

        for (int i = 0; i < V; i++)
        {
            if (i != s and i != t)
            {
                if (nodeValue[i] > maxValueOfNode)
                {
                    maxValueOfNode = nodeValue[i];
                    nodeIndex = i;
                }
            }
        }
        cout << "Answer of 1.a" << endl;
        cout << nodeIndex << " " << nodeValue[nodeIndex] << endl;

        //////////// b /////////////////////////////////////
        dfs(rdata, s, visited);

        cout << "Answer of 1.b" << endl;
        bool firstOnePrinted = false; 
        queue<int>notVisited;
        cout<<"[{";
        for (int i = 1; i < V; i++)
        {
            if (visited[i] == true)
            {
                if (firstOnePrinted)
                {
                    cout << ",";
                }
                cout << i;
                firstOnePrinted = true;
            }
            else{
                notVisited.push(i);
            }
        }
        cout<<"},{";

        // firstOnePrinted = false; 
        // for (int i = 1; i < V; i++)
        // {
        //     if (visited[i] == false)
        //     {
        //         if (firstOnePrinted)
        //         {
        //             cout << ",";
        //         }
        //         cout << i;
        //         firstOnePrinted = true;
        //     }
        // }
        while(!notVisited.empty()){
            cout<<notVisited.front();
            notVisited.pop();
            if(notVisited.size()!=0){
                cout<<",";
            }
        }
        cout<<"}]"<<endl;
        cout<<maxFlow<<endl;
        return maxFlow;
    }
};
int main()
{
    cin >> V >> E;
    V++;
    Graph g;
    int x, y, z;
    for (int i = 0; i < E; i++)
    {
        cin >> x >> y >> z;
        g.addEdge(x, y, z);
    }
    int a, b;
    cin >> a >> b;
    g.fordFulkerson(a, b);
}