#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <fstream>

template<typename Data>
struct node
{
    Data data;
    int count;
    node<Data> *gThan, *lThan;

    node(Data d = Data(), int c = 1);
    ~node();
    node(const node<Data> &other);
    node<Data>& operator=(const node<Data> &other);
    node<Data>& operator+=(const node<Data> &other);
    void swap(node<Data> &other);

    template<typename d>
    friend
    bool operator==(const node<d> &x, const node<d> &y);

    template<typename d>
    friend
    bool operator>=(const node<d> &x, const node<d> &y);

    template<typename d>
    friend
    bool operator<=(const node<d> &x, const node<d> &y);


    template<typename d>
    friend
    bool operator!=(const node<d> &x, const node<d> &y);


    template<typename d>
    friend
    bool operator>(const node<d> &x, const node<d> &y);


    template<typename d>
    friend
    bool operator<(const node<d> &x, const node<d> &y);

    template<typename d>
    friend
    std::ostream& operator<<(std::ostream& out, const node<d> &other);

    template<typename d>
    friend
    std::istream& operator>>(std::istream& out, const node<d> &other);
};

template<typename Data>
node<Data>::node(Data d, int c)
{
    data = d;
    count = c;
    gThan = lThan = nullptr;
}

template<typename Data>
node<Data>::~node()
{
    data = Data();
    count = 0;
    gThan = lThan = nullptr;
}

template<typename Data>
node<Data>::node(const node<Data> &other)
{
    data = other.data;
    count = other.count;
    gThan = lThan = nullptr;
}

template<typename Data>
node<Data>& node<Data>::operator=(const node<Data> &other)
{
    if(this != &other)
    {
        data = other.data;
        count = other.count;
        gThan = lThan = nullptr;
    }
    return *this;
}

template<typename Data>
node<Data>& node<Data>::operator+=(const node<Data> &other)
{
    if((this != &other) && (data == other.data))
        count += other.count;
    return *this;
}


template<typename Data>
void node<Data>::swap(node<Data> &other)
{
    Data temp = data;
    data = other.data;
    other.data = temp;

    int t = count;
    count = other.count;
    other.count = t;
}

template<typename d>
std::ostream& operator<<(std::ostream& out, const node<d> &other)
{
    out<<other.data<<"["<<other.count<<"] ";
    return out;
}

template<typename d>
std::istream& operator>>(std::istream& in, node<d> &other)
{
    char junk;
    if(&in == &std::cin)
    {
        std::cout<<"Data: ";
        in>>other.data;
        std::cout<<"Count: ";
        in>>other.count;
    }
    else
    {
        in>>other.data>>junk>>other.count>>junk;
    }
    return in;
}

template<typename d>
bool operator==(const node<d> &x, const node<d> &y)
{
    return x.data == y.data;
}

template<typename d>
bool operator>=(const node<d> &x, const node<d> &y)
{
    return x.data >= y.data;
}

template<typename d>
bool operator<=(const node<d> &x, const node<d> &y)
{
    return x.data <= y.data;
}

template<typename d>
bool operator!=(const node<d> &x, const node<d> &y)
{
    return x.data != y.data;
}

template<typename d>
bool operator>(const node<d> &x, const node<d> &y)
{
    return x.data > y.data;
}

template<typename d>
bool operator<(const node<d> &x, const node<d> &y)
{
    return x.data < y.data;
}


#endif // NODE_H
