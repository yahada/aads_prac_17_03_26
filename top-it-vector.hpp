#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cstddef>
#include <iostream>
namespace topit
{
  template< class T >
  struct Vector {
  public:
    ~Vector();

    Vector();
    Vector(const Vector&);
    Vector(Vector&&) noexcept;
    Vector(size_t size, const T& init);

    Vector& operator=(const Vector&);
    Vector& operator=(Vector&&) noexcept;

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;

    T& at(size_t it);
    const T& at(size_t it) const;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    void pushBack(const T& v);
    void popBack();
    void insert(size_t i, const T& v);
    void erase(size_t i);
    void swap(Vector< T >& rhs) noexcept;

  private:
    void extend(T** oldData, size_t& k, const T& newT);
    explicit Vector(size_t size);
    T* data_;
    size_t size_, capacity_;
  };
  template< class T >
  bool operator==(const Vector< T >& rhs, const Vector< T >& lhs);

}

template< class T >
bool topit::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}

template< class T >
size_t topit::Vector< T >::getSize() const noexcept
{
  return size_;
}

template< class T >
size_t topit::Vector< T >::getCapacity() const noexcept
{
  return capacity_;
}

template< class T >
void topit::Vector< T >::extend(T** oldData, size_t& k, const T& newT)
{
  T* newData = nullptr;
  try
  {
    newData = new T[k * 2];
    for (size_t i = 0; i < k; ++i)
    {
      newData[i] = (*oldData)[i];
    }
    newData[k++] = newT;
  }
  catch(...)
  {
    delete[] newData;
    throw;
  }

  delete[] *oldData;
  *oldData = newData;
}

template< class T >
T& topit::Vector< T >::operator[](size_t id) noexcept
{
  const Vector< T >* cthis = this;
  return const_cast< T& >((*cthis)[id]);
}


template< class T >
const T& topit::Vector< T >::operator[](size_t id) const noexcept
{
  return data_[id];
}

template< class T >
void topit::Vector< T >::swap(Vector< T >& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}
template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(const Vector< T >& rhs)
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }
  Vector< T > cpy(rhs);
  swap(this, rhs);
  return *this;
}

template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(Vector< T >&& rhs) noexcept
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }
  Vector< T >cpy(std::move(rhs));
  swap(cpy);
  return *this;
}

template< class T >
topit::Vector< T >::Vector(const Vector& rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < rhs.getSize(); ++i)
  {
    data_[i] = rhs[i];
  }
}

template< class T >
topit::Vector< T >::Vector(size_t size):
  data_(size ? new T[size]: nullptr),
  size_(size),
  capacity_(size_)
{}

template< class T >
topit::Vector< T >::Vector(size_t size, const T& init):
  Vector(size)
{
  for (size_t i = 0; i < size; ++i)
  {
    data_[i] = init;
  }
}

template< class T >
topit::Vector< T >::Vector(Vector< T >&& rhs) noexcept:
  data_(rhs.data_),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
{
  rhs.data_ = nullptr;
}

template< class T >
bool topit::operator==(const Vector< T >& rhs, const Vector< T >& lhs)
{
  bool isEqual = lhs.getSize() == rhs.getSize();
  for (size_t i = 0; (i < lhs.getSize()) && (isEqual = isEqual && lhs[i] == rhs[i]); ++i);
  return isEqual;
}

template< class T >
T& topit::Vector< T >::at(size_t id)
{
  const Vector< T >* cthis = this;
  return const_cast< T& >(cthis->at(id));
}



template< class T >
const T& topit::Vector< T >::at(size_t id) const
{
  if (id < getSize())
  {
    return (*this)[id];
  }
  throw std::out_of_range("bad id");
}

template< class T >
void topit::Vector< T >::pushBack(const T& v)
{
  if (capacity_ == 0)
  {
    data_ = new T[8];
    capacity_ = 8;
  } else if (size_ >= capacity_)
  {
    extend(&data_, size_, v);
    capacity_ *= 2;
    return;
  }

  data_[size_] = v;
  size_++;
}

template< class T >
void topit::Vector< T >::popBack()
{
  if (!size_)
  {
    return;
  }

  T* newData = nullptr;
  try
  {
    newData = new T[capacity_ - 1];
    for (size_t i = 0; i < size_ - 1; ++i)
    {
      newData[i] = data_[i];
    }
    delete[] data_;
    data_ = newData;
    --capacity_;
    --size_;
  }
  catch(...)
  {
    delete[] newData;
    throw;
  }
}

template< class T >
topit::Vector< T >::~Vector()
{
  delete[] data_;
}

template< class T >
topit::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}
#endif