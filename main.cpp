#include <iostream>
#include "MyVector.h"
#include <vector>
#include "test.h"


int main() 
{
  MyVector<int> myvector;
  std::vector<int> vector;
  
  test_push_back(myvector, vector);
  return 0;
}
