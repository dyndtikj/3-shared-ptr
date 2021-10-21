#include <mshared_ptr.hpp>

int main() {
  int* a = nullptr;
  *a = 100;
  SharedPtr<int> ptr1;
//  SharedPtr<int> ptr2(ptr1);
//  SharedPtr<int> ptr3 = ptr2;
//  SharedPtr<int> ptr4 = std::move(ptr3);
}