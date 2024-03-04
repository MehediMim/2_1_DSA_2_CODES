#include<bits/stdc++.h>
using namespace std;
# define INF 1e7+10
#define  MIN -1e7


int get_max(vector<pair<int,int>> items,int n){
    int max_value= -1000;
    for(int i=0;i<n;i++){
        max_value=max(max_value,items[i].first);
    }
    return max_value;
}
vector<vector<int>> knapsack(vector<pair<int,int>> items,int n,int w){
    int max_value = get_max(items,n);   
    vector<vector<int>> dp(n+1,vector<int>(n*max_value+1));

    for(int i=0;i<=n;i++){
        for(int j=0;j<=n*max_value;j++){
            if(i==0){
                dp[i][j]=100000;
            }
            if(j==0){
                dp[i][j]=0;
            }
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n*max_value;j++){
            if(items[i-1].first<=j){
                dp[i][j]=min(dp[i-1][j],dp[i-1][j-items[i-1].first]+items[i-1].second);
            }
            else{
                dp[i][j]=dp[i-1][j];
            }
        }
    }
    return dp; 
}

int get_result(vector<vector<int>> dp,vector<pair<int,int>>items,int n,int w){
    int ans=-1;
    for(int i=0;i<=n*get_max(items,n);i++){
        if(dp[n][i]<=w){
            ans=i;
        }
    }
    return ans;
}

vector<int> get_indices(int ans, vector<vector<int>> dp,vector<pair<int,int>> items,int n,int w){
    vector<int> indices;
   
    for(int i=n; i>0 and ans>0 ; i--){
        if(dp[i][ans] != dp[i-1][ans]){
            indices.push_back(i);
            ans-=items[i-1].first;
            cout<<ans<<endl;
        }
    }
    return indices;
}

long double get_scaling_factor(double epsilon,vector<pair<int,int>> items, int n){
    int max_value=MIN;
    for(int i=0;i<n;i++){
        max_value=max(max_value,items[i].first);
    }

    cout<<max_value<<endl;
    cout<<n<<endl;
    return (long double)(epsilon*max_value)/(2.0*n);
}
vector<pair<int,int>> get_reduced_value(vector<pair<int,int>> items, int n, double theta){
    vector<pair<int,int>> reduced_values;
    for(int i=0;i<n;i++){
        reduced_values.push_back({ceil(items[i].first/theta),items[i].second});
    }
    return reduced_values;
}

int main(){
    int n,w;
    cin>>n>>w;
    vector<pair<int,int>> items(n);
    for(int i=0;i<n;i++){
        cin>>items[i].first>>items[i].second;
    }
    vector<vector<int>> dp = knapsack(items,n,w);
    int ans = get_result(dp,items,n,w);
    //   cout<<ans<<endl;
    vector<int> indices = get_indices(ans,dp,items,n,w);
    // for(int i=0;i<indices.size();i++){
    //     cout<<indices[i]<<" ";
    // }
     
    cout<<endl; 
    int wt=0;
    for(int i=0; i<indices.size(); i++){
     wt+=items[indices[i]-1].first;
    }
    
        cout<<"Orginal Instance: "<<endl;
        cout<<"Answer: "<<ans<<endl;
        cout<<"Used Weight: "<<dp[n][ans]<<endl;
        cout<<"indices: ";
        for(int i=0;i<indices.size();i++){
            cout<<indices[i]<<" ";
        }
        cout<<endl;

      long double espilons[] = {0.5,0.2,0.1,0.05};

        for(int i=0; i<4; i++) {

        long double theta = get_scaling_factor(espilons[i],items,n);
        vector<pair<int,int>> reduced_values = get_reduced_value(items,n,theta);
        vector <vector<int>> reduced_dp = knapsack(reduced_values,n,w);
       

      
        long double ans = get_result(reduced_dp,reduced_values,n,w);

        vector<int> reduced_indices = get_indices(ans,reduced_dp,reduced_values,n,w);

        // for(int i=0;i<reduced_indices.size();i++){
        //     cout<<reduced_indices[i]<<" ";
        // }
        vector<pair<int,int>> rounded_items;
        for(int i=0;i<reduced_values.size();i++){
            rounded_items.push_back({reduced_values[i].first*theta,reduced_values[i].second});
        }
        cout<<"Rounded Instance With Epsilon: "<< espilons[i]  <<endl;
        cout<<setprecision(20)<<"Theta: "<<theta<<endl;
        cout<<"Answer of reduced instance: "<<ans<<endl;
        cout<<"Answer of reduced instance multipied by theta "<<1.0*ans*theta<<endl;
        cout<<"indices: ";
        for(int i=0;i<reduced_indices.size();i++){
            cout<<reduced_indices[i]<<" ";
        }
        cout<<endl;
        int used_weight=0;
        int rounded_value=0;
        for(int i=0;i<reduced_indices.size();i++){
            rounded_value+=items[reduced_indices[i]-1].first;
           // cout<<items[reduced_indices[i]-1].first<<".... "<<reduced_indices[i]<<endl;
            used_weight+=items[indices[i]-1].second;
        }
        cout<<"Answer of rounded instance: (rounded up) "<<rounded_value<<endl;
        cout<<"Used Weight of rounded instance: "<<used_weight<<endl;
}
    return 0;
}