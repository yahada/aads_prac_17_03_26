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

    VecIter< T >& operator--();
    VecIter< T > operator--(int);

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
T& topit::VecIter< T >::operator*()
{
  return data_[pos_];
}

template< class T >
T* topit::VecIter< T >::operator->()
{
  return std::addressof(data_[pos_]);
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
