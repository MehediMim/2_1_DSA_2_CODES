#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <climits>
using namespace std;
class Solution
{
public:
    bool bfs(vector<vector<int>> &rGraph, int s, int e, vector<int> &parent, int v)
    {
        vector<int> visited(v, 0);
        queue<int> q;
        q.push(s);
        parent[s] = -1;
        visited[s] = 1;
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            if (node == e)
                return true;
            for (int adjNode = 0; adjNode < v; adjNode++)
            {
                if (!visited[adjNode] && rGraph[node][adjNode] > 0)
                {
                    parent[adjNode] = node;
                    visited[adjNode] = 1;
                    q.push(adjNode);
                }
            }
        }
        return false;
    }

    int findMaxFlow(vector<vector<int>> &rGraph, int S, int E)
    {
        vector<int> parent(E + 1);
        parent[0] = -1;
        int maxFlow = 0;
        while (bfs(rGraph, 0, E, parent, E + 1))
        {
            int pathFlow = INT_MAX;
            int v = E;
            while (parent[v] != -1)
            {
                int u = parent[v];
                pathFlow = min(pathFlow, rGraph[u][v]);
                v = u;
            }
            maxFlow += pathFlow;

            v = E;
            while (parent[v] != -1)
            {
                int u = parent[v];
                rGraph[u][v] -= pathFlow;
                rGraph[v][u] += pathFlow;
                v = u;
            }
        }

        return maxFlow;
    }

    int maximumMatch(vector<vector<int>> &G)
    {
        int r = G.size();
        int c = G[0].size();
        vector<vector<int>> rGraph(r + c + 2, vector<int>(r + c + 2, 0));
        for (int i = 1; i <= r; i++)
        {
            rGraph[0][i] = 1;
        }
        for (int i = r + 1; i <= r + c; i++)
        {
            rGraph[i][r + c + 1] = 1;
        }
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                rGraph[i + 1][j + r + 1] = G[i][j];
            }
        }
        return findMaxFlow(rGraph, 0, r + c + 1);
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> G(n, vector<int>(m, 0));
    for (int i = 0; i < m; i++)
    {
        int jobId;
        cin>>jobId;
        jobId-=1;
        int no;
        cin>>no;
        while(no--){
            int emp;
            cin>>emp;
            emp-=1;
            G[emp][jobId]=1;
        }
        
        
    }

    cout<<Solution().maximumMatch(G)<<endl;

    return 0;
}