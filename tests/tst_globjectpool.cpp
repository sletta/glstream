#include <iostream>
#include "globjectpool.h"

int main(int argc, char **argv)
{
    GLObjectPool list;

    std::vector<GLuint> allocated;

    for (int i=0; i<10; ++i)
        allocated.push_back(list.allocate());

    std::cout << std::endl << "10 ids allocated:" << std::endl;
    for (int id : allocated)
        std::cout << " - id=" << id << std::endl;

    for (int i=0; i<10; i+=2)
        list.release(allocated[i]);
    std::cout << std::endl << "after releasing every other id:" << std::endl;
    for (int id : list)
        std::cout << "id: " << id << std::endl;

    list.release(allocated.back());
    std::cout << std::endl << "after releasing the very last element:" << std::endl;
    for (int id : list)
        std::cout << "id: " << id << std::endl;

    for (int i=0; i<10; ++i)
        list.allocate();
    std::cout << std::endl << "after allocating 10 more:" << std::endl;
    for (int id : list)
        std::cout << "id: " << id << std::endl;

    return 0;
}

//
// to compile:
//
// > clang++ -g -std=c++11 -I../src tst_globjectpool.cpp -o tst_globjectpool && ./tst_globjectpool
//