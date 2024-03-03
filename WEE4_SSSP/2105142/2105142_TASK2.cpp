#include <bits/stdc++.h>
using namespace std;

int V;
int E;
bool modified=false;
class Graph
{
public:
    vector<tuple<int, int, int>> edges;
    vector<int> parent;
    vector<int> value;
    int src;
    Graph(int x = 1)
    {
        edges.resize(V + 1);
        parent.resize(V + 1, -1);
        value.resize(V + 1, INT_MAX);
    }
    void reset(){
        // parent.resize(V + 1, -1);
        // value.resize(V + 1, INT_MAX);
        for(int i=0;i<=V;i++){
            value[i]=INT_MAX;
            parent[i]=-1;
        }
    }

    void addEdge(int x, int y, int z)
    {
        edges.push_back({x, y, z});
    }
    int find_Util(int D)
    {
        {
            for (int i = 0; i < V - 1; i++)
            {
                for (int i = 0; i < edges.size(); i++)
                {
                    int from = get<0>(edges[i]);
                    int to = get<1>(edges[i]);
                    int weight = get<2>(edges[i]);
                    // if(value[from]!=INt_MAX    value[from]+weight<value[to]){
                    if (value[from] != INT_MAX and value[from] + weight < value[to])
                    {
                        value[to] = value[from] + weight;
                    }
                }
            }

            for (int i = 0; i < E; i++)
            {
                int from = get<0>(edges[i]);
                int to = get<1>(edges[i]);
                int weight = get<2>(edges[i]);
                if (value[from] != INT_MAX and value[from] + weight < value[to])
                {
                    return INT_MAX;
                }
            }
        }
        //cout<<"UTIL "<<value[D]<<endl;
        return value[D];
    }
    int findMin(int A, int B, int L, int S, int D)
    {
        value[S] = 0;
        int temp=find_Util( D);
        if(temp==INT_MAX){
            cout<<"CYCLE"<<endl;
            return INT_MAX;
        }
        // cout << S << "_" << value[S] << endl;
        // cout << D << "_" << value[D] << endl;

        addEdge(A, B, L);

        for (int i = 0; i < V - 1; i++)
        {
            for (int i = 0; i < edges.size(); i++)
            {
                int from = get<0>(edges[i]);
                int to = get<1>(edges[i]);
                int weight = get<2>(edges[i]);
                // if(value[from]!=INt_MAX    value[from]+weight<value[to]){
                if (value[from] != INT_MAX and value[from] + weight < value[to])
                {
                    value[to] = value[from] + weight;
                }
            }
        }

        for (int i = 0; i < edges.size(); i++)
        {
            int from = get<0>(edges[i]);
            int to = get<1>(edges[i]);
            int weight = get<2>(edges[i]);
            if (value[from] != INT_MAX and value[from] + weight < value[to])
            {
                //cout << "CYCLE_" << endl;
                edges.pop_back();
                return INT_MAX;
            }
        }
        //cout << L << " " << value[D] << endl;
        edges.pop_back();
        if(temp>value[D]) modified=true;
        //cout<<"Function "<<value[D]<<endl;
        return value[D];
    }
};

main()
{
    int N, M;
    int A, B;
    int L, H;
    int S, D;
    cin >> N >> M;
    V = N;
    E = M;
    Graph g;
    for (int i = 0; i < M; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        g.addEdge(x, y, z);
    }
    cin >> A >> B >> L >> H >> S >> D;
    cout<<endl;
    int minInedx,min=INT_MAX;
    for (int i = L; i <= H; i++)
    {
        int res = g.findMin(A, B, i, S, D);
        //cout<<i<<" "<<res<<endl;
        if(res<min){
            min=res;
            minInedx=i;
        }
        if(res==INT_MAX){
            g.reset();
        }
    }
    if(min!=INT_MAX and modified)cout<<minInedx<<" "<<min<<endl;
    else cout<<"impossible"<<endl;
}

