#include "top-it-vector.hpp"
#include <iostream>
#include <iomanip>
#include <utility>
#include <initializer_list>
#include "top-it-iterator.hpp"

bool testIsEmpty()
{
  topit::Vector< int > v;
  return v.isEmpty();
}

bool testGetSize()
{
  topit::Vector< int > v({1, 2});
  return v.getSize() == 2;
}

bool testGetCapacity()
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
  return res && v.getCapacity() == 16;
}

bool testShrimpToFit()
{
  topit::Vector< int > v({1, 2, 3, 4});
  v.shrimpToFit();
  return v.getSize() == 4 && v.getCapacity() == 4;
}

bool testReserveInEmpty()
{
  topit::Vector< int > v;
  v.reserve(4);
  return v.getCapacity() == 4;
}

bool testReserveInNonEmpty()
{
  topit::Vector< int > v({1, 2, 3});
  v.reserve(4);
  return v.getCapacity() == 4 && (v[0] == 1) && (v[1] == 2) && (v[2] == 3);
}



bool testBegin()
{
  topit::Vector< int > v({1, 2});
  topit::VecIter< int > it = v.begin();
  return *(it) == 1;
}

bool testConstBegin()
{
  topit::Vector< int > v({1, 2});
  topit::VecConstIter< int > it = v.cbegin();
  return *(it) == 1;
}

bool testEnd()
{
  topit::Vector< int > v({1, 2});
  topit::VecIter< int > it = --v.end();
  return *(it) == 2;
}

bool testConstEnd()
{
  topit::Vector< int > v({1, 2});
  topit::VecConstIter< int > it = --v.cend();
  return *(it) == 2;
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
  topit::Vector< int > v({1});
  topit::Vector< int > yav = v;
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

bool testCopyOperatorforEmpty()
{
  topit::Vector< int > v;
  topit::Vector< int > yav;
  yav = v;
  return v == yav;
}

bool testCopyOperatorforNonEmpty()
{
  topit::Vector< int > v({1});
  topit::Vector< int > yav;
  yav = v;
  return v == yav;
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


bool testEmptyInitializerList()
{
  topit::Vector< int > v({});
  topit::Vector< int > yav;
  return yav == v;
}

bool testNonEmptyInitializerList()
{
  topit::Vector< int > v({1, 2});
  return v.getSize() == 2 && (v[0] == 1) && (v[1] == 2);
}



bool testPushBack()
{
  topit::Vector< int > v;
  v.pushBack(1);
  bool res = v[0] == 1;
  v.pushBack(2);
  return res && v[1] == 2;
}

bool testPushBackCount()
{
  topit::Vector< int > v;
  v.pushBackCount(2, 4);
  bool res = (v[0] == 4) && (v[1] == 4) && v.getSize() == 2 && v.getCapacity() == 8;
  v.pushBackCount(2, 5);
  return res && (v[2] == 5) && (v[3] == 5) && v.getSize() == 4 && v.getCapacity() == 8;
}

bool testPushBackWithBeginRange()
{
  topit::Vector< int > v({1, 2});
  topit::Vector< int > yav({3, 4, 5, 6});
  v.pushBackRange(yav.begin(), 2);
  return (v[2] == 3) && (v[3] == 4);
}

bool testPushBackWithMiddleRange()
{
  topit::Vector< int > v({1, 2});
  topit::Vector< int > yav({3, 4, 5, 6});
  v.pushBackRange(yav.begin() + 1, 2);
  return (v[2] == 4) && (v[3] == 5);
}

bool testPopBackEmpty()
{
  topit::Vector< int > v;
  v.popBack();
  topit::Vector< int > yav;
  return v == yav;
}

bool testPopBackNonEmpty()
{
  topit::Vector< int > v({1, 2});
  v.popBack();
  return (v[0] == 1) && v.getSize() == 1;
}

bool testInsertElementIntoBeginOfEmpty()
{
  topit::Vector< int > v;
  v.insert(0, 4);
  return v.getSize() == 1 && (v[0] == 4);
}

bool testInsertElementIntoNotBeginOfEmpty()
{
  topit::Vector< int > v;
  try
  {
    v.insert(1, 4);
    return false;
  }
  catch(const std::out_of_range&)
  {
    return true;
  }
}

bool testInsertInRangeOfNonEmpty()
{
  topit::Vector< int > v({1, 2, 3});
  v.insert(1, 4);
  return v.getSize() == 4 && (v[0] == 1) && (v[1] == 4) && (v[2] == 2) && (v[3] == 3);
}

bool testInsertElementOutOfRangeOfNonEmpty()
{
  topit::Vector< int > v({1, 2, 3});
  try
  {
    v.insert(5, 4);
    return false;
  }
  catch(const std::out_of_range&)
  {
    return true;
  }
}


bool testInsertFewElementsIntoEmptyVector()
{
  topit::Vector< int > v({1, 2, 3});

  topit::Vector< int > yav;
  yav.insert(0, v, 0, 3);

  return yav[0] == 1 && yav[1] == 2 && yav[2] == 3;
}

bool testInsertFewElementsIntoNonEmptyVector()
{
  topit::Vector< int > v({2, 3, 4});

  topit::Vector< int > yav({1, 5, 6});

  yav.insert(1, v, 0, 3);

  return yav[0] == 1 && yav[1] == 2 && yav[2] == 3 && yav[3] == 4 && yav[4] == 5 && yav[5] == 6;
}

bool testInsertElementWithIteratorIntoNonEmpty()
{
  topit::Vector< int > v({1, 2, 3, 4});
  topit::VecIter< int > it = v.begin();
  v.insert(it + 1, 4);
  return (v[0] == 1) && (v[1] == 4) && (v[2] == 2) && (v[3] == 3);
}

bool testInsertElementWithIteratorIntoEmpty()
{
  topit::Vector< int > v;
  topit::VecIter< int > it = v.begin();
  v.insert(it, 4);
  return v.getSize() == 1 && (v[0] == 4);
}

bool testInsertSameElementsWithIterator()
{
  topit::Vector< int > v;
  topit::VecIter< int > it = v.begin();
  v.insert(it, 2, 4);
  bool res = (v[0] == 4) && (v[1] == 4);
  v.insert(v.end(), 2, 5);
  return res && v[2] == 5 && v[3] == 5;
}

bool testInsertElementsFromAnotherVecWithIterator()
{
  topit::Vector< int > v({4, 5, 6});

  topit::Vector< int > yav({1, 2, 3});

  topit::VecIter< int > it = v.begin();
  v.insert(it, yav.begin(), 3);
  return v.getSize() == 6 && (v[0] == 1) && (v[1] == 2) && (v[2] == 3);
}

bool testEraseElementInEmpty()
{
  topit::Vector< int > v;
  try
  {
    v.erase(0);
    return false;
  }
  catch(const std::out_of_range&)
  {
    return true;
  }
}

bool testEraseElementInNonEmpty()
{
  topit::Vector< int > v({1, 2, 3});
  v.erase(0);
  v.erase(1);
  return v.getSize() && (v[0] == 2);
}

bool testEraseFewElementsInEmpty()
{
  topit::Vector< int > v;
  try
  {
    v.erase(0, 4);
    return false;
  }
  catch(const std::out_of_range&)
  {
    return true;
  }
}

bool testEraseFewElementsInNonEmpty()
{
  topit::Vector< int > v({1, 2, 3, 4, 5});
  v.erase(1, 3);
  bool res = v[0] == 1 && v[1] == 4 && v[2] == 5;
  v.erase(0, 2);
  return res && v[0] == 5;
}

bool testEraseFewElementsOutOfRangeInNonEmpty()
{
  topit::Vector< int > v({1, 2, 3, 4, 5});
  try
  {
    v.erase(1, 6);
    return false;
  }
  catch(const std::out_of_range&)
  {
    return true;
  }
}

bool testEraseElementWithIteratorInNonEmpty()
{
  topit::Vector< int > v({1, 2, 3});
  v.erase(v.begin());
  return v[0] == 2 && v[1] == 3;
}

bool testEraseElementWithIteratorInEmpty()
{
  topit::Vector< int > v({1, 2, 3});
  try
  {
    v.erase(v.begin());
    return false;
  }
  catch(const std::out_of_range&)
  {
    return true;
  }
}


bool testEraseFewElementsWithIterator()
{
  topit::Vector< int > v({1, 2, 3, 4, 5, 6});
  v.erase(v.begin(), 3);
  return v[0] == 4 && v[1] == 5 && v[2] == 6;
}

bool testEraseFewElementsWithIteratorOutOfRange()
{
  topit::Vector< int > v({1, 2});
  try
  {
    v.erase(v.begin(), 3);
    return false;
  }
  catch(const std::out_of_range& e)
  {
    return true;
  }
}

bool testEraseRangeOfElementsWithIterator()
{
  topit::Vector< int > v({1, 2, 3, 4, 5, 6});
  topit::VecIter< int > itS = v.begin();
  topit::VecIter< int > itE = v.begin() + 2;
  v.erase(itS, itE);
  return v[0] == 3 && v[1] == 4 && v[2] == 5;
}

bool testEraseRangeOfElementsWithIteratorOutOfRange()
{
  topit::Vector< int > v({1, 2});
  try
  {
    topit::VecIter< int > itS = v.begin();
    topit::VecIter< int > itE = v.begin() + 4;
    v.erase(itS, itE);
    return false;
  }
  catch(const std::out_of_range& e)
  {
    return true;
  }
}





int main()
{
  using test_t = std::pair< const char *, bool(*)() > ;
  test_t tests[] = {
    { "Is empty vector", testIsEmpty },
    { "Size of vector", testGetSize },
    { "Capacity of vector", testGetCapacity },
    { "Shrimp to fit", testShrimpToFit},
    { "Reserve in empty", testReserveInEmpty},
    { "Reserve in non empty", testReserveInNonEmpty},

    { "Begin of the vector", testBegin},
    { "Const begin of the vector", testConstBegin},
    { "End of the vector", testEnd},
    { "Const end of the vector", testConstEnd},

    { "Inbound access", testElementInboundAccess },
    { "Out of bound access", testElementOutOfBoundAccess },
    { "Inbound const access", testElementInboundConstAccess },
    { "Out of bound const access", testElementOutOfBoundConstAccess },

    { "Copy constructor for empty vector", testCopyConstructorforEmpty },
    { "Copy constructor for non empty vector", testCopyConstructorforNonEmpty },
    { "Move constructor for empty vector", testMoveConstructorforEmpty },
    { "Move constructor for non empty vector", testMoveConstructorforNonEmpty },
    { "Copy operator for empty vector", testCopyOperatorforEmpty },
    { "Copy operator for non empty vector", testCopyOperatorforNonEmpty },
    { "Move operator for empty vector", testMoveOperatorforEmpty },
    { "Move operator for non empty vector", testMoveOperatorforNonEmpty },

    { "Empty vector for empty initializer list", testEmptyInitializerList},
    { "Non-empty vector for non-empty initializer list", testNonEmptyInitializerList},

    { "Push back value", testPushBack },
    { "Push back few same elements", testPushBackCount},
    { "Push back few elements from the begining of another vector", testPushBackWithBeginRange},
    { "Push back few elements from the middle of another vector", testPushBackWithMiddleRange},
    { "Pop back empty vector", testPopBackEmpty },
    { "Pop back non empty vector", testPopBackNonEmpty },

    { "Insert element into begin of empty vector", testInsertElementIntoBeginOfEmpty},
    { "Insert element out of range of empty vector ", testInsertElementIntoNotBeginOfEmpty},
    { "Insert element in range of non empty vector", testInsertInRangeOfNonEmpty},
    { "Insert element out of range of non empty vector", testInsertElementOutOfRangeOfNonEmpty},
    { "Insert few elements into empty vector", testInsertFewElementsIntoEmptyVector},
    { "Insert few elements into non empty vector", testInsertFewElementsIntoNonEmptyVector},
    { "Insert element with iterator into empty", testInsertElementWithIteratorIntoEmpty},
    { "Insert element with iterator into non empty", testInsertElementWithIteratorIntoNonEmpty},
    { "Insert same elements with iterator", testInsertSameElementsWithIterator},
    { "Insert elements from another vector with iterator", testInsertElementsFromAnotherVecWithIterator},

    { "Erase element in empty vector", testEraseElementInEmpty},
    { "Erase element in non empty vector", testEraseElementInNonEmpty},
    { "Erase few elements in empty vector", testEraseFewElementsInEmpty},
    { "Erase few elements in non empty vector", testEraseFewElementsInNonEmpty},
    { "Erase few elements in non empty vector with wrong range", testEraseFewElementsOutOfRangeInNonEmpty},
    { "Erase element with iterator in non empty", testEraseElementWithIteratorInNonEmpty},
    { "Erase element with iterator in empty", testEraseElementWithIteratorInNonEmpty},
    { "Erase few elements with iterator", testEraseFewElementsWithIterator},
    { "Erase few elements with iterator out of range", testEraseFewElementsWithIteratorOutOfRange},
    { "Erase range of elements with iterator", testEraseRangeOfElementsWithIterator},
    { "Erase range of elements with iterator out of range", testEraseRangeOfElementsWithIteratorOutOfRange},
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