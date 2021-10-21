#include <mshared_ptr.hpp>
#include <iostream>
#include <memory>

int main() {
  std::cout<<"wiekdfw";
  int a = 100;
  a++;
  int* ptr = &a;
  SharedPtr<int> ptr2(ptr);
  std::cout<<"wiekdfw";
  SharedPtr<int> ptr3(ptr2);
  SharedPtr<int> ptr4;

  SharedPtr<int> ptr5 = ptr2;
  SharedPtr<int> ptr6 = std::move(ptr3);
  return 0;
}