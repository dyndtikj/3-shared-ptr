// Copyright 2021 <geraldy12319@gamil.com>

#ifndef INCLUDE_MSHARED_PTR_HPP_
#define INCLUDE_MSHARED_PTR_HPP_

#include "atomic"

// template class
template <typename T>
class SharedPtr {
 private:
  T* pointer;
  std::atomic_uint* counter;

 public:
 // SharedPtr() : pointer{nullptr}, counter(nullptr){}

  SharedPtr();

  explicit SharedPtr(T* ptr);

  SharedPtr(const SharedPtr& r);    // copy constructor
  SharedPtr(SharedPtr&& r);         // move constructor
  ~SharedPtr();

  auto operator =(const SharedPtr& r) -> SharedPtr& ; // copy ptr, count++
  auto operator =(SharedPtr&& r) -> SharedPtr& ;    // move ptr.object and count

  operator bool() const ;
  auto operator*() const -> T& ;
  auto operator->() const -> T*;

  auto get() -> T*;
  auto use_count() const -> std::size_t;

  void reset();
  void reset(T* ptr);
  void swap(SharedPtr& r);
};

#endif // INCLUDE_MSHARED_PTR_HPP_
