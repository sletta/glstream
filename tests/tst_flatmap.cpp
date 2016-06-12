#include <iostream>
#include "flatmap.h"

int main(int argc, char **argv)
{
    FlatMap<int, int> map;

    map.insert(1, 10);
    map.insert(3, 30);
    map.insert(0, 00);
    map.insert(2, 20);
    map.insert(6, 60);
    map.insert(8, 80);
    map.insert(4, 40);

    std::cout << "Map contains: " << map.size() << " entries.." << std::endl;
    for (auto e : map) {
        std::cout << " - " << e.key << ": " << e.value << std::endl;
    }

    std::cout << "Map contains 10: " << map.contains(10) << std::endl;
    std::cout << "Map contains 1: " << map.contains(1) << std::endl;

    map.remove(0);
    map.remove(8);
    map.remove(3);

    std::cout << "after remove..." << std::endl << "Map contains: " << map.size() << " entries.." << std::endl;
    for (auto e : map) {
        std::cout << " - " << e.key << ": " << e.value << std::endl;
    }

    std::cout << "checking find()" << std::endl;
    for (int i=0; i<10; ++i)
        std::cout << " - " << i << ": " << map.find(i, -1) << std::endl;




    return 0;
}

//
// to compile:
//
// > clang++ -g -std=c++11 -I../src tst_flatmap.cpp -o tst_flatmap && ./tst_flatmap
//