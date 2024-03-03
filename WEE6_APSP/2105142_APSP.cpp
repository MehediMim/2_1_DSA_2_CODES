#include <bits/stdc++.h>
using namespace std;
int V, E;

class Graph
{
public:
    vector<vector<int>> data;
    Graph()
    {
        data.resize(V + 1);
        for (int i = 0; i <= V; i++)
        {
            data[i].resize(V + 1, INT_MAX);
        }
    }

    void addEdge(int a, int b, int c)
    {
        data[a][b] = c;
        data[b][a] = c;
    }
    void apsp(int limit)
    {
        int i, j, k;
        for (i = 0; i <= V; i++)
        {
            for (j = 0; j <= V; j++)
            {
                for (k = 0; k <= V; k++)
                {
                    if (data[i][j] > (data[i][k] + data[k][j]) and (data[k][j] != INT_MAX and data[i][k] != INT_MAX))
                    {
                        data[i][j] = data[i][k] + data[k][j];
                    }
                }
            }
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        for (int i = 1; i <= V; i++)
        {
            int cnt = 0;
            for (int j = 1; j <= V; j++)
            {
                if (data[i][j] <= limit and i!=j)
                {
                    cnt++;
                }
            }
            //cout << i << " " << cnt << endl;
            pq.push({cnt, i});
        }
        // while (!pq2.empty())
        // {
        //     pair<int, int> temp = pq2.top();
        //     cout << temp.second << " (" << temp.first << " reachable vertices)" << endl;
        //     pq2.pop();
        // }
        pair<int, int> checker = pq.top();

        cout << checker.second << " ";
        pq.pop();
        while (!pq.empty())
        {
            //cout<<"HELLO ";
            pair<int, int> temp = pq.top();
            pq.pop();
            //cout<<temp.first <<" "<< checker.first<<endl;
            if (temp.first == checker.first)
            {
                cout << temp.second << " ";
            }
            else
                break;
        }
    }
};

int main()
{
    cin >> V >> E;
    Graph g;
    for (int i = 0; i < E; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        g.addEdge(a, b, c);
    }
    int limit;
    cin >> limit;
    g.apsp(limit);
}