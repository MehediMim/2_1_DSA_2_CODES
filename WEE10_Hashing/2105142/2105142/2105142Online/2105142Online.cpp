// You have to prepare a national index for storing and searching for information about the citizens
// of our country. The index should store 3 information about a citizen: name, NID number, and
// phone number. We should be able to search the index by any of the three information. The
// program should output all information of the searched citizen, if available. The run-time
// complexity for storing or searching information about a single citizen should be O(|s1|+|s2|+|s3
// |),
// where s1
// is his name, s2 is his NID number, and s3
// is his phone number. You can assume that the
// total number of records in the index will be less than 1000.

#include <bits/stdc++.h>
using namespace std;
#include "hash.cpp"

class NODE{
    public:
    string name;
    string NID;
    string phonenumber;
    NODE(string a,string b,string c){
        name=a;
        NID=b;
        phonenumber=c;
    }
};
int main()
{
    hashTable *ht=new hashTable(1000,100);
    vector<NODE*>v;
    int counter=0;
    v.resize(1000);
    while(1){
        int t;
        string name;
    string NID;
    string phonenumber;
        cout<<"Enter choice: 1. Enter Data, 2. Search Index"<<endl;
        cin>>t;
        if(t==1){
            cout<<"Enter name:"<<endl;
            cin>>name;
            cout<<"Enter NID no:"<<endl;
            cin>>NID;
            cout<<"Enter phone no: "<<endl;
            cin>>phonenumber;
            v.push_back(new NODE (NID,name,phonenumber));
            ht->insert_chain(1,NID,name,phonenumber);
        }
        else if(t==2){
            string temp;
            cin >>temp;
            for(auto a:v){
                if(a->name==temp){
                    auto x= ht->search_chain(1,temp);
                    cout<<x->name<<endl;
                    cout<<x->phonenumber<<endl;
                    cout<<x->key<<endl;
                }
                if(a->NID==temp){
                    temp=a->NID;
                    auto x= ht->search_chain(1,temp);
                    cout<<x->name<<endl;
                    cout<<x->phonenumber<<endl;
                    cout<<x->key<<endl;
                }
                if(a->phonenumber==temp){
                    temp=a->phonenumber;
                    auto x= ht->search_chain(1,temp);
                    cout<<x->name<<endl;
                    cout<<x->phonenumber<<endl;
                    cout<<x->key<<endl;
                }
            }
        }

    }
}