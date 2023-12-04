
#include <iostream>
#include "MyVector.h"
#include <vector>


int main()
{
    MyVector<int> s(50);
    s.push_back(1);
    s.push_back(2);
    s.push_back(3);
    s.push_back(4);
    s.push_back(5);
    s.push_back(6);
    s.push_back(7);
    s.erase(3);
    s.erase(5);
    s;
}