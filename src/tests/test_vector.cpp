#include <gtest/gtest.h>

#include <limits>
#include <vector>

#include "../s21_containers.h"

TEST(VectorTest, DefaultConstructor) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  EXPECT_EQ(s21_v.size(), 0u);
  EXPECT_EQ(s21_v.capacity(), 0u);
  EXPECT_TRUE(s21_v.empty());
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());
}

TEST(VectorTest, ParameterizedConstructor) {
  s21::vector<int> s21_v(5);
  std::vector<int> std_v(5);
  EXPECT_EQ(s21_v.size(), 5u);
  EXPECT_GE(s21_v.capacity(), 5u);
  for (size_t i = 0; i < s21_v.size(); ++i) {
    EXPECT_EQ(s21_v[i], 0);
  }
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  for (size_t i = 0; i < s21_v.size(); ++i) {
    EXPECT_EQ(s21_v[i], std_v[i]);
  }

  // Краевой случай: ноль элементов
  s21::vector<int> s21_v_zero(0);
  std::vector<int> std_v_zero(0);
  EXPECT_EQ(s21_v_zero.size(), 0u);
  EXPECT_EQ(s21_v_zero.capacity(), 0u);
  EXPECT_TRUE(s21_v_zero.empty());
  EXPECT_EQ(s21_v_zero.size(), std_v_zero.size());
  EXPECT_EQ(s21_v_zero.capacity(), std_v_zero.capacity());

  // Краевой случай: максимальный размер
  size_t max_size = s21_v.max_size();
  EXPECT_THROW(s21::vector<int>(max_size + 1), std::bad_alloc);  // Переполнение
}

TEST(VectorTest, InitializerListConstructor) {
  s21::vector<int> s21_v = {1, 2, 3, 4};
  std::vector<int> std_v = {1, 2, 3, 4};
  EXPECT_EQ(s21_v.size(), 4u);
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  for (size_t i = 0; i < s21_v.size(); ++i) {
    EXPECT_EQ(s21_v[i], std_v[i]);
  }

  // Краевой случай: пустой initializer_list
  s21::vector<int> s21_v_empty = {};
  std::vector<int> std_v_empty = {};
  EXPECT_EQ(s21_v_empty.size(), 0u);
  EXPECT_EQ(s21_v_empty.capacity(), 0u);
  EXPECT_TRUE(s21_v_empty.empty());
  EXPECT_EQ(s21_v_empty.size(), std_v_empty.size());
  EXPECT_EQ(s21_v_empty.capacity(), std_v_empty.capacity());

  // Краевой случай: один элемент
  s21::vector<int> s21_v_one = {42};
  std::vector<int> std_v_one = {42};
  EXPECT_EQ(s21_v_one.size(), 1u);
  EXPECT_EQ(s21_v_one[0], 42);
  EXPECT_EQ(s21_v_one.size(), std_v_one.size());
  EXPECT_EQ(s21_v_one[0], std_v_one[0]);
}

TEST(VectorTest, CopyConstructor) {
  s21::vector<int> s21_v1 = {1, 2, 3};
  std::vector<int> std_v1 = {1, 2, 3};
  s21::vector<int> s21_v2(s21_v1);
  std::vector<int> std_v2(std_v1);
  EXPECT_EQ(s21_v2.size(), s21_v1.size());
  EXPECT_EQ(s21_v2.capacity(), s21_v1.capacity());
  for (size_t i = 0; i < s21_v2.size(); ++i) {
    EXPECT_EQ(s21_v2[i], s21_v1[i]);
  }
  EXPECT_EQ(s21_v2.size(), std_v2.size());
  EXPECT_EQ(s21_v2.capacity(), std_v2.capacity());
  for (size_t i = 0; i < s21_v2.size(); ++i) {
    EXPECT_EQ(s21_v2[i], std_v2[i]);
  }
  s21_v2[0] = 99;
  std_v2[0] = 99;
  EXPECT_EQ(s21_v1[0], 1);  // Оригинал не изменен
  EXPECT_EQ(std_v1[0], 1);

  // Краевой случай: копирование пустого вектора
  s21::vector<int> s21_v_empty;
  std::vector<int> std_v_empty;
  s21::vector<int> s21_v_copy_empty(s21_v_empty);
  std::vector<int> std_v_copy_empty(std_v_empty);
  EXPECT_EQ(s21_v_copy_empty.size(), 0u);
  EXPECT_EQ(s21_v_copy_empty.capacity(), 0u);
  EXPECT_EQ(s21_v_copy_empty.size(), std_v_copy_empty.size());
  EXPECT_EQ(s21_v_copy_empty.capacity(), std_v_copy_empty.capacity());
}

TEST(VectorTest, MoveConstructor) {
  s21::vector<int> s21_v1 = {1, 2, 3};
  std::vector<int> std_v1 = {1, 2, 3};
  s21::vector<int> s21_v2(std::move(s21_v1));
  std::vector<int> std_v2(std::move(std_v1));
  EXPECT_EQ(s21_v2.size(), 3u);
  EXPECT_EQ(s21_v2.capacity(), std_v2.capacity());
  for (size_t i = 0; i < s21_v2.size(); ++i) {
    EXPECT_EQ(s21_v2[i], std_v2[i]);
  }
  EXPECT_EQ(s21_v1.size(), 0u);  // Оригинал пуст
  EXPECT_EQ(std_v1.size(), 0u);
  EXPECT_EQ(s21_v1.capacity(), 0u);
  EXPECT_EQ(std_v1.capacity(), 0u);

  // Краевой случай: перемещение пустого вектора
  s21::vector<int> s21_v_empty;
  std::vector<int> std_v_empty;
  s21::vector<int> s21_v_move_empty(std::move(s21_v_empty));
  std::vector<int> std_v_move_empty(std::move(std_v_empty));
  EXPECT_EQ(s21_v_move_empty.size(), 0u);
  EXPECT_EQ(s21_v_move_empty.capacity(), 0u);
  EXPECT_EQ(s21_v_empty.size(), 0u);
  EXPECT_EQ(s21_v_empty.capacity(), 0u);
  EXPECT_EQ(s21_v_move_empty.size(), std_v_move_empty.size());
  EXPECT_EQ(s21_v_move_empty.capacity(), std_v_move_empty.capacity());
}

TEST(VectorTest, AccessMethods) {
  s21::vector<int> s21_v = {10, 20, 30};
  std::vector<int> std_v = {10, 20, 30};
  EXPECT_EQ(s21_v.at(1), 20);
  EXPECT_EQ(s21_v[1], 20);
  EXPECT_EQ(s21_v.front(), 10);
  EXPECT_EQ(s21_v.back(), 30);
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v[1], std_v[1]);
  EXPECT_EQ(s21_v.front(), std_v.front());
  EXPECT_EQ(s21_v.back(), std_v.back());
  EXPECT_THROW(s21_v.at(3), std::out_of_range);  // Выход за пределы
  // Исправление: Ожидаем std::out_of_range, а не std::bad_alloc
  EXPECT_THROW(s21_v.at(s21_v.size()), std::out_of_range);  // Граница size
  s21_v.clear();
  std_v.clear();
  EXPECT_THROW(s21_v.front(), std::out_of_range);
  EXPECT_THROW(s21_v.back(), std::out_of_range);
  EXPECT_THROW(s21_v.at(0), std::out_of_range);

  s21_v.push_back(1);
  std_v.push_back(1);                           // Синхронизируем добавление
  EXPECT_EQ(s21_v.data()[0], std_v.data()[0]);  // Должно совпадать
}

TEST(VectorTest, CapacityMethods) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  EXPECT_TRUE(s21_v.empty());
  EXPECT_EQ(s21_v.size(), 0u);
  EXPECT_EQ(s21_v.capacity(), 0u);
  EXPECT_GT(s21_v.max_size(), 0u);  // Исправление: не требуем точного равенства
  s21_v.reserve(10);
  std_v.reserve(10);
  EXPECT_GE(s21_v.capacity(), 10u);
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  s21_v.push_back(1);
  std_v.push_back(1);
  s21_v.shrink_to_fit();
  std_v.shrink_to_fit();
  EXPECT_EQ(s21_v.capacity(), 1u);  // Ожидаем минимальную емкость
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  s21_v.clear();
  std_v.clear();
  EXPECT_EQ(s21_v.size(), 0u);
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());  // Емкость сохраняется
  EXPECT_TRUE(s21_v.empty());

  // Краевой случай: переполнение reserve
  size_t max_capacity = s21_v.max_size();
  EXPECT_THROW(s21_v.reserve(max_capacity + 1), std::bad_alloc);

  // Краевой случай: shrink_to_fit на пустом
  s21_v.shrink_to_fit();
  EXPECT_EQ(s21_v.capacity(), 0u);
}

TEST(VectorTest, Modifiers) {
  s21::vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};
  s21_v.push_back(4);
  std_v.push_back(4);
  EXPECT_EQ(s21_v.size(), 4u);
  EXPECT_EQ(s21_v.back(), 4);
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.back(), std_v.back());
  s21_v.pop_back();
  std_v.pop_back();
  EXPECT_EQ(s21_v.size(), 3u);
  EXPECT_EQ(s21_v.back(), 3);
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.back(), std_v.back());
  auto s21_it = s21_v.begin();
  auto std_it = std_v.begin();
  ++s21_it;
  ++std_it;
  s21_v.insert(s21_it, 5);
  std_v.insert(std_it, 5);
  EXPECT_EQ(s21_v.size(), 4u);
  EXPECT_EQ(s21_v[1], 5);
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v[1], std_v[1]);
  s21_v.erase(s21_it);
  std_v.erase(std_it);
  EXPECT_EQ(s21_v.size(), 3u);
  EXPECT_EQ(s21_v[1], 2);
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v[1], std_v[1]);

  // Краевые случаи
  s21::vector<int> s21_v_empty;
  std::vector<int> std_v_empty;
  EXPECT_THROW(s21_v_empty.pop_back(), std::out_of_range);
  EXPECT_THROW(s21_v_empty.erase(s21_v_empty.begin()), std::out_of_range);
  s21_v_empty.push_back(1);
  std_v_empty.push_back(1);
  s21_v_empty.insert(s21_v_empty.begin(), 2);
  std_v_empty.insert(std_v_empty.begin(), 2);
  EXPECT_EQ(s21_v_empty.size(), 2u);
  EXPECT_EQ(s21_v_empty[0], 2);
  EXPECT_EQ(s21_v_empty.size(), std_v_empty.size());
  EXPECT_EQ(s21_v_empty[0], std_v_empty[0]);

  // Тест swap
  s21::vector<int> s21_v2 = {4, 5, 6};
  std::vector<int> std_v2 = {4, 5, 6};
  s21_v.swap(s21_v2);
  std_v.swap(std_v2);
  EXPECT_EQ(s21_v.size(), 3u);
  EXPECT_EQ(s21_v2.size(), 3u);
  for (size_t i = 0; i < s21_v.size(); ++i) {
    EXPECT_EQ(s21_v[i], std_v[i]);
  }
  for (size_t i = 0; i < s21_v2.size(); ++i) {
    EXPECT_EQ(s21_v2[i], std_v2[i]);
  }
}
TEST(VectorTest, PushBackMultipleElements) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  for (int i = 0; i < 10; ++i) {
    s21_v.push_back(i);
    std_v.push_back(i);
  }
  EXPECT_EQ(s21_v.size(), 10u);
  EXPECT_EQ(s21_v.size(), std_v.size());
  for (size_t i = 0; i < s21_v.size(); ++i) {
    EXPECT_EQ(s21_v[i], std_v[i]);
  }
}

TEST(VectorTest, PopBackSingleElement) {
  s21::vector<int> s21_v = {1};
  std::vector<int> std_v = {1};
  s21_v.pop_back();
  std_v.pop_back();
  EXPECT_EQ(s21_v.size(), 0u);
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_TRUE(s21_v.empty());
  EXPECT_TRUE(std_v.empty());
}

TEST(VectorTest, InsertAtBeginning) {
  s21::vector<int> s21_v = {2, 3};
  std::vector<int> std_v = {2, 3};
  auto s21_it = s21_v.begin();
  auto std_it = std_v.begin();
  s21_v.insert(s21_it, 1);
  std_v.insert(std_it, 1);
  EXPECT_EQ(s21_v.size(), 3u);
  EXPECT_EQ(s21_v.size(), std_v.size());
  for (size_t i = 0; i < s21_v.size(); ++i) {
    EXPECT_EQ(s21_v[i], std_v[i]);
  }
}

TEST(VectorTest, InsertAtEnd) {
  s21::vector<int> s21_v = {1, 2};
  std::vector<int> std_v = {1, 2};
  auto s21_it = s21_v.end();
  auto std_it = std_v.end();
  s21_v.insert(s21_it, 3);
  std_v.insert(std_it, 3);
  EXPECT_EQ(s21_v.size(), 3u);
  EXPECT_EQ(s21_v.size(), std_v.size());
  for (size_t i = 0; i < s21_v.size(); ++i) {
    EXPECT_EQ(s21_v[i], std_v[i]);
  }
}

TEST(VectorTest, EraseFirstElement) {
  s21::vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};
  auto s21_it = s21_v.begin();
  auto std_it = std_v.begin();
  s21_v.erase(s21_it);
  std_v.erase(std_it);
  EXPECT_EQ(s21_v.size(), 2u);
  EXPECT_EQ(s21_v.size(), std_v.size());
  for (size_t i = 0; i < s21_v.size(); ++i) {
    EXPECT_EQ(s21_v[i], std_v[i]);
  }
}

TEST(VectorTest, ClearWithData) {
  s21::vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};
  s21_v.clear();
  std_v.clear();
  EXPECT_EQ(s21_v.size(), 0u);
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_TRUE(s21_v.empty());
  EXPECT_TRUE(std_v.empty());
}

TEST(VectorTest, ClearEmptyVector) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  s21_v.clear();
  std_v.clear();
  EXPECT_EQ(s21_v.size(), 0u);
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_TRUE(s21_v.empty());
  EXPECT_TRUE(std_v.empty());
  EXPECT_EQ(s21_v.data(), nullptr);
  EXPECT_EQ(std_v.data(), nullptr);
}

TEST(VectorTest, SwapSameSize) {
  s21::vector<int> s21_v1 = {1, 2, 3};
  s21::vector<int> s21_v2 = {4, 5, 6};
  std::vector<int> std_v1 = {1, 2, 3};
  std::vector<int> std_v2 = {4, 5, 6};
  s21_v1.swap(s21_v2);
  std_v1.swap(std_v2);
  EXPECT_EQ(s21_v1.size(), 3u);
  EXPECT_EQ(s21_v2.size(), 3u);
  EXPECT_EQ(s21_v1.size(), std_v1.size());
  EXPECT_EQ(s21_v2.size(), std_v2.size());
  for (size_t i = 0; i < s21_v1.size(); ++i) {
    EXPECT_EQ(s21_v1[i], std_v1[i]);
  }
  for (size_t i = 0; i < s21_v2.size(); ++i) {
    EXPECT_EQ(s21_v2[i], std_v2[i]);
  }
}

TEST(VectorTest, SwapDifferentSize) {
  s21::vector<int> s21_v1 = {1, 2};
  s21::vector<int> s21_v2 = {3, 4, 5};
  std::vector<int> std_v1 = {1, 2};
  std::vector<int> std_v2 = {3, 4, 5};
  s21_v1.swap(s21_v2);
  std_v1.swap(std_v2);
  EXPECT_EQ(s21_v1.size(), 3u);
  EXPECT_EQ(s21_v2.size(), 2u);
  EXPECT_EQ(s21_v1.size(), std_v1.size());
  EXPECT_EQ(s21_v2.size(), std_v2.size());
  for (size_t i = 0; i < s21_v1.size(); ++i) {
    EXPECT_EQ(s21_v1[i], std_v1[i]);
  }
  for (size_t i = 0; i < s21_v2.size(); ++i) {
    EXPECT_EQ(s21_v2[i], std_v2[i]);
  }
}

TEST(VectorTest, SwapEmptyVectors) {
  s21::vector<int> s21_v1;
  s21::vector<int> s21_v2;
  std::vector<int> std_v1;
  std::vector<int> std_v2;
  s21_v1.swap(s21_v2);
  std_v1.swap(std_v2);
  EXPECT_EQ(s21_v1.size(), 0u);
  EXPECT_EQ(s21_v2.size(), 0u);
  EXPECT_EQ(s21_v1.size(), std_v1.size());
  EXPECT_EQ(s21_v2.size(), std_v2.size());
  EXPECT_EQ(s21_v1.capacity(), std_v1.capacity());
  EXPECT_EQ(s21_v2.capacity(), std_v2.capacity());
}