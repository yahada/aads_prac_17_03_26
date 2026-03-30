#ifndef TOP_IT_ITERATOR_HPP
#define TOP_IT_ITERATOR_HPP
#include <cassert>
#include <cstddef>
namespace topit
{
  template< class T >
  struct VecIter {
  public:
    VecIter();
    VecIter(T* ptr);
    VecIter< T >& operator++();
    VecIter< T > operator++(int);
    VecIter< T >& operator+(size_t);
    VecIter< T >& operator--();
    VecIter< T > operator--(int);
    VecIter< T >& operator-(size_t);
    std::ptrdiff_t operator-(VecIter< T > other) const;
    T& operator*();
    T* operator->();

    bool operator!=(const VecIter< T >& other) const;
    bool operator==(const VecIter< T >& other) const;
  private:
    T* ptr_;
  };
}

template< class T >
topit::VecIter< T >::VecIter():
  ptr_(nullptr)
{}


template< class T >
topit::VecIter< T >::VecIter(T* ptr):
  ptr_(ptr)
{}

template< class T >
topit::VecIter< T >& topit::VecIter< T >::operator++()
{
  ++ptr_;
  return *this;
}

template< class T >
topit::VecIter< T > topit::VecIter< T >::operator++(int)
{
  VecIter< T >tmp{*this};
  ++(*this);
  return tmp;
}

template< class T >
topit::VecIter< T >& topit::VecIter< T >::operator+(size_t n)
{
  return {ptr_ + n};
}


template< class T >
topit::VecIter< T >& topit::VecIter< T >::operator--()
{
  ptr_--;
  return *this;
}

template< class T >
topit::VecIter< T > topit::VecIter< T >::operator--(int)
{
  VecIter< T >tmp{*this};
  --(*this);
  return tmp;
}

template< class T >
topit::VecIter< T >& topit::VecIter< T >::operator-(size_t n)
{
  return {ptr_ - n};
}

template< class T >
std::ptrdiff_t topit::VecIter< T >::operator-(VecIter< T > other) const
{
  return ptr_ - other.ptr_;
}


template< class T >
T& topit::VecIter< T >::operator*()
{
  return *ptr_;
}

template< class T >
T* topit::VecIter< T >::operator->()
{
  return std::addressof(ptr_);
}

template< class T >
bool topit::VecIter< T >::operator!=(const VecIter< T >& rhs) const
{
  return !(*this == rhs);
}

template< class T >
bool topit::VecIter< T >::operator==(const VecIter< T >& rhs) const
{
  return ptr_ == rhs.ptr_;
}

#endif
