// Copyright 2021 <geraldy12319@gamil.com>

#ifndef INCLUDE_MSHARED_PTR_HPP_
#define INCLUDE_MSHARED_PTR_HPP_

#include <iostream>
#include <utility>
#include "atomic"

template <typename T>
class SharedPtr {
 private:
  T *pointer;
  std::atomic_uint *counter;

 public:
  SharedPtr();
  explicit SharedPtr(T *ptr);
  SharedPtr(const SharedPtr &r);
  SharedPtr(SharedPtr &&r) noexcept;
  ~SharedPtr();
  auto operator=(const SharedPtr &r) -> SharedPtr &;
  auto operator=(SharedPtr &&r) noexcept -> SharedPtr &;

  // Check if this points to object
  explicit operator bool() const;
  auto operator*() const -> T &;
  auto operator->() const -> T *;

  auto get() -> T *;
  auto get_counter() -> std::atomic_uint *;
  void reset();
  void reset(T *ptr);
  void swap(SharedPtr &r);
  // returns quantity of pointers which point to the same obj
  [[nodiscard]] auto use_count() const -> size_t;
};

template <typename T>
SharedPtr<T>::SharedPtr() : pointer(nullptr), counter(nullptr) {}

template <typename T>
SharedPtr<T>::SharedPtr(T *ptr) : pointer(ptr) {
  if (ptr == nullptr)
    counter = nullptr;
  else
    counter = new std::atomic_uint{1};
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr &r)
    : pointer(r.pointer), counter(r.counter) {
  (*counter)++;
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr &&r) noexcept
    : pointer(std::move(r.pointer)),
      counter(std::move(r.counter)) {
    r.pointer = nullptr;
    r.counter = nullptr;
}

template <typename T>
SharedPtr<T>::~SharedPtr() {
  if (!counter) return;
  if (--(*counter) == 0) {
    // all errors with extra free it's a programmer's problem due to his
    // bad knowledge and understanding of shared ptr
    delete pointer;
    delete counter;
  }
}

template <typename T>
auto SharedPtr<T>::operator=(const SharedPtr &r) -> SharedPtr & {
  if (this == &r) {
    return *this;
  }
  this->~SharedPtr();
  this->pointer = r.pointer;
  this->counter = r.counter;
  (*counter)++;
  return *this;
}

template <typename T>
auto SharedPtr<T>::operator=(SharedPtr &&r) noexcept -> SharedPtr & {
  if (this == &r) {
    return *this;
  }
  this->~SharedPtr();
  pointer = std::move(r.pointer);
  counter = std::move(r.counter);
  r.pointer = nullptr;
  r.counter = nullptr;
  return *this;
}

template <typename T>
SharedPtr<T>::operator bool() const {
  return pointer != nullptr;
}

template <typename T>
auto SharedPtr<T>::operator*() const -> T & {
  return *pointer;
}
template <typename T>
auto SharedPtr<T>::operator->() const -> T * {
  return pointer;
}
template <typename T>
auto SharedPtr<T>::get() -> T * {
  return pointer;
}

template <typename T>
auto SharedPtr<T>::get_counter() -> std::atomic_uint* {
  return counter;
}

template <typename T>
void SharedPtr<T>::reset() {
  // call =(&&) and destructor for this shared ptr is called
  *this = std::move(SharedPtr());
}

template <typename T>
void SharedPtr<T>::reset(T *ptr) {
  // call =(&&) and destructor for this shared ptr is called
  *this = std::move(SharedPtr<T>(ptr));
}

template <typename T>
void SharedPtr<T>::swap(SharedPtr &r) {
  // simple exchange of fields
  std::swap(pointer, r.pointer);
  std::swap(counter, r.counter);
}

template <typename T>
auto SharedPtr<T>::use_count() const -> size_t {
  return static_cast<size_t>(*counter);
}

#endif // INCLUDE_MSHARED_PTR_HPP_
