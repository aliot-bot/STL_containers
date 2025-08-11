#include <gtest/gtest.h>

#include <list>
#include <stdexcept>

#include "../s21_containers.h"

TEST(ListTest, DefaultConstructor) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  EXPECT_EQ(s21_list.empty(), std_list.empty());
  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(ListTest, InitializerListConstructor) {
  s21::list<int> s21_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  EXPECT_EQ(s21_list.size(), std_list.size());
  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  for (; s21_it != s21_list.end() && std_it != std_list.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(ListTest, CopyConstructor) {
  s21::list<int> s21_list1 = {1, 2, 3};
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list2(s21_list1);
  std::list<int> std_list2(std_list1);
  EXPECT_EQ(s21_list2.size(), std_list2.size());
  auto s21_it = s21_list2.begin();
  auto std_it = std_list2.begin();
  for (; s21_it != s21_list2.end() && std_it != std_list2.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(ListTest, MoveConstructor) {
  s21::list<int> s21_list1 = {1, 2, 3};
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list2(std::move(s21_list1));
  std::list<int> std_list2(std::move(std_list1));
  EXPECT_EQ(s21_list2.size(), std_list2.size());
  EXPECT_EQ(s21_list1.size(), std_list1.size());
  auto s21_it = s21_list2.begin();
  auto std_it = std_list2.begin();
  for (; s21_it != s21_list2.end() && std_it != std_list2.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(ListTest, SizeNConstructor) {
  s21::list<int> s21_list(5);
  std::list<int> std_list(5);
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(ListTest, FrontBack) {
  s21::list<int> s21_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
}

TEST(ListTest, EmptySizeMaxSize) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  EXPECT_EQ(s21_list.empty(), std_list.empty());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_GT(s21_list.max_size(), 0);
}

TEST(ListTest, PushBackPushFront) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  s21_list.push_back(1);
  std_list.push_back(1);
  s21_list.push_front(2);
  std_list.push_front(2);
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(ListTest, PopBackPopFront) {
  s21::list<int> s21_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21_list.pop_back();
  std_list.pop_back();
  s21_list.pop_front();
  std_list.pop_front();
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(ListTest, InsertErase) {
  s21::list<int> s21_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  ++s21_it;
  ++std_it;
  s21_list.insert(s21_it, 4);
  std_list.insert(std_it, 4);
  s21_it = s21_list.begin();
  std_it = std_list.begin();
  ++s21_it;
  ++std_it;
  s21_list.erase(s21_it);
  std_list.erase(std_it);
  EXPECT_EQ(s21_list.size(), std_list.size());
  s21_it = s21_list.begin();
  std_it = std_list.begin();
  for (; s21_it != s21_list.end() && std_it != std_list.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(ListTest, InsertAtBeginning) {
  s21::list<int> s21_list = {2, 3};
  std::list<int> std_list = {2, 3};
  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  s21_list.insert(s21_it, 1);
  std_list.insert(std_it, 1);
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.front(), std_list.front());
}

TEST(ListTest, InsertAtEnd) {
  s21::list<int> s21_list = {1, 2};
  std::list<int> std_list = {1, 2};
  auto s21_it = s21_list.end();
  auto std_it = std_list.end();
  s21_list.insert(s21_it, 3);
  std_list.insert(std_it, 3);
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.back(), std_list.back());
}

TEST(ListTest, InsertInMiddle) {
  s21::list<int> s21_list = {1, 3};
  std::list<int> std_list = {1, 3};
  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  ++s21_it;
  ++std_it;
  s21_list.insert(s21_it, 2);
  std_list.insert(std_it, 2);
  EXPECT_EQ(s21_list.size(), std_list.size());
  auto s21_check = s21_list.begin();
  auto std_check = std_list.begin();
  ++s21_check;
  ++std_check;
  EXPECT_EQ(*s21_check, *std_check);
}

TEST(ListTest, InsertIntoEmptyList) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  s21_list.insert(s21_it, 1);
  std_list.insert(std_it, 1);
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
}

TEST(ListTest, EraseFromBeginning) {
  s21::list<int> s21_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  s21_list.erase(s21_it);
  std_list.erase(std_it);
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.front(), std_list.front());
}

TEST(ListTest, EraseFromEnd) {
  s21::list<int> s21_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  auto s21_it = s21_list.end();
  --s21_it;
  auto std_it = std_list.end();
  --std_it;

  s21_list.erase(s21_it);
  std_list.erase(std_it);

  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.back(), std_list.back());
}

TEST(ListTest, EraseFromMiddle) {
  s21::list<int> s21_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  ++s21_it;
  ++std_it;
  s21_list.erase(s21_it);
  std_list.erase(std_it);
  EXPECT_EQ(s21_list.size(), std_list.size());
  auto s21_check = s21_list.begin();
  auto std_check = std_list.begin();
  ++s21_check;
  ++std_check;
  EXPECT_EQ(*s21_check, *std_check);
}

TEST(ListTest, EraseSingleElement) {
  s21::list<int> s21_list = {1};
  std::list<int> std_list = {1};
  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  s21_list.erase(s21_it);
  std_list.erase(std_it);
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(ListTest, EraseInvalidIterator) {
  s21::list<int> s21_list = {1, 2, 3};
  auto s21_it = s21_list.end();
  EXPECT_THROW(s21_list.erase(s21_it), std::out_of_range);
}

TEST(ListTest, Clear) {
  s21::list<int> s21_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21_list.clear();
  std_list.clear();
  EXPECT_EQ(s21_list.empty(), std_list.empty());
  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(ListTest, Swap) {
  s21::list<int> s21_list1 = {1, 2};
  s21::list<int> s21_list2 = {3, 4};
  std::list<int> std_list1 = {1, 2};
  std::list<int> std_list2 = {3, 4};
  s21_list1.swap(s21_list2);
  std_list1.swap(std_list2);
  EXPECT_EQ(s21_list1.size(), std_list1.size());
  EXPECT_EQ(s21_list2.size(), std_list2.size());
  auto s21_it1 = s21_list1.begin();
  auto std_it1 = std_list1.begin();
  auto s21_it2 = s21_list2.begin();
  auto std_it2 = std_list2.begin();
  for (; s21_it1 != s21_list1.end() && std_it1 != std_list1.end();
       ++s21_it1, ++std_it1) {
    EXPECT_EQ(*s21_it1, *std_it1);
  }
  for (; s21_it2 != s21_list2.end() && std_it2 != std_list2.end();
       ++s21_it2, ++std_it2) {
    EXPECT_EQ(*s21_it2, *std_it2);
  }
}

TEST(ListTest, Merge) {
  s21::list<int> s21_list1 = {1, 3, 5};
  s21::list<int> s21_list2 = {2, 4, 6};
  std::list<int> std_list1 = {1, 3, 5};
  std::list<int> std_list2 = {2, 4, 6};
  s21_list1.merge(s21_list2);
  std_list1.merge(std_list2);
  EXPECT_EQ(s21_list1.size(), std_list1.size());
  auto s21_it = s21_list1.begin();
  auto std_it = std_list1.begin();
  for (; s21_it != s21_list1.end() && std_it != std_list1.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(ListTest, Splice) {
  s21::list<int> s21_list1 = {1, 2, 3};
  s21::list<int> s21_list2 = {4, 5};
  std::list<int> std_list1 = {1, 2, 3};
  std::list<int> std_list2 = {4, 5};
  auto s21_it = s21_list1.begin();
  auto std_it = std_list1.begin();
  ++s21_it;
  ++std_it;
  EXPECT_EQ(s21_list1.size(), std_list1.size());
  s21_it = s21_list1.begin();
  std_it = std_list1.begin();
  for (; s21_it != s21_list1.end() && std_it != std_list1.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(ListTest, Reverse) {
  s21::list<int> s21_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21_list.reverse();
  std_list.reverse();
  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  for (; s21_it != s21_list.end() && std_it != std_list.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(ListTest, Unique) {
  s21::list<int> s21_list = {1, 1, 2, 2, 3};
  std::list<int> std_list = {1, 1, 2, 2, 3};
  s21_list.unique();
  std_list.unique();
  EXPECT_EQ(s21_list.size(), std_list.size());
  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  for (; s21_it != s21_list.end() && std_it != std_list.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(ListTest, Sort) {
  s21::list<int> s21_list = {3, 1, 4, 1, 5};
  std::list<int> std_list = {3, 1, 4, 1, 5};
  s21_list.sort();
  std_list.sort();
  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  for (; s21_it != s21_list.end() && std_it != std_list.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(ListTest, EraseSingleElementWithEnd) {
  s21::list<int> s21_list = {1};
  std::list<int> std_list = {1};
  auto s21_it = s21_list.end();
  --s21_it;
  auto std_it = std_list.end();
  --std_it;
  s21_list.erase(s21_it);
  std_list.erase(std_it);
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_TRUE(s21_list.empty());
  EXPECT_TRUE(std_list.empty());
}

TEST(ListTest, IteratorComparison) {
  s21::list<int> s21_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  auto s21_it1 = s21_list.begin();
  auto s21_it2 = s21_list.end();
  auto std_it1 = std_list.begin();
  auto std_it2 = std_list.end();
  EXPECT_TRUE(s21_it1 != s21_it2);
  EXPECT_TRUE(std_it1 != std_it2);
  ++s21_it1;
  ++std_it1;
  EXPECT_TRUE(s21_it1 != s21_it2);
  EXPECT_TRUE(std_it1 != std_it2);
  EXPECT_FALSE(s21_it1 == s21_it2);
  EXPECT_FALSE(std_it1 == std_it2);
}

TEST(ListTest, ConstIteratorAccess) {
  const s21::list<int> s21_list = {1, 2, 3};
  const std::list<int> std_list = {1, 2, 3};
  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  EXPECT_EQ(*s21_it, *std_it);
  ++s21_it;
  ++std_it;
  EXPECT_EQ(*s21_it, *std_it);
}

TEST(ListTest, LargeListOperations) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  for (int i = 0; i < 1000; ++i) {
    s21_list.push_back(i);
    std_list.push_back(i);
  }
  EXPECT_EQ(s21_list.size(), std_list.size());
  auto s21_it = s21_list.begin();
  auto std_it = std_list.begin();
  for (int i = 0; i < 500; ++i, ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
  s21_list.erase(s21_it);
  std_list.erase(std_it);
  EXPECT_EQ(s21_list.size(), std_list.size());
  s21_list.reverse();
  std_list.reverse();
  s21_it = s21_list.begin();
  std_it = std_list.begin();
  for (int i = 0; i < 500; ++i, ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(ListTest, ComplexModification) {
  s21::list<int> s21_list1 = {1, 3, 5};
  s21::list<int> s21_list2 = {2, 4, 6};
  std::list<int> std_list1 = {1, 3, 5};
  std::list<int> std_list2 = {2, 4, 6};
  s21_list1.merge(s21_list2);
  std_list1.merge(std_list2);
  EXPECT_EQ(s21_list1.size(), std_list1.size());
  auto s21_it = s21_list1.begin();
  auto std_it = std_list1.begin();
  for (; s21_it != s21_list1.end() && std_it != std_list1.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
  s21_it = s21_list1.begin();
  std_it = std_list1.begin();
  ++s21_it;
  ++std_it;
  s21_list1.erase(s21_it);
  std_list1.erase(std_it);
  EXPECT_EQ(s21_list1.size(), std_list1.size());
  s21_list1.reverse();
  std_list1.reverse();
  s21_it = s21_list1.begin();
  std_it = std_list1.begin();
  for (; s21_it != s21_list1.end() && std_it != std_list1.end();
       ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}