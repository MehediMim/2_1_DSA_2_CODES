#include <bits/stdc++.h>
using namespace std;


vector<tuple<int, int, int>> mst;

class NODE
{
public:
    int absolute_parent;
    int rank;
};
vector<NODE> _node;

int _find(int x)
{
    if (_node[x].absolute_parent == -1)
    {
        return x;
    }
    return _node[x].absolute_parent = _find(_node[x].absolute_parent);
}
void merge(int from, int to)
{
    int x = _find(from);
    int y = _find(to);
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
    int V;

public:
    Graph(int x)
    {
        V = x;
    }
    Graph()
    {
        V=1;
    }
    void addEdge(int x, int y, int z)
    {
        v.push_back({x, y, z});
    }
    static bool __sort(const tuple<int, int, int> &a, const tuple<int, int, int> &b)
    {
        return get<2>(a) < get<2>(b);
    }
    void kruskal()
    {
        sort(v.begin(), v.end(),__sort);
        for(const auto& edge : v){
            int from,to,weight;
            from=get<0>(edge);
            to=get<1>(edge);
            weight=get<2>(edge);
            cout<<from<<" "<<to<<" "<<weight<<endl;
            
        }
        
        _node.resize(V);
        int answer=0;
        for(int i=0;i<V;i++){
            _node[i].absolute_parent=-1;
            _node[i].rank=0;
        }
        cout << "Following are the edges in the "
                "constructed MST"
             << endl; 
        for(const auto& edge : v){
            int from,to,weight;
            from=get<0>(edge);
            to=get<1>(edge);
            weight=get<2>(edge);
            if(_find(from)!=_find(to)){
                merge(from,to);
                answer+=weight;
                //cout << from << " -- " << to << " == " << weight << endl; 
                mst.push_back({from,to,weight});
            }
        }
        cout << "Minimum Cost Spanning Tree: " << answer<<endl; 
    }

};

int main()
{
    Graph g(5);
    int x,y;
    cin >> x >> y;
    int a ,b ,c;
    for (int i = 0; i < y; i++)
    {
        cin>>a>>b>>c;
        g.addEdge(a,b,c);
    }

    // Function call

    g.kruskal();
    for(const auto& element : mst){
        cout<<"["<<get<0>(element)<<","<<get<1>(element)<<","<<get<2>(element)<<"] ";
    }
}