// Copyright 2021 <geraldy12319@gamil.com>

#include <gtest/gtest.h>

#include <string>

#include "mshared_ptr.hpp"

TEST(SharedPtr, EmptyConstructor) {
  SharedPtr<int> p;

  ASSERT_EQ(p.get(), nullptr);
  ASSERT_EQ(p.get_counter(), nullptr);
}
TEST(SharedPtr, Construct_from_null) {
  int* ptr;
  ptr = nullptr;
  SharedPtr<int> p(ptr);

  ASSERT_EQ(p.get(), nullptr);
  ASSERT_EQ(p.get_counter(), nullptr);
}
TEST(SharedPtr, PointerConstructor) {
  SharedPtr<int> p(new int{5});

  ASSERT_EQ(*p.get(), 5);
  ASSERT_EQ(p.use_count(), 1);

  SharedPtr<int> v(new int{5});

  ASSERT_EQ(*v.get(), 5);
  ASSERT_EQ(v.use_count(), 1);
}
TEST(SharedPtr, CopyAssignment) {
  const SharedPtr p(new double{2.2});
  SharedPtr n(new double{3.4});

  n = p;

  ASSERT_EQ(*n, *p);
  ASSERT_EQ(n.use_count(), p.use_count());
}
TEST(SharedPtr, MoveAssignment) {
  SharedPtr p(new double{2.2});

  ASSERT_EQ(p.use_count(), 1);

  SharedPtr n(new double{3.4});

  n = std::move(p);

  ASSERT_EQ(*n, 2.2);
  ASSERT_EQ(n.use_count(), 1);

  ASSERT_EQ(p.get(), nullptr);
  ASSERT_EQ(p.get_counter(), nullptr);
}
TEST(SharedPtr, CopyConstructor) {
  const SharedPtr p(new std::string{"Hello"});
  SharedPtr n(p);

  ASSERT_EQ(*n, *p);
  ASSERT_EQ(n.use_count(), p.use_count());
}
TEST(SharedPtr, MoveConstructor) {
  SharedPtr p(new std::string{"Hi"});
  SharedPtr n(std::move(p));

  ASSERT_EQ(*n, "Hi");
  ASSERT_EQ(n.use_count(), 1);

  ASSERT_EQ(p.get(), nullptr);
  ASSERT_EQ(p.get_counter(), nullptr);
}
TEST(SharedPtr, Dereferencing) {
  SharedPtr p(new std::string{"Hi"});

  EXPECT_EQ(*p, "Hi");
}
struct Foo {
  explicit Foo(int in) : a(in) {}
  [[nodiscard]] int get() const { return a; }
  int a;
};

TEST(SharedPtr, AccessThroughPointer) {
  SharedPtr<Foo> ptr(new Foo{516237});

  ASSERT_EQ(ptr->get(), 516237);
}
TEST(SharedPtr, ResetEmpty) {
  SharedPtr p(new double{2.2});
  p.reset();
  ASSERT_EQ(p.get(), nullptr);
  ASSERT_EQ(p.get_counter(), nullptr);
}
TEST(SharedPtr, ResetPointer) {
  SharedPtr p(new double{2.2});
  SharedPtr n(static_cast<const SharedPtr<double>>(p));
  p.reset(new double{3.4});
  ASSERT_EQ(*p, 3.4);
  ASSERT_EQ(p.use_count(), 1);
  ASSERT_EQ(*n, 2.2);
  ASSERT_EQ(p.use_count(), 1);
}
TEST(SharedPtr, Swap1) {
  SharedPtr ptr1{new int{1}};
  SharedPtr ptr2{new int{2}};

  ptr1.swap(ptr2);

  ASSERT_EQ(*(ptr2.get()), 1);
  ASSERT_EQ(ptr2.operator bool(), true);
  ASSERT_EQ(ptr2.use_count(), 1);

  ASSERT_EQ(*(ptr1.get()), 2);
  ASSERT_EQ(ptr2.operator bool(), true);
  ASSERT_EQ(ptr1.use_count(), 1);
}

TEST(SharedPtr, Swap2) {
  SharedPtr ptr1{new int{567}};
  SharedPtr ptr2{new int{123}};
  SharedPtr ptr3 = ptr1;

  ptr2.swap(ptr1);

  ASSERT_EQ(ptr2.use_count(), 2);
  ASSERT_EQ(ptr1.use_count(), 1);
}
TEST(SharedPtr, Get) {
  SharedPtr ptr1{new int{1}};
  *ptr1 = 2;

  ASSERT_EQ(*ptr1, 2);
  ASSERT_EQ(ptr1.use_count(), 1);
}

TEST(SharedPtr, BoolCheck)  //+
{
  SharedPtr<int> ptr1{};

  ASSERT_EQ(ptr1.operator bool(), false);

  SharedPtr ptr2(new int{23235});

  ASSERT_EQ(ptr2.operator bool(), true);
}
template <class T>
auto selfCopyAssignment(T& value1, T& value2) -> T& {
  value1 = value2;
  return value1;
}
TEST(SharedPtr, ThisCopyAssigment) {
  SharedPtr ptr1{new int{5555}};

  EXPECT_EQ(*selfCopyAssignment(ptr1, ptr1), 5555);
  EXPECT_EQ(selfCopyAssignment<SharedPtr<int>>(ptr1, ptr1).use_count(), 1);
}
template <class T>
auto selfMoveAssignment(T& value1, T& value2) -> T& {
  value1 = std::move(value2);
  return value1;
}
TEST(SharedPtr, ThisMoveAssigment) {
  SharedPtr ptr1{new int{4444}};

  EXPECT_EQ(*selfMoveAssignment(ptr1, ptr1), 4444);
  EXPECT_EQ(selfMoveAssignment(ptr1, ptr1).use_count(), 1);
}