#include <gtest/gtest.h>
#include <set>

#include "../s21_containers.h"

TEST(MultisetTest, DefaultConstructor) {
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;
  EXPECT_EQ(s21_ms.size(), std_ms.size());
  EXPECT_EQ(s21_ms.empty(), std_ms.empty());
}

TEST(MultisetTest, InitializerListConstructor) {
  s21::multiset<int> s21_ms = {1, 2, 2, 3};
  std::multiset<int> std_ms = {1, 2, 2, 3};
  EXPECT_EQ(s21_ms.size(), std_ms.size());
  EXPECT_EQ(s21_ms.count(2), std_ms.count(2));
}

TEST(MultisetTest, CopyConstructor) {
  s21::multiset<int> s21_orig = {1, 2, 2};
  std::multiset<int> std_orig = {1, 2, 2};
  
  s21::multiset<int> s21_copy(s21_orig);
  std::multiset<int> std_copy(std_orig);
  
  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_copy.count(1), std_copy.count(1));
}

TEST(MultisetTest, MoveConstructor) {
  s21::multiset<int> s21_orig = {1, 2, 2};
  std::multiset<int> std_orig = {1, 2, 2};
  
  s21::multiset<int> s21_moved(std::move(s21_orig));
  std::multiset<int> std_moved(std::move(std_orig));
  
  EXPECT_EQ(s21_moved.size(), std_moved.size());
  EXPECT_TRUE(s21_orig.empty());
}

TEST(MultisetTest, MoveAssignment) {
  s21::multiset<int> s21_orig = {1, 2, 2};
  std::multiset<int> std_orig = {1, 2, 2};
  
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;
  s21_ms = std::move(s21_orig);
  std_ms = std::move(std_orig);
  
  EXPECT_EQ(s21_ms.size(), std_ms.size());
  EXPECT_TRUE(s21_orig.empty());
}

TEST(MultisetTest, Insert) {
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;
  
  s21_ms.insert(1);
  s21_ms.insert(2);
  s21_ms.insert(2);
  std_ms.insert(1);
  std_ms.insert(2);
  std_ms.insert(2);
  
  EXPECT_EQ(s21_ms.size(), std_ms.size());
  EXPECT_EQ(s21_ms.count(2), std_ms.count(2));
}

TEST(MultisetTest, Erase) {
  s21::multiset<int> s21_ms = {1, 2, 2, 3};
  std::multiset<int> std_ms = {1, 2, 2, 3};
  
  s21_ms.erase(s21_ms.find(2));
  std_ms.erase(std_ms.find(2));
  
  EXPECT_EQ(s21_ms.size(), std_ms.size());
  EXPECT_EQ(s21_ms.count(2), std_ms.count(2));
}

TEST(MultisetTest, Swap) {
  s21::multiset<int> s21_ms1 = {1, 2, 2};
  s21::multiset<int> s21_ms2 = {3, 4, 4};
  
  std::multiset<int> std_ms1 = {1, 2, 2};
  std::multiset<int> std_ms2 = {3, 4, 4};
  
  s21_ms1.swap(s21_ms2);
  std_ms1.swap(std_ms2);
  
  EXPECT_EQ(s21_ms1.size(), std_ms1.size());
  EXPECT_EQ(s21_ms2.size(), std_ms2.size());
  EXPECT_EQ(s21_ms1.count(4), std_ms1.count(4));
}

TEST(MultisetTest, Merge) {
  s21::multiset<int> s21_ms1 = {1, 2};
  s21::multiset<int> s21_ms2 = {2, 3};
  
  std::multiset<int> std_ms1 = {1, 2};
  std::multiset<int> std_ms2 = {2, 3};
  
  s21_ms1.merge(s21_ms2);
  std_ms1.merge(std_ms2);
  
  EXPECT_EQ(s21_ms1.size(), std_ms1.size());
  EXPECT_EQ(s21_ms1.count(2), std_ms1.count(2));
  EXPECT_EQ(s21_ms2.size(), std_ms2.size());
}

TEST(MultisetTest, Count) {
  s21::multiset<int> s21_ms = {1, 2, 2, 3, 3, 3};
  std::multiset<int> std_ms = {1, 2, 2, 3, 3, 3};
  
  EXPECT_EQ(s21_ms.count(1), std_ms.count(1));
  EXPECT_EQ(s21_ms.count(2), std_ms.count(2));
  EXPECT_EQ(s21_ms.count(3), std_ms.count(3));
  EXPECT_EQ(s21_ms.count(4), std_ms.count(4));
}

TEST(MultisetTest, Find) {
  s21::multiset<int> s21_ms = {1, 2, 2, 3};
  std::multiset<int> std_ms = {1, 2, 2, 3};
  
  EXPECT_NE(s21_ms.find(2), s21_ms.end());
  EXPECT_EQ(*s21_ms.find(2), *std_ms.find(2));
  EXPECT_EQ(s21_ms.find(4), s21_ms.end());
}

TEST(MultisetTest, Contains) {
  s21::multiset<int> s21_ms = {1, 2, 2};
  std::multiset<int> std_ms = {1, 2, 2};
  
  EXPECT_EQ(s21_ms.contains(1), (std_ms.find(1) != std_ms.end()));
  EXPECT_EQ(s21_ms.contains(2), (std_ms.find(2) != std_ms.end()));
  EXPECT_EQ(s21_ms.contains(3), (std_ms.find(3) != std_ms.end()));
}

TEST(MultisetTest, LowerBound) {
  s21::multiset<int> s21_ms = {1, 2, 2, 3};
  std::multiset<int> std_ms = {1, 2, 2, 3};
  
  EXPECT_EQ(*s21_ms.lower_bound(2), *std_ms.lower_bound(2));
  EXPECT_EQ(*s21_ms.lower_bound(1), *std_ms.lower_bound(1));
}

TEST(MultisetTest, UpperBound) {
  s21::multiset<int> s21_ms = {1, 2, 2, 3};
  std::multiset<int> std_ms = {1, 2, 2, 3};
  
  EXPECT_EQ(*s21_ms.upper_bound(2), *std_ms.upper_bound(2));
  EXPECT_EQ(*s21_ms.upper_bound(1), *std_ms.upper_bound(1));
}

TEST(MultisetTest, Iterator) {
  s21::multiset<int> s21_ms = {1, 2, 2, 3};
  std::multiset<int> std_ms = {1, 2, 2, 3};
  
  auto s21_it = s21_ms.begin();
  auto std_it = std_ms.begin();
  
  for (; s21_it != s21_ms.end() && std_it != std_ms.end(); ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(MultisetTest, ConstIterator) {
  const s21::multiset<int> s21_ms = {1, 2, 2, 3};
  const std::multiset<int> std_ms = {1, 2, 2, 3};
  
  auto s21_it = s21_ms.begin();
  auto std_it = std_ms.begin();
  
  for (; s21_it != s21_ms.end() && std_it != std_ms.end(); ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(MultisetTest, MaxSize) {
  s21::multiset<int> s21_ms;
  std::multiset<int> std_ms;
  
  EXPECT_GT(s21_ms.max_size(), 0);
  EXPECT_GT(std_ms.max_size(), 0);
}

TEST(MultisetTest, Clear) {
  s21::multiset<int> s21_ms = {1, 2, 2};
  std::multiset<int> std_ms = {1, 2, 2};
  
  s21_ms.clear();
  std_ms.clear();
  
  EXPECT_EQ(s21_ms.size(), std_ms.size());
  EXPECT_EQ(s21_ms.empty(), std_ms.empty());
}