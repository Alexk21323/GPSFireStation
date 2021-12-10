#include <iostream>
#include "binarytree.h"
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    char data;
    binaryTree<char> tree;
    cout<<"Starting!!!"<<endl;
    for(size_t i = 0; i < 25; ++i)
    {
        data = static_cast<char>(rand()%26 + 65);
        cout<<"Trying to input: "<<data<<endl;
        tree<<data;
        cout<<"Input successful!"<<endl;
    }
    cout<<"Your tree contains: "<<tree<<endl<<endl;
    for(size_t i = 0; i < 25; ++i)
    {
        data = static_cast<char>(rand()%26 + 65);
        cout<<"Trying to delete:  "<<data<<endl;
        tree.deleteData(data);
     }
     cout<<"Your tree contains: "<<tree<<endl<<endl;
 return 0;
}
