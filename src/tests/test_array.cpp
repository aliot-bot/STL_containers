#include <gtest/gtest.h>
#include <array>

#include "../s21_containers.h"

TEST(ArrayTest, InitializerListConstructor) {
  s21::array<int, 5> s21_arr = {1, 2, 3};
  std::array<int, 5> std_arr = {1, 2, 3};
  
  EXPECT_EQ(s21_arr.size(), std_arr.size());
  for (size_t i = 0; i < s21_arr.size(); ++i) {
    EXPECT_EQ(s21_arr[i], std_arr[i]);
  }
}

TEST(ArrayTest, InitializerListConstructorThrow) {
  EXPECT_THROW((s21::array<int, 2>{1, 2, 3}), std::out_of_range);
}

TEST(ArrayTest, CopyConstructor) {
  s21::array<int, 3> s21_orig = {1, 2, 3};
  std::array<int, 3> std_orig = {1, 2, 3};
  
  s21::array<int, 3> s21_copy(s21_orig);
  std::array<int, 3> std_copy(std_orig);
  
  for (size_t i = 0; i < s21_copy.size(); ++i) {
    EXPECT_EQ(s21_copy[i], std_copy[i]);
  }
}

TEST(ArrayTest, MoveConstructor) {
  s21::array<int, 3> s21_orig = {1, 2, 3};
  std::array<int, 3> std_orig = {1, 2, 3};
  
  s21::array<int, 3> s21_moved(std::move(s21_orig));
  std::array<int, 3> std_moved(std::move(std_orig));
  
  for (size_t i = 0; i < s21_moved.size(); ++i) {
    EXPECT_EQ(s21_moved[i], std_moved[i]);
  }
}

TEST(ArrayTest, MoveAssignment) {
  s21::array<int, 3> s21_orig = {1, 2, 3};
  std::array<int, 3> std_orig = {1, 2, 3};
  
  s21::array<int, 3> s21_arr;
  std::array<int, 3> std_arr;
  s21_arr = std::move(s21_orig);
  std_arr = std::move(std_orig);
  
  for (size_t i = 0; i < s21_arr.size(); ++i) {
    EXPECT_EQ(s21_arr[i], std_arr[i]);
  }
}

TEST(ArrayTest, AtMethod) {
  s21::array<int, 3> s21_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};
  
  EXPECT_EQ(s21_arr.at(1), std_arr.at(1));
  EXPECT_THROW(s21_arr.at(5), std::out_of_range);
  EXPECT_THROW(std_arr.at(5), std::out_of_range);
}

TEST(ArrayTest, OperatorBrackets) {
  s21::array<int, 3> s21_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};
  
  EXPECT_EQ(s21_arr[1], std_arr[1]);
  s21_arr[1] = 10;
  std_arr[1] = 10;
  EXPECT_EQ(s21_arr[1], std_arr[1]);
}

TEST(ArrayTest, FrontBack) {
  s21::array<int, 3> s21_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};
  
  EXPECT_EQ(s21_arr.front(), std_arr.front());
  EXPECT_EQ(s21_arr.back(), std_arr.back());
}

TEST(ArrayTest, Data) {
  s21::array<int, 3> s21_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};
  
  EXPECT_EQ(*s21_arr.data(), *std_arr.data());
  EXPECT_EQ(*(s21_arr.data() + 1), *(std_arr.data() + 1));
}

TEST(ArrayTest, BeginEnd) {
  s21::array<int, 3> s21_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};
  
  auto s21_it = s21_arr.begin();
  auto std_it = std_arr.begin();
  
  EXPECT_EQ(*s21_it, *std_it);
  ++s21_it;
  ++std_it;
  EXPECT_EQ(*s21_it, *std_it);
  
  EXPECT_EQ(*(s21_arr.end() - 1), *(std_arr.end() - 1));
}

TEST(ArrayTest, Empty) {
  s21::array<int, 0> s21_empty;
  std::array<int, 0> std_empty;
  
  EXPECT_TRUE(s21_empty.empty());
  EXPECT_TRUE(std_empty.empty());
  
  s21::array<int, 1> s21_non_empty;
  std::array<int, 1> std_non_empty;
  
  EXPECT_FALSE(s21_non_empty.empty());
  EXPECT_FALSE(std_non_empty.empty());
}

TEST(ArrayTest, Size) {
  s21::array<int, 5> s21_arr;
  std::array<int, 5> std_arr;
  
  EXPECT_EQ(s21_arr.size(), std_arr.size());
  
  s21::array<int, 10> s21_big;
  std::array<int, 10> std_big;
  
  EXPECT_EQ(s21_big.size(), std_big.size());
}

TEST(ArrayTest, MaxSize) {
  s21::array<int, 5> s21_arr;
  std::array<int, 5> std_arr;
  
  EXPECT_EQ(s21_arr.max_size(), std_arr.max_size());
}

TEST(ArrayTest, Swap) {
  s21::array<int, 3> s21_a = {1, 2, 3};
  s21::array<int, 3> s21_b = {4, 5, 6};
  
  std::array<int, 3> std_a = {1, 2, 3};
  std::array<int, 3> std_b = {4, 5, 6};
  
  s21_a.swap(s21_b);
  std_a.swap(std_b);
  
  for (size_t i = 0; i < s21_a.size(); ++i) {
    EXPECT_EQ(s21_a[i], std_a[i]);
    EXPECT_EQ(s21_b[i], std_b[i]);
  }
}

TEST(ArrayTest, Fill) {
  s21::array<int, 5> s21_arr;
  std::array<int, 5> std_arr;
  
  s21_arr.fill(42);
  std_arr.fill(42);
  
  for (size_t i = 0; i < s21_arr.size(); ++i) {
    EXPECT_EQ(s21_arr[i], std_arr[i]);
  }
}

TEST(ArrayTest, ConstIterator) {
  const s21::array<int, 3> s21_arr = {1, 2, 3};
  const std::array<int, 3> std_arr = {1, 2, 3};
  
  int s21_sum = 0;
  for (auto it = s21_arr.begin(); it != s21_arr.end(); ++it) {
    s21_sum += *it;
  }
  
  int std_sum = 0;
  for (auto it = std_arr.begin(); it != std_arr.end(); ++it) {
    std_sum += *it;
  }
  
  EXPECT_EQ(s21_sum, std_sum);
}

TEST(ArrayTest, IteratorOperations) {
  s21::array<int, 5> s21_arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_arr = {1, 2, 3, 4, 5};
  
  auto s21_it = s21_arr.begin();
  auto std_it = std_arr.begin();
  
  EXPECT_EQ(*(s21_it + 2), *(std_it + 2));
  EXPECT_EQ(s21_it[2], std_it[2]);
  EXPECT_EQ(*(s21_it += 2), *(std_it += 2));
}

TEST(ArrayTest, ReverseIteration) {
  s21::array<int, 3> s21_arr = {1, 2, 3};
  std::array<int, 3> std_arr = {1, 2, 3};
  
  int s21_sum = 0;
  for (auto it = s21_arr.end() - 1; it >= s21_arr.begin(); --it) {
    s21_sum += *it;
  }
  
  int std_sum = 0;
  for (auto it = std_arr.end() - 1; it >= std_arr.begin(); --it) {
    std_sum += *it;
  }
  
  EXPECT_EQ(s21_sum, std_sum);
}