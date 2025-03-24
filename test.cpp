#include "test.h"

void test_push_back(MyVector<int>& myvector, std::vector<int>& vector)
{
  int n;
  std::cin >> n;
  int* arr;
  arr = new int[n];
  for(int i = 0; i < n; ++i)
    std::cin >> arr[i];

  timespec t1, t2;
  double t;
  simple_gettime(&t1);
  for(int j = 0; j < 1000; ++j)
  for(int i = 0; i < n; ++i)
    myvector.push_back(arr[i]);

  simple_gettime(&t2);
  t = diff(t1, t2);

  std::cout << "Testing push_back. 1000 times with N = " << n << '\n';
  std::cout << "MyVector finished at: " << t << " seconds\n";

  simple_gettime(&t1);
  for(int j = 0; j < 1000; ++j)
  for(int i = 0; i < n; ++i)
    vector.push_back(arr[i]);
  simple_gettime(&t2);
  t = diff(t1, t2);
  std::cout << "std::vector finished at: " << t << " seconds\n";
  delete[] arr;
}

