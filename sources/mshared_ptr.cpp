// Copyright 2021 Your Name <your_email>

#include <stdexcept>
#include <mshared_ptr.hpp>

  template <typename T>
  SharedPtr<T>::SharedPtr() : pointer{nullptr}, counter(nullptr){};

  template <typename T>
  SharedPtr<T>::SharedPtr(T* ptr)
      : pointer{ptr}, counter(new std::atomic_uint) {
    *counter = 1;
  };

  template <typename T>
  SharedPtr<T>::SharedPtr(const SharedPtr& r) // copy constructor
      : pointer(r.pointer), counter(r.counter) {
    ++(*counter);
  };

  template <typename T>
  SharedPtr<T>::SharedPtr(SharedPtr&& r) // move constructor
      : pointer(std::move(r.pointer)),
        counter(std::move(r.counter)) {
    ++(*counter);
  };

  template <typename T>
  SharedPtr<T>::~SharedPtr() {
    if (*counter == 1) {
      delete counter;
      counter = nullptr;
      pointer = nullptr;
    } else {
      --(*counter);
    }
  };

  template <typename T>
  auto SharedPtr<T>::operator =(const SharedPtr<T>& r) -> SharedPtr<T>&{
    this->pointer = r.pointer;
    this->counter = r.counter;
    if (counter != nullptr) {
      ++(*counter);
    }
    return *this;
  };

  template <typename T>
  auto SharedPtr<T>::operator=(SharedPtr&& r) -> SharedPtr& {
    this->reset();
    this->pointer = r.pointer;
    this->counter = r.counter;
    if (counter != nullptr) {
      ++(*counter);
    }
    return *this;
  };

  template <typename T>
  SharedPtr<T>::operator bool() const { return pointer; };

  template <typename T>
  auto SharedPtr<T>::operator*() const -> T& { return *pointer; };

  template <typename T>
  auto SharedPtr<T>::operator->() const -> T* { return pointer; };

  template <typename T>
  auto SharedPtr<T>::get() -> T* { return pointer; };

  template <typename T>
  auto SharedPtr<T>::use_count() const -> std::size_t { return *counter; };

  template <typename T>
  void SharedPtr<T>::reset() {
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
  };

  template <typename T>
  void SharedPtr<T>::reset(T* ptr) {
    if (counter != nullptr) {
      --(*counter);
    }
    counter = new std::atomic_uint;
    *counter = 1;
    pointer = ptr;
  };

  template <typename T>
  void SharedPtr<T>::swap(SharedPtr& r) {
    SharedPtr<T> temp(r);
    r = *this;
    *this = temp;
  };
