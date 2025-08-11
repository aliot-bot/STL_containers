#include <gtest/gtest.h>

#include <set>

#include "../s21_containers.h"

TEST(SetTest, DefaultConstructor) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(SetTest, InitializerListConstructor) {
  s21::set<int> s21_set = {1, 2, 3, 2, 1};  // Дубликаты игнорируются
  std::set<int> std_set = {1, 2, 3, 2, 1};
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_TRUE(s21_set.contains(1) == std_set.count(1));
  EXPECT_TRUE(s21_set.contains(2) == std_set.count(2));
  EXPECT_TRUE(s21_set.contains(3) == std_set.count(3));
}

TEST(SetTest, CopyConstructor) {
  s21::set<int> s21_set1 = {1, 2, 3};
  s21::set<int> s21_set2(s21_set1);
  std::set<int> std_set1 = {1, 2, 3};
  std::set<int> std_set2(std_set1);
  EXPECT_EQ(s21_set1.size(), std_set1.size());
  EXPECT_EQ(s21_set2.size(), std_set2.size());
  EXPECT_TRUE(s21_set2.contains(2) == std_set2.count(2));
}

TEST(SetTest, MoveConstructor) {
  s21::set<int> s21_set1 = {1, 2, 3};
  s21::set<int> s21_set2(std::move(s21_set1));
  std::set<int> std_set1 = {1, 2, 3};
  std::set<int> std_set2(std::move(std_set1));
  EXPECT_TRUE(s21_set2.contains(2) == std_set2.count(2));
  EXPECT_TRUE(s21_set1.empty() == std_set1.empty());
}

TEST(SetTest, CopyAssignment) {
  s21::set<int> s21_set1 = {1, 2, 3};
  s21::set<int> s21_set2;
  s21_set2 = s21_set1;
  std::set<int> std_set1 = {1, 2, 3};
  std::set<int> std_set2;
  std_set2 = std_set1;
  EXPECT_EQ(s21_set1.size(), std_set1.size());
  EXPECT_EQ(s21_set2.size(), std_set2.size());
  EXPECT_TRUE(s21_set2.contains(3) == std_set2.count(3));
}

TEST(SetTest, MoveAssignment) {
  s21::set<int> s21_set1 = {1, 2, 3};
  s21::set<int> s21_set2;
  s21_set2 = std::move(s21_set1);
  std::set<int> std_set1 = {1, 2, 3};
  std::set<int> std_set2;
  std_set2 = std::move(std_set1);
  EXPECT_TRUE(s21_set2.contains(1) == std_set2.count(1));
  EXPECT_TRUE(s21_set1.empty() == std_set1.empty());
}

TEST(SetTest, EmptyCheck) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  EXPECT_EQ(s21_set.empty(), std_set.empty());
  s21_set.insert(1);
  std_set.insert(1);
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(SetTest, SizeCheck) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  EXPECT_EQ(s21_set.size(), std_set.size());
  s21_set.insert(1);
  s21_set.insert(2);
  std_set.insert(1);
  std_set.insert(2);
  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(SetTest, MaxSizeCheck) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  EXPECT_GT(s21_set.max_size(), 0);
  EXPECT_GT(std_set.max_size(), 0);
  EXPECT_TRUE(s21_set.max_size() <= std_set.max_size());
}

TEST(SetTest, ClearMethod) {
  s21::set<int> s21_set = {1, 2, 3};
  std::set<int> std_set = {1, 2, 3};
  s21_set.clear();
  std_set.clear();
  EXPECT_TRUE(s21_set.empty() == std_set.empty());
  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(SetTest, InsertUnique) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  auto s21_result1 = s21_set.insert(1);
  auto std_result1 = std_set.insert(1);
  auto s21_result2 = s21_set.insert(1);
  auto std_result2 = std_set.insert(1);
  EXPECT_EQ(s21_result1.second, std_result1.second);
  EXPECT_EQ(s21_result2.second, std_result2.second);
  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(SetTest, InsertMultiple) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  s21_set.insert(1);
  s21_set.insert(3);
  s21_set.insert(2);
  std_set.insert(1);
  std_set.insert(3);
  std_set.insert(2);
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_TRUE(s21_set.contains(2) == std_set.count(2));
}

TEST(SetTest, EraseElement) {
  s21::set<int> s21_set = {1, 2, 3};
  std::set<int> std_set = {1, 2, 3};
  auto s21_it = s21_set.find(2);
  auto std_it = std_set.find(2);
  s21_set.erase(s21_it);
  std_set.erase(std_it);
  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(SetTest, SwapMethod) {
  s21::set<int> s21_set1 = {1, 2};
  s21::set<int> s21_set2 = {3, 4};
  std::set<int> std_set1 = {1, 2};
  std::set<int> std_set2 = {3, 4};
  s21_set1.swap(s21_set2);
  std_set1.swap(std_set2);
  EXPECT_TRUE(s21_set1.contains(3) == std_set1.count(3));
  EXPECT_TRUE(s21_set2.contains(1) == std_set2.count(1));
}

TEST(SetTest, MergeMethod) {
  s21::set<int> s21_set1 = {1, 2};
  s21::set<int> s21_set2 = {2, 3};
  std::set<int> std_set1 = {1, 2};
  std::set<int> std_set2 = {2, 3};
  s21_set1.merge(s21_set2);
  std_set1.merge(std_set2);
  EXPECT_EQ(s21_set1.size(), std_set1.size());
  EXPECT_TRUE(s21_set2.empty() == std_set2.empty());
}

TEST(SetTest, FindMethod) {
  s21::set<int> s21_set = {1, 2, 3};
  std::set<int> std_set = {1, 2, 3};
  auto s21_it = s21_set.find(2);
  auto std_it = std_set.find(2);
  EXPECT_NE(s21_it, s21_set.end());
  EXPECT_NE(std_it, std_set.end());
  EXPECT_EQ(*s21_it, *std_it);
}

TEST(SetTest, ContainsMethod) {
  s21::set<int> s21_set = {1, 2, 3};
  std::set<int> std_set = {1, 2, 3};
  EXPECT_TRUE(s21_set.contains(1) == std_set.count(1));
}

TEST(SetTest, CountMethod) {
  s21::set<int> s21_set = {1, 2, 3};
  std::set<int> std_set = {1, 2, 3};
  EXPECT_EQ(s21_set.count(2), std_set.count(2));
  EXPECT_EQ(s21_set.count(4), std_set.count(4));
}

TEST(SetTest, LowerUpperBound) {
  s21::set<int> s21_set = {1, 2, 3};
  std::set<int> std_set = {1, 2, 3};
  EXPECT_EQ(*s21_set.lower_bound(2), *std_set.lower_bound(2));
  EXPECT_EQ(*s21_set.upper_bound(2), *std_set.upper_bound(2));
}

TEST(SetTest, EqualRange) {
  s21::set<int> s21_set = {1, 2, 3};
  std::set<int> std_set = {1, 2, 3};
  auto s21_range = s21_set.equal_range(2);
  auto std_range = std_set.equal_range(2);
  EXPECT_EQ(*s21_range.first, *std_range.first);
  EXPECT_EQ(*s21_range.second, *std_range.second);
}

TEST(SetTest, StringType) {
  s21::set<std::string> s21_set = {"a", "c", "b"};
  std::set<std::string> std_set = {"a", "c", "b"};
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_TRUE(s21_set.contains("b") == std_set.count("b"));
}