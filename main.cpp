#include "top-it-vector.hpp"
#include <iostream>
#include <iomanip>
#include <utility>

bool testEmptyVector()
{
  topit::Vector< int > v;
  return v.isEmpty();
}

bool testSizeOfVector()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.pushBack(5);
  return v.getSize() == 5;
}

bool testCapacityOfVector()
{
  topit::Vector< int > v;
  bool res = v.getCapacity() == 0;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.pushBack(5);
  res = res && v.getCapacity() == 8;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.pushBack(4);
  v.pushBack(5);
  res = res && v.getCapacity() == 16;
  return res;
}

bool testPushAndPopValue()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);

  bool res = v.getSize() == 3;

  v.popBack();
  v.popBack();

  res = res && v.getSize() == 1;
  return res;
}

bool testElementInboundAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);  
  try
  {
    int& val = v.at(0);
    return val == 1;
  }
  catch(...)
  {
    return false;
  }
}

bool testElementOutOfBoundAccess()
{
  topit::Vector< int > v;
  try
  {
    v.at(0);
    return false;
  }
  catch(const std::out_of_range&)
  {
    return true;
  } catch(...)
  {
    return false;
  }
}

bool testElementInboundConstAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  const topit::Vector< int >& rv = v;
  try
  {
    const int& val = rv.at(0);
    return val == 1;
  }
  catch(...)
  {
    return false;
  }
}

bool testElementOutOfBoundConstAccess()
{
  const topit::Vector< int > v;
  try
  {
    v.at(0);
    return false;
  }
  catch(const std::out_of_range&)
  {
    return true;
  } catch(...)
  {
    return false;
  }
}

int main()
{
  using test_t = std::pair< const char *, bool(*)() > ;
  test_t tests[] = {
    {"Empty vector", testEmptyVector},
    {"Size of vector", testSizeOfVector},
    {"Capacity of vector", testCapacityOfVector},
    {"Push and Pop value", testPushAndPopValue},
    {"Inbound access", testElementInboundAccess},
    {"Out of bound access", testElementOutOfBoundAccess},
    {"Inbound const access", testElementInboundConstAccess},
    {"Out of bound const access", testElementOutOfBoundConstAccess},
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
  //подсчет пройденных/не пройденных тестов
  //выводить только не прошедшие тесты
}