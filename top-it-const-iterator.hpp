#ifndef TOP_IT_CONST_ITERATOR_HPP
#define TOP_IT_CONST_ITERATOR_HPP
#include <cassert>
#include <cstddef>
namespace topit
{
  template< class T >
  struct VecConstIter {
  public:
    VecConstIter();
    VecConstIter(const T* ptr);
    VecConstIter< T >& operator++();
    VecConstIter< T > operator++(int);

    VecConstIter< T >& operator--();
    VecConstIter< T > operator--(int);

    const T& operator*();
    const T* operator->();

    bool operator!=(const VecConstIter< T >& other) const;
    bool operator==(const VecConstIter< T >& other) const;
  private:
    const T* ptr_;
  };
}

template< class T >
topit::VecConstIter< T >::VecConstIter():
  ptr_(nullptr)
{}


template< class T >
topit::VecConstIter< T >::VecConstIter(const T* ptr):
  ptr_(ptr)
{}

template< class T >
topit::VecConstIter< T >& topit::VecConstIter< T >::operator++()
{
  ++ptr_;
  return *this;
}

template< class T >
topit::VecConstIter< T > topit::VecConstIter< T >::operator++(int)
{
  VecConstIter< T >tmp{*this};
  ++(*this);
  return tmp;
}

template< class T >
topit::VecConstIter< T >& topit::VecConstIter< T >::operator--()
{
  ptr_--;
  return *this;
}

template< class T >
topit::VecConstIter< T > topit::VecConstIter< T >::operator--(int)
{
  VecConstIter< T >tmp{*this};
  --(*this);
  return tmp;
}

template< class T >
const T& topit::VecConstIter< T >::operator*()
{
  return *ptr_;
}

template< class T >
const T* topit::VecConstIter< T >::operator->()
{
  return std::addressof(ptr_);
}

template< class T >
bool topit::VecConstIter< T >::operator!=(const VecConstIter< T >& rhs) const
{
  return !(*this == rhs);
}

template< class T >
bool topit::VecConstIter< T >::operator==(const VecConstIter< T >& rhs) const
{
  return ptr_ == rhs.ptr_;
}

#endif
