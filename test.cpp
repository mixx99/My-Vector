#include "test.h"
#include "simple-bench.h"
#include <iostream>

namespace 
{
  int* arr = nullptr;
  int n;
  void input()
  {
    std::cin >> n;
    arr = new int[n];
    for(int i = 0; i < n; ++i)
      std::cin >> arr[i];
  }
}

void test_push_back(MyVector<int>& myvector, std::vector<int>& vector)
{
  if(arr == nullptr)
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
  //delete[] arr; // ??
}


void test_insert(MyVector<int>& myvector, std::vector<int>& vector)
{
  timespec t1, t2;
  double t;
  if(myvector.get_size() != n - 1 || vector.size() != n - 1)
  {
    for(int i = 0; i < n; ++i)
    {
      vector.push_back(arr[i]);
      myvector.push_back(arr[i]);
    }
  }
  std::cout << "Testing insert. 1000 times N = " << n << std::endl;
  std::cout << "  Sizeof vectors = " << myvector.get_size() << std::endl;

  simple_gettime(&t1);
  for(int i = 0; i < n / 100000; ++i)
    myvector.insert(arr[i], arr[i] % n);
  simple_gettime(&t2);
  t = diff(t1, t2);
  std::cout << "  myvector finished at: " << t << " seconds" << std::endl;

  simple_gettime(&t1);
  for(int i = 0; i < n / 100000; ++i)
  {
    auto it = vector.begin();
    for(int j = 0; j < arr[i] % n; ++j)
      it++;
    vector.insert(it, arr[i]);
  }
  simple_gettime(&t2);

  t = diff(t1, t2);
  std::cout << "  std::vector finished at :" << t << "seconds" << std::endl;
  delete[] arr;
}


