#include <gtest/gtest.h>

#include <queue>

#include "../s21_containers.h"

// Тесты для s21::queue
TEST(QueueTest, DefaultConstructor) {
  s21::queue<int> q;
  std::queue<int> std_q;
  ASSERT_TRUE(q.empty());
  ASSERT_EQ(q.size(), 0);
  ASSERT_THROW(q.front(), std::out_of_range);
  ASSERT_THROW(q.back(), std::out_of_range);
  ASSERT_THROW(q.pop(), std::out_of_range);

  // Сравнение с std::queue
  ASSERT_EQ(q.empty(), std_q.empty());
  ASSERT_EQ(q.size(), std_q.size());
}

TEST(QueueTest, InitializerListConstructor) {
  s21::queue<int> q = {1, 2, 3};
  std::queue<int> std_q;
  std_q.push(1);
  std_q.push(2);
  std_q.push(3);

  ASSERT_FALSE(q.empty());
  ASSERT_EQ(q.size(), 3);
  ASSERT_EQ(q.front(), 1);
  ASSERT_EQ(q.back(), 3);

  // Сравнение с std::queue
  ASSERT_EQ(q.empty(), std_q.empty());
  ASSERT_EQ(q.size(), std_q.size());
  ASSERT_EQ(q.front(), std_q.front());
  ASSERT_EQ(q.back(), std_q.back());
}

TEST(QueueTest, CopyConstructor) {
  s21::queue<int> q1 = {1, 2};
  s21::queue<int> q2(q1);

  std::queue<int> std_q1;
  std_q1.push(1);
  std_q1.push(2);
  std::queue<int> std_q2(std_q1);

  ASSERT_EQ(q2.size(), 2);
  ASSERT_EQ(q2.front(), 1);
  ASSERT_EQ(q2.back(), 2);

  q1.pop();
  ASSERT_EQ(q1.size(), 1);
  ASSERT_EQ(q2.size(), 2);  // Копия не зависит от оригинала

  // Сравнение с std::queue
  ASSERT_EQ(q2.size(), std_q2.size());
  ASSERT_EQ(q2.front(), std_q2.front());
  ASSERT_EQ(q2.back(), std_q2.back());
}

TEST(QueueTest, MoveConstructor) {
  s21::queue<int> q1 = {1, 2};
  s21::queue<int> q2(std::move(q1));

  std::queue<int> std_q1;
  std_q1.push(1);
  std_q1.push(2);
  std::queue<int> std_q2(std::move(std_q1));

  ASSERT_TRUE(q1.empty());
  ASSERT_EQ(q1.size(), 0);
  ASSERT_EQ(q2.size(), 2);
  ASSERT_EQ(q2.front(), 1);

  // Сравнение с std::queue
  ASSERT_EQ(q1.empty(), std_q1.empty());
  ASSERT_EQ(q1.size(), std_q1.size());
  ASSERT_EQ(q2.size(), std_q2.size());
  ASSERT_EQ(q2.front(), std_q2.front());
}

TEST(QueueTest, MoveAssignment) {
  s21::queue<int> q1 = {1, 2};
  s21::queue<int> q2;
  q2 = std::move(q1);

  std::queue<int> std_q1;
  std_q1.push(1);
  std_q1.push(2);
  std::queue<int> std_q2;
  std_q2 = std::move(std_q1);

  ASSERT_TRUE(q1.empty());
  ASSERT_EQ(q1.size(), 0);
  ASSERT_EQ(q2.size(), 2);
  ASSERT_EQ(q2.front(), 1);

  // Сравнение с std::queue
  ASSERT_EQ(q1.empty(), std_q1.empty());
  ASSERT_EQ(q1.size(), std_q1.size());
  ASSERT_EQ(q2.size(), std_q2.size());
  ASSERT_EQ(q2.front(), std_q2.front());
}

TEST(QueueTest, PushAndPop) {
  s21::queue<int> q;
  std::queue<int> std_q;

  q.push(1);
  std_q.push(1);
  ASSERT_EQ(q.size(), 1);
  ASSERT_EQ(q.front(), 1);

  q.push(2);
  std_q.push(2);
  ASSERT_EQ(q.size(), 2);
  ASSERT_EQ(q.back(), 2);

  q.pop();
  std_q.pop();
  ASSERT_EQ(q.size(), 1);
  ASSERT_EQ(q.front(), 2);

  // Сравнение с std::queue
  ASSERT_EQ(q.empty(), std_q.empty());
  ASSERT_EQ(q.size(), std_q.size());
  ASSERT_EQ(q.front(), std_q.front());
  ASSERT_EQ(q.back(), std_q.back());
}

TEST(QueueTest, Swap) {
  s21::queue<int> q1 = {1, 2};
  s21::queue<int> q2 = {3, 4, 5};

  std::queue<int> std_q1;
  std_q1.push(1);
  std_q1.push(2);
  std::queue<int> std_q2;
  std_q2.push(3);
  std_q2.push(4);
  std_q2.push(5);

  q1.swap(q2);
  std_q1.swap(std_q2);

  ASSERT_EQ(q1.size(), 3);
  ASSERT_EQ(q1.front(), 3);
  ASSERT_EQ(q2.size(), 2);
  ASSERT_EQ(q2.front(), 1);

  // Сравнение с std::queue
  ASSERT_EQ(q1.size(), std_q1.size());
  ASSERT_EQ(q1.front(), std_q1.front());
  ASSERT_EQ(q2.size(), std_q2.size());
  ASSERT_EQ(q2.front(), std_q2.front());
}

TEST(QueueTest, ConstMethods) {
  const s21::queue<int> q = {1, 2};
  const std::queue<int> std_q = []() {
    std::queue<int> q;
    q.push(1);
    q.push(2);
    return q;
  }();

  ASSERT_EQ(q.size(), 2);
  ASSERT_EQ(q.front(), 1);
  ASSERT_EQ(q.back(), 2);

  // Сравнение с std::queue
  ASSERT_EQ(q.size(), std_q.size());
  ASSERT_EQ(q.front(), std_q.front());
  ASSERT_EQ(q.back(), std_q.back());
}

TEST(QueueTest, LongSequence) {
  s21::queue<int> q;
  std::queue<int> std_q;

  for (int i = 0; i < 1000; ++i) {
    q.push(i);
    std_q.push(i);
  }

  ASSERT_EQ(q.size(), 1000);
  ASSERT_EQ(q.front(), 0);
  ASSERT_EQ(q.back(), 999);

  for (int i = 0; i < 500; ++i) {
    q.pop();
    std_q.pop();
  }

  ASSERT_EQ(q.size(), 500);
  ASSERT_EQ(q.front(), 500);
  ASSERT_EQ(q.back(), 999);

  // Сравнение с std::queue
  ASSERT_EQ(q.size(), std_q.size());
  ASSERT_EQ(q.front(), std_q.front());
  ASSERT_EQ(q.back(), std_q.back());
}
