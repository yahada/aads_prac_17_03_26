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
  return v.getSize() == 2;
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

bool testPushBack()
{
  topit::Vector< int > v;
  v.pushBack(1);
  bool res = v[0] == 1;
  v.pushBack(2);
  res = res && v[1] == 2;
  return res;
}

bool testPopBack()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.popBack();
  return v[0] == 1 && v.getSize() == 1 && v.getCapacity() == 8;
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

bool testCopyConstructorforEmpty()
{
  topit::Vector< int > v;
  topit::Vector< int > yav = v;
  return v == yav;
}

bool testCopyConstructorforNonEmpty()
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int > yav = v;
  return v == yav;
}

bool testCopyOperatorforEmpty()
{
  topit::Vector< int > v;
  topit::Vector< int > yav;
  yav = v;
  return v == yav;
}

bool testCopyOperatorforNonEmpty()
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int > yav;
  yav = v;
  return v == yav;
}

bool testMoveConstructorforEmpty()
{
  topit::Vector< int > v;
  topit::Vector< int > copyV(v);
  topit::Vector< int > yav(std::move(v));
  try
  {
    v.at(0);
    return false;
  } catch(const std::out_of_range&)
  {
    return yav == copyV;
  }
}

bool testMoveConstructorforNonEmpty()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  topit::Vector< int > copyV(v);
  topit::Vector< int > yav(std::move(v));
  try
  {
    v.at(0);
    return false;
  } catch(const std::out_of_range&)
  {
    return yav == copyV;
  }
}


bool testMoveOperatorforEmpty()
{
  topit::Vector< int > v;
  topit::Vector< int > copyV(v);
  topit::Vector< int > yav;
  yav = std::move(v);
  try
  {
    v.at(0);
    return false;
  } catch(const std::out_of_range&)
  {
    return yav == copyV;
  }
}

bool testMoveOperatorforNonEmpty()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  topit::Vector< int > copyV(v);
  topit::Vector< int > yav;
  yav = std::move(v);
  try
  {
    v.at(0);
    return false;
  } catch(const std::out_of_range&)
  {
    return yav == copyV;
  }
}

int main()
{
  using test_t = std::pair< const char *, bool(*)() > ;
  test_t tests[] = {
    { "Empty vector", testEmptyVector },
    { "Size of vector", testSizeOfVector },
    { "Capacity of vector", testCapacityOfVector },
    { "Push value to the back", testPushBack },
    { "Pop value from back", testPopBack },
    { "Inbound access", testElementInboundAccess },
    { "Out of bound access", testElementOutOfBoundAccess },
    { "Inbound const access", testElementInboundConstAccess },
    { "Out of bound const access", testElementOutOfBoundConstAccess },
    { "Copy constructor for empty vector", testCopyConstructorforEmpty },
    { "Copy constructor for non empty vector", testCopyConstructorforNonEmpty },
    { "Copy operator for empty vector", testCopyOperatorforEmpty },
    { "Copy operator for non empty vector", testCopyOperatorforNonEmpty },
    { "Move constructor for empty vector", testMoveConstructorforEmpty },
    { "Move constructor for non empty vector", testMoveConstructorforNonEmpty },
    { "Move operator for empty vector", testMoveOperatorforEmpty },
    { "Move operator for non empty vector", testMoveOperatorforNonEmpty },
  };
  std::cout << "TESTS\n";
  const size_t count = sizeof(tests) / sizeof(test_t);
  bool pass = true;
  size_t countFailedTests = 0;
  size_t countSuccessTests = 0;
  for (size_t i = 0; i < count; ++i)
  {
    std::cout << std::boolalpha;
    bool res = tests[i].second();
    if (res)
    {
      countSuccessTests++;
    } else
    {
    std::cout << i + 1 << ". " << tests[i].first << ": " << tests[i].second() << '\n';
      countFailedTests++;
    }
    pass = pass && res;
  }

  std::cout << "Successful tests: " << countSuccessTests << '\n';
  std::cout << "Failed tests: " << countFailedTests << '\n';
  std::cout << "RESULT: " << pass << '\n';
}