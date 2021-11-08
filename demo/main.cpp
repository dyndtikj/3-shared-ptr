#include <mshared_ptr.hpp>
#include <iostream>

int main() {

  int* ptr = new int(100);

  int* p = new int(200);

  int*s = new int(300);
  SharedPtr<int> ptr2(ptr);
  SharedPtr<int> ptr3(p);
  SharedPtr<int> ptr4(s);

  ptr3= std::move(ptr2);

//  ptr2=ptr3=ptr4;
//  std::cout<<ptr2.use_count();
  std::cout<<ptr3.use_count();
  std::cout<<ptr4.use_count();
//  std::cout<<*ptr2.get();

  std::cout<<*ptr3;
  std::cout<<*ptr4.get();
  ptr3.reset();
  std::cout<<ptr4.use_count();

  SharedPtr<int> ptr6 = std::move(ptr3);
  return 0;
}