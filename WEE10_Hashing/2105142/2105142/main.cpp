#include <bits/stdc++.h>
using namespace std;
#define llint long long int
#include "hash.cpp"

string generateRandomWord()
{
    static const char alphabet[] = "abcdefghijklmnopqrstuvwXyz";
    static bool initialized = false;

    if (!initialized)
    {
        srand(time(NULL));
        initialized = true;
    }

    int length = rand() % 6 + 5;
    std::string word;

    for (int i = 0; i < length; ++i)
    {
        word += alphabet[rand() % (sizeof(alphabet) - 1)];
    }
    // cout<<word<<" "<<word.size()<<endl;
    return word;
}

vector<string> generateSets(llint N)
{
    set<string> stringData;
    set<llint> data;
    while (stringData.size() != N)
    {
        string s = generateRandomWord();
        stringData.insert(s);
    }
    vector<string> result(stringData.begin(), stringData.end());
    return result;
}
vector<string> generateDataToSearch(vector<string> allData, llint iNeedThisMuch)
{
    vector<string> result;
    vector<string> tempData = allData;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(tempData.begin(), tempData.end(), default_random_engine(seed));
    result.assign(tempData.begin(), tempData.begin() + iNeedThisMuch);
    return result;
}
void generate_Report()
{
    cout << "Value of C for seperate chaining : " << endl;
    llint C = 100;
    // cin>>C;
    auto data = generateSets(10000);
    llint N = data.size();
    vector<string> search_data = generateDataToSearch(data, (int)(0.1 * N));
    int table_size[] = {5000, 10000, 20000};
    double report[3][3][2][2];

    int k = 0;

    for (auto X : table_size)
    {
        // cout << k << " " << X << endl;
        for (llint i = 1; i <= 2; i++)
        {
            hashTable *chainTable = new hashTable(X, C);
            for (llint j = 0; j < N; j++)
            {
                chainTable->insert_chain(i, data[j], j + 1);
            }

            chainTable->resetProb();

            for (llint j = 0; j < (int)(0.1 * N); j++)
            {
                auto l = chainTable->search_chain(i, data[j]);
            }

            report[k][0][i - 1][0] = chainTable->getCollitionCounter();
            report[k][0][i - 1][1] = (double)chainTable->getProbeCounter() / ((int)(0.1 * N));
        }
        // cout << "ALL_OK 78" << endl;
        for (llint i = 1; i <= 2; i++)
        {
            hashTable *doubleTable = new hashTable(X, C);

            for (llint j = 0; j < N; j++)
            {
                doubleTable->insert_double(i, data[j], j + 1);
            }

            // cout<<(int)(0.1*N)<<endl;
            for (llint j = 0; j < (int)(0.1 * N); j++)
            {
                auto l = doubleTable->search_double(i, search_data[j]);
            }
            report[k][1][i - 1][0] = doubleTable->getCollitionCounter();
            report[k][1][i - 1][1] = (double)doubleTable->getProbeCounter() / (int)(0.1 * N);
        }

        // cout << "ALL_OK 97" << endl;

        for (int i = 1; i <= 2; i++)
        {
            hashTable *customTable = new hashTable(X, C);
            for (int j = 0; j < N; j++)
            {
                customTable->insert_custom(i, data[j], j + 1);
            }
            // cout << "ALL_OK 107" << endl;
            for (int j = 0; j < (int)(0.1 * N); j++)
            {
                auto l = customTable->search_custom(i, search_data[j]);
            }
            // cout << "ALL_OK 117" << endl;
            report[k][2][i - 1][0] = customTable->getCollitionCounter() ;
            report[k][2][i - 1][1] = (double)customTable->getProbeCounter() / (int)(0.1 * N);
        }
        // cout << "ALL_OK 114" << endl;
        k++;
    }

    int i = 0;
    cout << " " << setw(68) << setfill('_') << "" << endl;
    cout << setfill(' ');
    cout << "| Hash       | Collision         | Hash Function 1 | Hash Function 2 |" << endl;
    cout << "| Table Size | Resolution Method | Colls. | Probes | Colls. | Probes |" << endl;
    cout << "|" << setw(69) << setfill('_') << "|" << endl;
    cout << setfill(' ');

    for (long long n : table_size)
    {
        std::cout << "| N = " << std::setw(7) << std::left << table_size[i];

        for (long long j = 0; j < 3; j++)
        {
            if (j == 0)
                std::cout << "| Separate Chaining | ";
            else if (j == 1)
                std::cout << "|" << std::setw(34) << std::right << "| Double Hashing    | ";
            else
                std::cout << "|" << std::setw(34) << std::right << "| Custom Probing    | ";

            for (long long k = 0; k < 2; k++)
            {
                for (long long m = 0; m < 2; m++)
                {
                    if (m == 0)
                        std::cout << std::defaultfloat << std::setw(5) << std::setprecision(5) << std::right << report[i][j][k][m] << "  ";
                    if (m == 1)
                        std::cout << std::fixed << std::setw(2) << std::setprecision(3) << " " << report[i][j][k][m] << "  ";
                }

                std::cout << "| ";
            }

            std::cout << std::endl;
        }

        std::cout << "|" << std::setw(69) << std::setfill('_') << "|" << std::endl;
        std::cout << std::setfill(' ');
        i++;
    }
}

int main()
{
    // freopen("Report1.txt","w",stdout);
    generate_Report();
}
