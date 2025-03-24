#include <iostream>
#include "MyVector.h"
#include <vector>
#include "test.h"


int main() 
{
  MyVector<int> myvector;
  std::vector<int> vector;
  
  test_push_back(myvector, vector);
  test_insert(myvector, vector);
  //int* a = new int;
  return 0;
}
