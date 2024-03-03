#include <iostream>
#include "color.hpp"
#include "2105142_MAP.cpp"

using namespace std;

int main()
{
    RedBlackTree tree;
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    string command;
    while (cin >> command && !cin.eof())
    {
        if (command == "I")
        {
            int key;
            string value;
            cin >> key >> value;
            tree.insert(key, value);
            tree.print();
        }
        else if (command == "F")
        {
            int key;
            cin >> key;
            node *result = tree.find(key);
            if (result != nullptr)
            {
                cout << key << " found" << endl;
            }
            else
            {
                cout << key << " Not found" << endl;
            }
        }
        else if (command == "E")
        {
            int key;
            cin >> key;
            node *result = tree.erase(key);
            if (result == nullptr)
            {
                cout << key << " Not found" << endl;
            }
            else
            {
                tree.print();
            }
        }
        else if (command == "S")
        {
            cout << tree.size_tree() << endl;
        }
        else if (command == "Itr")
        {
            tree.iterate();
        }
        else if (command == "Clr")
        {
            bool clr = tree.clear();
            if (clr)
            {
                cout << dye::green_on_black("Successful") << endl;
            }
            else
            {
                cout << dye::red_on_black("Unsuccessful") << endl;
            }
        }
        else if (command == "Em")
        {
            bool em = tree.isempty();
            if (em)
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }
        }
        else
        {
            cout << dye::red_on_black("Invalid Input") << endl;
        }
    }

    return 0;
}
