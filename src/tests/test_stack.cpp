#include <gtest/gtest.h>

#include <stack>

#include "../s21_containers.h"

TEST(StackTest, DefaultConstructor) {
  s21::stack<int> s;
  std::stack<int> std_s;
  ASSERT_TRUE(s.empty());
  ASSERT_EQ(s.size(), 0);
  ASSERT_THROW(s.top(), std::out_of_range);
  ASSERT_THROW(s.pop(), std::out_of_range);

  // Сравнение с std::stack
  ASSERT_EQ(s.empty(), std_s.empty());
  ASSERT_EQ(s.size(), std_s.size());
}

TEST(StackTest, InitializerListConstructor) {
  s21::stack<int> s = {1, 2, 3};
  std::stack<int> std_s;
  std_s.push(1);
  std_s.push(2);
  std_s.push(3);

  ASSERT_FALSE(s.empty());
  ASSERT_EQ(s.size(), 3);
  ASSERT_EQ(s.top(), 3);

  // Сравнение с std::stack
  ASSERT_EQ(s.empty(), std_s.empty());
  ASSERT_EQ(s.size(), std_s.size());
  ASSERT_EQ(s.top(), std_s.top());
}

TEST(StackTest, CopyConstructor) {
  s21::stack<int> s1 = {1, 2};
  s21::stack<int> s2(s1);

  std::stack<int> std_s1;
  std_s1.push(1);
  std_s1.push(2);
  std::stack<int> std_s2(std_s1);

  ASSERT_EQ(s2.size(), 2);
  ASSERT_EQ(s2.top(), 2);

  s1.pop();
  ASSERT_EQ(s1.size(), 1);
  ASSERT_EQ(s2.size(), 2);

  // Сравнение с std::stack
  ASSERT_EQ(s2.size(), std_s2.size());
  ASSERT_EQ(s2.top(), std_s2.top());
}

TEST(StackTest, MoveConstructor) {
  s21::stack<int> s1 = {1, 2};
  s21::stack<int> s2(std::move(s1));

  std::stack<int> std_s1;
  std_s1.push(1);
  std_s1.push(2);
  std::stack<int> std_s2(std::move(std_s1));

  ASSERT_TRUE(s1.empty());
  ASSERT_EQ(s1.size(), 0);
  ASSERT_EQ(s2.size(), 2);
  ASSERT_EQ(s2.top(), 2);

  // Сравнение с std::stack
  ASSERT_EQ(s1.empty(), std_s1.empty());
  ASSERT_EQ(s1.size(), std_s1.size());
  ASSERT_EQ(s2.size(), std_s2.size());
  ASSERT_EQ(s2.top(), std_s2.top());
}

TEST(StackTest, MoveAssignment) {
  s21::stack<int> s1 = {1, 2};
  s21::stack<int> s2;
  s2 = std::move(s1);

  std::stack<int> std_s1;
  std_s1.push(1);
  std_s1.push(2);
  std::stack<int> std_s2;
  std_s2 = std::move(std_s1);

  ASSERT_TRUE(s1.empty());
  ASSERT_EQ(s1.size(), 0);
  ASSERT_EQ(s2.size(), 2);
  ASSERT_EQ(s2.top(), 2);

  // Сравнение с std::stack
  ASSERT_EQ(s1.empty(), std_s1.empty());
  ASSERT_EQ(s1.size(), std_s1.size());
  ASSERT_EQ(s2.size(), std_s2.size());
  ASSERT_EQ(s2.top(), std_s2.top());
}

TEST(StackTest, PushAndPop) {
  s21::stack<int> s;
  std::stack<int> std_s;

  s.push(1);
  std_s.push(1);
  ASSERT_EQ(s.size(), 1);
  ASSERT_EQ(s.top(), 1);

  s.push(2);
  std_s.push(2);
  ASSERT_EQ(s.size(), 2);
  ASSERT_EQ(s.top(), 2);

  s.pop();
  std_s.pop();
  ASSERT_EQ(s.size(), 1);
  ASSERT_EQ(s.top(), 1);

  // Сравнение с std::stack
  ASSERT_EQ(s.empty(), std_s.empty());
  ASSERT_EQ(s.size(), std_s.size());
  ASSERT_EQ(s.top(), std_s.top());
}

TEST(StackTest, Swap) {
  s21::stack<int> s1 = {1, 2};
  s21::stack<int> s2 = {3, 4, 5};

  std::stack<int> std_s1;
  std_s1.push(1);
  std_s1.push(2);
  std::stack<int> std_s2;
  std_s2.push(3);
  std_s2.push(4);
  std_s2.push(5);

  s1.swap(s2);
  std_s1.swap(std_s2);

  ASSERT_EQ(s1.size(), 3);
  ASSERT_EQ(s1.top(), 5);
  ASSERT_EQ(s2.size(), 2);
  ASSERT_EQ(s2.top(), 2);

  // Сравнение с std::stack
  ASSERT_EQ(s1.size(), std_s1.size());
  ASSERT_EQ(s1.top(), std_s1.top());
  ASSERT_EQ(s2.size(), std_s2.size());
  ASSERT_EQ(s2.top(), std_s2.top());
}

TEST(StackTest, ConstMethods) {
  const s21::stack<int> s = {1, 2};
  const std::stack<int> std_s = []() {
    std::stack<int> s;
    s.push(1);
    s.push(2);
    return s;
  }();

  ASSERT_EQ(s.size(), 2);
  ASSERT_EQ(s.top(), 2);

  // Сравнение с std::stack
  ASSERT_EQ(s.size(), std_s.size());
  ASSERT_EQ(s.top(), std_s.top());
}

TEST(StackTest, LongSequence) {
  s21::stack<int> s;
  std::stack<int> std_s;

  for (int i = 0; i < 1000; ++i) {
    s.push(i);
    std_s.push(i);
  }

  ASSERT_EQ(s.size(), 1000);
  ASSERT_EQ(s.top(), 999);

  for (int i = 0; i < 500; ++i) {
    s.pop();
    std_s.pop();
  }

  ASSERT_EQ(s.size(), 500);
  ASSERT_EQ(s.top(), 499);

  // Сравнение с std::stack
  ASSERT_EQ(s.size(), std_s.size());
  ASSERT_EQ(s.top(), std_s.top());
}
