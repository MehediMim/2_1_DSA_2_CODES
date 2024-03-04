#include <bits/stdc++.h>
using namespace std;

class node
{
public:
    int value;
    int weight;
};

vector<vector<int>> knapsack(vector<node> data, int n, int W)
{
    int max_value = -1000;
    for (int i = 0; i < n; i++)
    {
        if (data[i].value > max_value)
        {
            max_value = data[i].value;
        }
    }
    vector<vector<int>> dp_table(n + 1, vector<int>((n * max_value) + 1));
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n * max_value; j++)
        {
            if (j == 0)
                dp_table[i][j] = 0;
            else if (i == 0)
                dp_table[i][j] = 999999;
            else
            {
                if (data[i - 1].value <= j)
                    dp_table[i][j] = min(dp_table[i - 1][j], dp_table[i - 1][j - data[i - 1].value] + data[i - 1].weight);
                else
                {
                    dp_table[i][j] = dp_table[i - 1][j];
                }
                // cout<<" * "<<dp_table[i][j]<<endl;
            }
        }
    }
    return dp_table;
}

int result(vector<vector<int>> dp_table, vector<node> data, int n, int W)
{
    int ans = -1;
    int max_value = -1000;
    for (int i = 0; i < n; i++)
    {
        if (data[i].value > max_value)
        {
            max_value = data[i].value;
        }
    }
    for (int i = 0; i <= n * max_value; i++)
    {
        if (dp_table[n][i] <= W)
        {
            ans = i;
        }
    }
    // cout << ans << endl;
    return ans;
}
void print(vector<vector<int>> v)
{
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[i].size(); j++)
        {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}
vector<int> get_indices(int ans, vector<vector<int>> dp_table, vector<node> data, int n, int W)
{
    vector<int> v;
    for (int i = n; i > 0;)
    {
        if (dp_table[i][ans] == dp_table[i - 1][ans])
            i--;
        else
        {
            v.push_back(i);
            ans -= data[i - 1].value;
            i--;
            if (ans <= 0)
                break;
        }
    }
    return v;
}

long double scalling_factor(double e, vector<node> data, int n)
{
    int max_value = -1000;
    for (int i = 0; i < n; i++)
    {
        if (data[i].value > max_value)
        {
            max_value = data[i].value;
        }
    }
    return (long double)((e * max_value) / (2.0 * n));
}

vector<node> reduced_value(vector<node> data, int n, double theta)
{
    vector<node> rdata = data;
    for (int i = 0; i < n; i++)
    {
        rdata[i].value = ceil(data[i].value / theta);
        rdata[i].weight = data[i].weight;
    }
    return rdata;
}

int main()
{
    // int n, W;
    // cin >> n >> W;
    // vector<node> data(n);
    // for (int i = 0; i < n; i++)
    // {
    //     cin >> data[i].value >> data[i].weight;
    // }
    // vector<vector<int>> dp_table=knapsack(data, n, W);
    // // print(dp_table);
    // int ans=result(dp_table,data,n,W);
    // cout<<dp_table[n][ans]<<endl;
    // vector<int>v=get_indices(ans,dp_table,data,n,W);
    // for(int i=0;i<v.size();i++){
    //     cout<<v[i]<<" ";
    // }
    int n, W;
    cin >> n >> W;
    vector<node> data(n);
    for (int i = 0; i < n; i++)
    {
        cin >> data[i].value >> data[i].weight;
    }
    vector<vector<int>> dp_table = knapsack(data, n, W);
    int ans = result(dp_table, data, n, W);
    vector<int> indices = get_indices(ans, dp_table, data, n, W);

    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout << "Original Instance: " << endl;
    cout << "Answer: " << ans << endl;
    cout << "Used weight: " << dp_table[n][ans] << endl;
    cout << "Indices: ";
    for (int i = 0; i < indices.size(); i++)
    {
        cout << indices[i] << " ";
    }
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;

    long double epsilon[] = {0.5, 0.2, 0.1, 0.05};
    for (int i = 0; i < 4; i++)
    {
        double e = epsilon[i];
        long double theta = scalling_factor(e, data, n);
        vector<node> rdata = reduced_value(data, n, theta);
        vector<vector<int>> rdp_table = knapsack(rdata, n, W);
        int rans = result(rdp_table, rdata, n, W);
        vector<int> rindices = get_indices(rans, rdp_table, rdata, n, W);
        int used_weight = 0;
        int rounded_value = 0;
        for (int i = 0; i < rindices.size(); i++)
        {
            rounded_value += data[rindices[i] - 1].value;
            used_weight += data[rindices[i] - 1].weight;
        }
        cout << "Rounded Instance with Eps: " << e << endl;
        cout << setprecision(20) << "Theta: " << theta << endl;
        cout << "Answer of reduced instance: " << rans << endl;
        cout <<setprecision(20) << "Answer of reduced instance multiplied by theta: " << 1.0 * rans * theta << endl;
        cout << "Indices: ";
        for (int i = 0; i < rindices.size(); i++)
        {
            cout << rindices[i] << " ";
        }
        cout << endl;
        cout << "Answer of original instance (rounded up): " << rounded_value << endl;
        cout << "Used Weight of rounded instance: " << used_weight << endl;
        cout << "Ratio: " << (1.0 * rans * theta )/ ans << endl;
        cout<<endl;
        cout<<endl;
        cout<<endl;
    }
}