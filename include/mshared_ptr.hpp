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
  SharedPtr() : pointer{nullptr}, counter(nullptr){}

  explicit SharedPtr(T* ptr)
      : pointer{ptr}, counter(new std::atomic_uint) {
    *counter = 1;
  }


  SharedPtr(const SharedPtr& r) // copy constructor
      : pointer(r.pointer), counter(r.counter) {
    ++(*counter);
  }

  SharedPtr(SharedPtr&& r) // move constructor
      : pointer(std::move(r.pointer)),
        counter(std::move(r.counter)) {
    ++(*counter);
  }

  ~SharedPtr() {
    if (*counter == 1) {
      delete counter;
      counter = nullptr;
      pointer = nullptr;
    } else {
      --(*counter);
    }
  }
  // copy ptr, count++
  auto operator =(const SharedPtr<T>& r) -> SharedPtr<T>&{
    this->pointer = r.pointer;
    this->counter = r.counter;
    if (counter != nullptr) {
      ++(*counter);
    }
    return *this;
  }

  auto operator=(SharedPtr&& r) -> SharedPtr& { // move ptr.object and count
    this->reset();
    this->pointer = r.pointer;
    this->counter = r.counter;
    if (counter != nullptr) {
      ++(*counter);
    }
    return *this;
  }

  operator bool() const { return pointer; }

  auto operator*() const -> T& { return *pointer; }

  auto operator->() const -> T* { return pointer; }

  auto get() -> T* { return pointer; }

  auto use_count() const -> std::size_t { return *counter; }

  void reset() {
    if (counter != nullptr) {
      if (*counter != 1) {
        --(*counter);     // other pointers can point to the object
      } else {
        delete pointer;
        delete counter;
      }
      pointer = nullptr;
      counter = nullptr;
    }
  }

  void reset(T* ptr) {
    if (counter != nullptr) {
      --(*counter);
    }
    counter = new std::atomic_uint;
    *counter = 1;
    pointer = ptr;
  }

  void swap(SharedPtr& r) {
    SharedPtr<T> temp(r);
    r = *this;
    *this = temp;
  }
};

#endif // INCLUDE_MSHARED_PTR_HPP_
