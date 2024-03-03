#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

int V, E;

class Graph
{
public:
    vector<vector<pair<int, int>>> v;
    vector<int> weight;
    vector<int> parent;

    Graph()
    {
        v.resize(V + 1);
        weight.resize(V + 1, INT_MAX);
        parent.resize(V + 1, -1);
    }
    void reset()
    {
        for (int i = 0; i <= V; i++)
        {
            weight[i] = INT_MAX;
            parent[i] = -1;
        }
    }

    int addEdge(int a, int b, int c)
    {
        v[a].push_back({b, c});
        // v[b].push_back({a,c});
    }
    int shortestPath(int src, int des)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        weight[src] = 0;
        pq.push({0, src});
        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();
            for (const auto &a : v[u])
            {
                if (a.second + weight[u] < weight[a.first])
                {
                    weight[a.first] = a.second + weight[u];
                    parent[a.first] = u;
                    pq.push({weight[a.first], a.first});
                }
            }
        }
        // cout<<"Hello"<<endl;
        //  for (int i = 0; i < V; ++i)
        //  {
        //      cout<<i+1<<" "<<weight[i]<<" "<<parent[i]<<endl;
        //  }
        return weight[des];
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
    int src;
    cin >> src;
    int index;
    int min = INT_MAX;
    stack<int> forward;
    stack<int> backward;
    stack<int> Finalforward;
    stack<int> Finalbackward;

    for (int j = 0; j < V; j++)
    {

        if (j == src)
            continue;

        // CLEARING

        while (!forward.empty())
        {
            forward.pop();
        }
        while (!backward.empty())
        {
            backward.pop();
        }

        int x = g.shortestPath(src, j);
        int _j = j;
        backward.push(_j);
        while (1)
        {
            _j = g.parent[_j];
            backward.push(_j);
            if (_j == src)
                break;
        }
        g.reset();

        int y = g.shortestPath(j, src);

        int _i = src;
        forward.push(_i);
        while (1)
        {
            _i = g.parent[_i];
            forward.push(_i);
            if (_i == j)
                break;
        }
        cout << x << " " << y << endl;
        int tempmin = x + y;

        if (tempmin < min and j != src)
        {
            min = tempmin;
            index = j;
            int _a = j;
            Finalforward = forward;
            Finalbackward = backward;
        }
        g.reset();
    }
    cout << "min " << min << " " << index <<endl;
    int z=Finalbackward.size();
    int zz=Finalforward.size() ;
    cout<<  z<< " " <<zz << endl;
    for (int i = 0; i < zz; i++)
    {
        cout << Finalforward.top() << " ";
        Finalforward.pop();
    }
    cout << endl;
    for (int i = 0; i < z; i++)
    {
        cout << Finalbackward.top() << " ";
        Finalbackward.pop();
    }
}
