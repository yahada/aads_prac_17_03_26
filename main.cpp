#include "top-it-vector.hpp"
#include <iostream>
#include <iomanip>
#include <utility>

bool testEmptyVector()
{
  topit::Vector< int > v;
  return v.isEmpty();
}

bool testSizeAndCapacityOfVector()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.pushBack(5);
  return v.getSize() == 5 && v.getCapacity() == 5;
}

bool testPushAndPopOfVector()
{
  topit::Vector< int > v;
  bool res;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.pushBack(5);
  res = v.getCapacity() == 5 && v.getSize() == 5;
  v.popBack();
  v.popBack();
  res = res && v.getCapacity() == 3 && v.getSize() == 3;
  return res;
}

int main()
{
  using test_t = std::pair< const char *, bool(*)() > ;
  test_t tests[] = {
    {"Empty vector", testEmptyVector},
    {"Size of vector", testSizeAndCapacityOfVector},
    {"Capacity of vector", testPushAndPopOfVector}
  };
  const size_t count = sizeof(tests) / sizeof(test_t);
  bool pass = true;
  for (size_t i = 0; i < count; ++i)
  {
    std::cout << std::boolalpha;
    bool res = tests[i].second();
    std::cout << tests[i].first << ": " << tests[i].second() << '\n';
    pass = pass && res;
  }
  std::cout << "RESULT: " << pass << '\n';
}