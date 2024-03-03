#include <bits/stdc++.h>
using namespace std;

vector<tuple<int, int, int>> mst;
vector<int> mst_counter;
int V, E;
int COUNT=1;
class NODE
{
public:
    int absolute_parent;
    int rank;
};

int _find(int x, vector<NODE> &_node)
{
    if (_node[x].absolute_parent == -1)
    {
        return x;
    }
    return _node[x].absolute_parent = _find(_node[x].absolute_parent, _node);
}

void merge(int from, int to, vector<NODE> &_node)
{
    int x = _find(from, _node);
    int y = _find(to, _node);
    if (x != y)
    {
        if (_node[x].rank < _node[y].rank)
            _node[x].absolute_parent = y;
        else if (_node[x].rank > _node[y].rank)
            _node[y].absolute_parent = x;
        else
        {
            _node[x].absolute_parent = y;
            _node[y].rank++;
        }
    }
}

class Graph
{
    vector<tuple<int, int, int>> v; // <From,To,Weight>
    vector<tuple<int, int, int>> notSortedv; // <From,To,Weight>

public:
    // Graph(int x)
    // {
    //     V = x;
    // }
    // Graph()
    // {
    //     // V = 1;
    // }
    void addEdge(int x, int y, int z)
    {
        v.push_back({x, y, z});
        notSortedv.push_back({x, y, z});
    }
    static bool __sort(const tuple<int, int, int> &a, const tuple<int, int, int> &b)
    {
        return get<2>(a) < get<2>(b);
    }
    void kruskal(vector<NODE> &_node)
    {
        sort(v.begin(), v.end(), __sort);
        _node.resize(V+1);
        int min_weight = INT_MAX;
        int w = 0;
        // int answer = 0;
        for (int i = 0; i < V; i++)
        {
            _node[i].absolute_parent = -1;
            _node[i].rank = 0;
        }
        //cout << "Following are the edges in the constructed MST" << endl;
        kruskal_util(0, min_weight, w, _node);

        //cout << "Minimum Cost Spanning Tree: " << answer << endl;
    }
    void kruskal_util(int i, int &min_weight, int w, vector<NODE> &_node)
    {
        if (mst.size() == V - 1)
        {
            if (w <= min_weight)
            {
                //TASK 1
                ///////////////////////////////////////////////
                //cout<<COUNT<<" : [";
                COUNT++;
                // for (const auto &element : mst)
                // {
                //     cout << "[" << get<0>(element) << "," << get<1>(element) << "," << get<2>(element) << "]";
                // }
                // cout<<"]"<<endl;

                //TASK 2
                ////////////////////////////////////////////////
                // cout<<"TASK 2"<<endl;
                for (const auto &element : mst)
                {
                     for(int l=0;l<E;l++){
                        if(element==notSortedv[l]){
                            mst_counter[l]++;
                        }
                     }
                }
                //cout << w << " " << min_weight << endl;
                min_weight = w;
                return;
            }
        }
        int k = i;
        vector<NODE> temp_parent;
        while (k < E and get<2>(v[k]) == get<2>(v[i]))
        {
            int from, to, weight;
            from = get<0>(v[k]);
            to = get<1>(v[k]);
            weight = get<2>(v[k]);
            if (_find(from, _node) != _find(to, _node))
            {
                temp_parent = _node;
                merge(from, to, _node);
                // answer += weight;
                mst.push_back({from, to, weight});
                // cout << from << " -- " << to << " == " << weight << endl;
                kruskal_util(k + 1, min_weight, w + weight, _node);
                mst.pop_back();
                _node = temp_parent;
            }
            else if (_find(from, _node) == _find(to, _node))
            {
                kruskal_util(k + 1, min_weight, w, _node);
            }
            k++;
        }
    }
};

int main()
{

    cin >> V >> E;
    Graph g;
    int a, b, c;
    for (int i = 0; i < E; i++)
    {
        cin >> a >> b >> c;
        g.addEdge(a, b, c);
    }

    vector<NODE> _node;
    mst_counter.resize(E);

    // Function call

    g.kruskal(_node);
    //reserve(mst_counter.begin(),mst_counter.end(),__sort);
    vector<int>critical;
    vector<int>pseudo_critical;
    for(int i=0;i<E;i++){
        //cout<<mst_counter[i]<<" "<<endl;
        if(mst_counter[i]==COUNT-1)critical.push_back(i);
        else if(mst_counter[i]!=0)pseudo_critical.push_back(i);
    }
    cout<<"Critical edges: [";
    for(int i=0;i<critical.size();i++){
        cout<<critical[i];
        if(i+1!=critical.size())cout<<",";
    }
    cout<<"]"<<endl;
    cout<<"Pseudo critical edges: [";
    for(int i=0;i<pseudo_critical.size();i++){
        cout<<pseudo_critical[i];
        if(i+1!=pseudo_critical.size())cout<<",";
    }
    cout<<"]";
    // for (const auto &element : mst)
    // {
    //     cout << "[" << get<0>(element) << "," << get<1>(element) << "," << get<2>(element) << "] ";
    // }
}
