#include "test.h"
#include "simple-bench.h"
#include <iostream>

namespace 
{
  std::vector<int> arr;
  int n;
  void input()
  {
    std::cin >> n;
    for(int i = 0; i < n; ++i)
    {
      int temp;
      std::cin >> temp;
      arr.push_back(temp);
    }
  }
}

void test_push_back(MyVector<int>& myvector, std::vector<int>& vector)
{
  if(arr.size() == 0)
    input();
  timespec t1, t2;
  double t;
  simple_gettime(&t1);
  for(int j = 0; j < 1000; ++j)
  for(int i = 0; i < n; ++i)
    myvector.push_back(arr[i]);

  simple_gettime(&t2);
  t = diff(t1, t2);

  std::cout << "Testing push_back. 1000 times with N = " << n << std::endl;
  std::cout << "  MyVector finished at: " << t << " seconds" << std::endl;

  simple_gettime(&t1);
  for(int j = 0; j < 1000; ++j)
  for(int i = 0; i < n; ++i)
    vector.push_back(arr[i]);
  simple_gettime(&t2);
  t = diff(t1, t2);
  std::cout << "  std::vector finished at: " << t << " seconds" << std::endl;
}


void test_insert(MyVector<int>& myvector, std::vector<int>& vector)
{
  if(arr.size() == 0)
    input();
  const int NUMBERS_TO_INSERT = 100;
  timespec t1, t2;
  double t;

  std::cout << "Testing insert. Insert " << NUMBERS_TO_INSERT << " numbers." << std::endl;
  std::cout << "  Sizeof vectors = " << myvector.get_size() << std::endl;

  simple_gettime(&t1);
  for(int i = 0; i < NUMBERS_TO_INSERT; ++i)
    myvector.insert(arr[i], arr[i] % myvector.get_size());
  simple_gettime(&t2);
  t = diff(t1, t2);
  std::cout << "  MyVector finished at: " << t << " seconds" << std::endl;

  simple_gettime(&t1);
  for(int i = 0; i < NUMBERS_TO_INSERT; ++i)
  {
    auto it = vector.begin();
    for(int j = 0; j < arr[i] % n; ++j)
      it++;
    vector.insert(it, arr[i]);
  }
  simple_gettime(&t2);

  t = diff(t1, t2);
  std::cout << "  std::vector finished at :" << t << " seconds" << std::endl;
}


