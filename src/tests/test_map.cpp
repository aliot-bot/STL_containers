#include <gtest/gtest.h>

#include <map>

#include "../s21_containers.h"

TEST(MapTest, DefaultConstructor) {
  s21::Map<int, std::string> s21_map;
  std::map<int, std::string> std_map;
  EXPECT_EQ(s21_map.empty(), std_map.empty());
  EXPECT_EQ(s21_map.size(), std_map.size());
}

TEST(MapTest, InitializerListConstructor) {
  s21::Map<int, std::string> s21_map = {{1, "one"}, {2, "two"}};
  std::map<int, std::string> std_map = {{1, "one"}, {2, "two"}};
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map.at(1), std_map.at(1));
}

TEST(MapTest, CopyConstructor) {
  s21::Map<int, std::string> s21_orig = {{3, "three"}};
  std::map<int, std::string> std_orig = {{3, "three"}};

  s21::Map<int, std::string> s21_copy(s21_orig);
  std::map<int, std::string> std_copy(std_orig);

  EXPECT_EQ(s21_copy.at(3), std_copy.at(3));
  EXPECT_EQ(s21_orig.size(), std_orig.size());
}

TEST(MapTest, MoveConstructor) {
  s21::Map<int, std::string> s21_orig = {{4, "four"}};
  std::map<int, std::string> std_orig = {{4, "four"}};

  s21::Map<int, std::string> s21_moved(std::move(s21_orig));
  std::map<int, std::string> std_moved(std::move(std_orig));

  EXPECT_EQ(s21_moved.at(4), std_moved.at(4));
  EXPECT_TRUE(s21_orig.empty());
}

TEST(MapTest, InsertNewElement) {
  s21::Map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  auto s21_res = s21_map.insert({5, "five"});
  auto std_res = std_map.insert({5, "five"});

  EXPECT_EQ(s21_res.second, std_res.second);
  EXPECT_EQ(s21_map.at(5), std_map.at(5));
}

TEST(MapTest, InsertExistingElement) {
  s21::Map<int, std::string> s21_map = {{6, "six"}};
  std::map<int, std::string> std_map = {{6, "six"}};

  auto s21_res = s21_map.insert({6, "six_again"});
  auto std_res = std_map.insert({6, "six_again"});

  EXPECT_EQ(s21_res.second, std_res.second);
  EXPECT_EQ(s21_map.at(6), std_map.at(6));
}

TEST(MapTest, InsertOrAssign) {
  s21::Map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  s21_map.insert_or_assign(7, "seven");
  std_map.insert_or_assign(7, "seven");

  EXPECT_EQ(s21_map.at(7), std_map.at(7));
}

TEST(MapTest, EraseElement) {
  s21::Map<int, std::string> s21_map = {{8, "eight"}};
  std::map<int, std::string> std_map = {{8, "eight"}};

  s21_map.erase(s21_map.begin());
  std_map.erase(std_map.begin());

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_FALSE(s21_map.contains(8));
}

TEST(MapTest, SwapMaps) {
  s21::Map<int, std::string> s21_map1 = {{1, "one"}};
  s21::Map<int, std::string> s21_map2 = {{2, "two"}};

  std::map<int, std::string> std_map1 = {{1, "one"}};
  std::map<int, std::string> std_map2 = {{2, "two"}};

  s21_map1.swap(s21_map2);
  std_map1.swap(std_map2);

  EXPECT_EQ(s21_map1.at(2), std_map1.at(2));
  EXPECT_EQ(s21_map2.at(1), std_map2.at(1));
}

TEST(MapTest, MergeMaps) {
  s21::Map<int, std::string> s21_map1 = {{1, "one"}};
  s21::Map<int, std::string> s21_map2 = {{2, "two"}};

  std::map<int, std::string> std_map1 = {{1, "one"}};
  std::map<int, std::string> std_map2 = {{2, "two"}};

  s21_map1.merge(s21_map2);
  std_map1.merge(std_map2);

  EXPECT_EQ(s21_map1.size(), std_map1.size());
  EXPECT_TRUE(s21_map1.contains(2));
}

TEST(MapTest, OperatorSquareBrackets) {
  s21::Map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  s21_map[9] = "nine";
  std_map[9] = "nine";

  EXPECT_EQ(s21_map[9], std_map[9]);
}

TEST(MapTest, AtThrowsException) {
  s21::Map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  EXPECT_THROW(s21_map.at(10), std::out_of_range);
  EXPECT_THROW(std_map.at(10), std::out_of_range);
}

TEST(MapTest, FindExisting) {
  s21::Map<int, std::string> s21_map = {{11, "eleven"}};
  std::map<int, std::string> std_map = {{11, "eleven"}};

  EXPECT_NE(s21_map.find(11), s21_map.end());
  EXPECT_NE(std_map.find(11), std_map.end());
}

TEST(MapTest, FindNonExisting) {
  s21::Map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  EXPECT_EQ(s21_map.find(12), s21_map.end());
  EXPECT_EQ(std_map.find(12), std_map.end());
}

TEST(MapTest, ContainsCheck) {
  s21::Map<int, std::string> s21_map = {{13, "thirteen"}};
  std::map<int, std::string> std_map = {{13, "thirteen"}};

  EXPECT_EQ(s21_map.contains(13), std_map.count(13) > 0);
  EXPECT_EQ(s21_map.contains(14), std_map.count(14) > 0);
}

TEST(MapTest, CountElements) {
  s21::Map<int, std::string> s21_map = {{15, "fifteen"}, {15, "fifteen_dup"}};
  std::map<int, std::string> std_map = {{15, "fifteen"}, {15, "fifteen_dup"}};

  EXPECT_EQ(s21_map.count(15), std_map.count(15));
  EXPECT_EQ(s21_map.count(16), std_map.count(16));
}

TEST(MapTest, LowerBound) {
  s21::Map<int, std::string> s21_map = {{10, "ten"}, {20, "twenty"}};
  std::map<int, std::string> std_map = {{10, "ten"}, {20, "twenty"}};

  auto s21_it = s21_map.lower_bound(15);
  auto std_it = std_map.lower_bound(15);

  EXPECT_EQ(s21_it->first, std_it->first);
}

TEST(MapTest, UpperBound) {
  s21::Map<int, std::string> s21_map = {{10, "ten"}, {20, "twenty"}};
  std::map<int, std::string> std_map = {{10, "ten"}, {20, "twenty"}};

  auto s21_it = s21_map.upper_bound(15);
  auto std_it = std_map.upper_bound(15);

  EXPECT_EQ(s21_it->first, std_it->first);
}

TEST(MapTest, EqualRange) {
  s21::Map<int, std::string> s21_map = {{10, "ten"}, {20, "twenty"}};
  std::map<int, std::string> std_map = {{10, "ten"}, {20, "twenty"}};

  auto s21_pair = s21_map.equal_range(15);
  auto std_pair = std_map.equal_range(15);

  EXPECT_EQ(s21_pair.first->first, std_pair.first->first);
  EXPECT_EQ(s21_pair.second->first, std_pair.second->first);
}

TEST(MapTest, MaxSize) {
  s21::Map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  // Сравнение относительных размеров
  EXPECT_GT(s21_map.max_size(), 0);
  EXPECT_GT(std_map.max_size(), 0);
}