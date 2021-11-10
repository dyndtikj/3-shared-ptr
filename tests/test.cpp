// Copyright 2021 <geraldy12319@gamil.com>

#include <gtest/gtest.h>
#include "mshared_ptr.hpp"

TEST(SharedPtr, Empty) {
  SharedPtr<int> p;
  ASSERT_EQ(p.get(), nullptr);
  ASSERT_EQ(p.get_counter(), nullptr);
}

TEST(SharedPtr, From_null) {
  int* ptr;
  ptr = nullptr;
  SharedPtr<int> p(ptr);
  ASSERT_EQ(p.get(), nullptr);
  ASSERT_EQ(p.get_counter(), nullptr);
}

TEST(SharedPtr, From_pointer) {
  SharedPtr<int> p(new int{5});
  ASSERT_EQ(*p.get(), 5);
  ASSERT_EQ(p.use_count(), 1);
}

TEST(SharedPtr, Copy_assignment) {
  SharedPtr p1(new double{1.2345});
  SharedPtr p2(new double{5.214421});
  p2 = p1;
  ASSERT_EQ(*p1, *p2);
  ASSERT_EQ(p1.use_count(), p2.use_count());
  ASSERT_EQ(p1.use_count(), 2);
}
TEST(SharedPtr, Move_assignment) {
  SharedPtr p1(new double{1.2345});
  SharedPtr p2(new double{5.214421});

  p2 = std::move(p1);

  ASSERT_EQ(*p2, 1.2345);
  ASSERT_EQ(p2.use_count(), 1);
  ASSERT_EQ(p1.get(), nullptr);
  ASSERT_EQ(p1.get_counter(), nullptr);
}
TEST(SharedPtr, CopyConstructor) {
  const SharedPtr p(new std::string{"Hello"});
  SharedPtr n(p);

  ASSERT_EQ(*n, *p);
  ASSERT_EQ(n.use_count(), p.use_count());
}
TEST(SharedPtr, MoveConstructor) {
  SharedPtr p1(new std::string{"Test_string"});
  SharedPtr p2(std::move(p1));

  ASSERT_EQ(*p2, "Test_string");
  ASSERT_EQ(p2.use_count(), 1);

  ASSERT_EQ(p1.get(), nullptr);
  ASSERT_EQ(p1.get_counter(), nullptr);
}

struct Test_Class {
  explicit Test_Class(int _value) : value(_value) {}
  int get_value() const { return value; }
  int value;
};

// Test for operator '->'
TEST(SharedPtr, Access_to_field_or_method) {
  SharedPtr<Test_Class> ptr(new Test_Class{12});
  ASSERT_EQ(ptr->get_value(), 12);
}

TEST(SharedPtr, Reset_default) {
  SharedPtr p(new int(12));
  p.reset();
  ASSERT_EQ(p.get(), nullptr);
  ASSERT_EQ(p.get_counter(), nullptr);
}

TEST(SharedPtr, Reset_value) {
  SharedPtr p(new int(12));
  p.reset(new int(3));
  ASSERT_EQ(*p, 3);
  ASSERT_EQ(p.use_count(), 1);
}

TEST(SharedPtr, Swap) {
  SharedPtr p1{new int(12)};
  SharedPtr p2{new int(21)};
  SharedPtr p3 = p1;      // to make counter 2
  p2.swap(p1);
  ASSERT_EQ(p2.use_count(), 2);
  ASSERT_EQ(p1.use_count(), 1);
}

TEST(SharedPtr, Get) {
  SharedPtr p{new int{1}};
  *p = 2;
  ASSERT_EQ(*p, 2);
  ASSERT_EQ(p.use_count(), 1);
}

TEST(SharedPtr, Operator_bool)
{
  SharedPtr<int> p1;
  ASSERT_EQ(p1.operator bool(), false);
  SharedPtr p2(new int{12});
  ASSERT_EQ(p2.operator bool(), true);
}

TEST(SharedPtr, Is_Movable){
  EXPECT_TRUE(
      std::is_move_constructible<SharedPtr<Test_Class>>::value);
  EXPECT_TRUE(
      std::is_move_assignable<SharedPtr<Test_Class>>::value);
  EXPECT_TRUE(
      std::is_move_constructible<SharedPtr<double>>::value);
  EXPECT_TRUE(
      std::is_move_assignable<SharedPtr<double>>::value);
}

TEST(SharedPtr, Is_Constructible){
  EXPECT_TRUE(
      std::is_copy_constructible<SharedPtr<Test_Class>>::value);
  EXPECT_TRUE(
      std::is_copy_assignable<SharedPtr<Test_Class>>::value);
  EXPECT_TRUE(
      std::is_copy_constructible<SharedPtr<double>>::value);
  EXPECT_TRUE(
      std::is_copy_assignable<SharedPtr<double>>::value);
}