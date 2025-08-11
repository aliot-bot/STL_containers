#ifndef S21_MAP_H
#define S21_MAP_H

#include <stdexcept>
#include <utility>

#include "s21_red_black_tree.h"

namespace s21 {

template <typename Key, typename Compare = std::less<Key>>
struct MapKeyComparator {
  template <typename T>
  bool operator()(const std::pair<const Key, T>& lhs,
                  const std::pair<const Key, T>& rhs) const {
    return comp(lhs.first, rhs.first);
  }
  Compare comp;
};

template <typename Key, typename T, typename Compare = std::less<Key>>
class Map {
 private:
  using value_type = std::pair<const Key, T>;
  using tree_type = RedBlackTree<value_type, MapKeyComparator<Key, Compare>>;
  tree_type tree_;

 public:
  using key_type = Key;
  using mapped_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;

  Map();
  Map(std::initializer_list<value_type> const& items);
  Map(const Map& other);
  Map(Map&& other) noexcept;
  ~Map();
  Map& operator=(const Map& other);
  Map& operator=(Map&& other) noexcept;

  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void clear() noexcept;
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  iterator erase(iterator pos);
  size_type erase(const Key& key);
  void swap(Map& other) noexcept;
  void merge(Map& other);
  T& operator[](const Key& key);
  T& at(const Key& key);
  const T& at(const Key& key) const;
  iterator find(const Key& key) noexcept;
  const_iterator find(const Key& key) const noexcept;
  bool contains(const Key& key) const noexcept;
  size_type count(const Key& key) const noexcept;
  iterator lower_bound(const Key& key) noexcept;
  const_iterator lower_bound(const Key& key) const noexcept;
  iterator upper_bound(const Key& key) noexcept;
  const_iterator upper_bound(const Key& key) const noexcept;
  std::pair<iterator, iterator> equal_range(const Key& key) noexcept;
  std::pair<const_iterator, const_iterator> equal_range(
      const Key& key) const noexcept;
  template <typename... Args>
  std::pair<iterator, bool> emplace(Args&&... args);
};

template <typename Key, typename T, typename Compare>
Map<Key, T, Compare>::Map() : tree_() {}

template <typename Key, typename T, typename Compare>
Map<Key, T, Compare>::Map(std::initializer_list<value_type> const& items) {
  for (const auto& item : items) {
    insert(item);
  }
}

template <typename Key, typename T, typename Compare>
Map<Key, T, Compare>::Map(const Map& other) : tree_(other.tree_) {}

template <typename Key, typename T, typename Compare>
Map<Key, T, Compare>::Map(Map&& other) noexcept
    : tree_(std::move(other.tree_)) {}

template <typename Key, typename T, typename Compare>
Map<Key, T, Compare>::~Map() {}

template <typename Key, typename T, typename Compare>
Map<Key, T, Compare>& Map<Key, T, Compare>::operator=(const Map& other) {
  tree_ = other.tree_;
  return *this;
}

template <typename Key, typename T, typename Compare>
Map<Key, T, Compare>& Map<Key, T, Compare>::operator=(Map&& other) noexcept {
  tree_ = std::move(other.tree_);
  return *this;
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::iterator Map<Key, T, Compare>::begin() noexcept {
  return tree_.begin();
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::const_iterator Map<Key, T, Compare>::begin()
    const noexcept {
  return tree_.begin();
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::iterator Map<Key, T, Compare>::end() noexcept {
  return tree_.end();
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::const_iterator Map<Key, T, Compare>::end()
    const noexcept {
  return tree_.end();
}

template <typename Key, typename T, typename Compare>
bool Map<Key, T, Compare>::empty() const noexcept {
  return tree_.empty();
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::size_type Map<Key, T, Compare>::size()
    const noexcept {
  return tree_.size();
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::size_type Map<Key, T, Compare>::max_size()
    const noexcept {
  return tree_.max_size();
}

template <typename Key, typename T, typename Compare>
void Map<Key, T, Compare>::clear() noexcept {
  tree_.clear();
}

template <typename Key, typename T, typename Compare>
std::pair<typename Map<Key, T, Compare>::iterator, bool>
Map<Key, T, Compare>::insert(const value_type& value) {
  return tree_.insert(value);
}

template <typename Key, typename T, typename Compare>
std::pair<typename Map<Key, T, Compare>::iterator, bool>
Map<Key, T, Compare>::insert(const Key& key, const T& obj) {
  return insert(std::make_pair(key, obj));
}

template <typename Key, typename T, typename Compare>
std::pair<typename Map<Key, T, Compare>::iterator, bool>
Map<Key, T, Compare>::insert_or_assign(const Key& key, const T& obj) {
  auto it = find(key);
  if (it != end()) {
    it->second = obj;
    return {it, false};
  }
  return insert(std::make_pair(key, obj));
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::iterator Map<Key, T, Compare>::erase(
    iterator pos) {
  return tree_.erase(pos);
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::size_type Map<Key, T, Compare>::erase(
    const Key& key) {
  auto it = find(key);
  if (it != end()) {
    erase(it);
    return 1;
  }
  return 0;
}

template <typename Key, typename T, typename Compare>
void Map<Key, T, Compare>::swap(Map& other) noexcept {
  tree_.swap(other.tree_);
}

template <typename Key, typename T, typename Compare>
void Map<Key, T, Compare>::merge(Map& other) {
  for (auto it = other.begin(); it != other.end();) {
    auto result = insert(*it);
    if (result.second) {
      it = other.erase(it);
    } else {
      ++it;
    }
  }
}

template <typename Key, typename T, typename Compare>
T& Map<Key, T, Compare>::operator[](const Key& key) {
  auto it = find(key);
  if (it == end()) {
    it = insert(std::make_pair(key, T())).first;
  }
  return it->second;
}

template <typename Key, typename T, typename Compare>
T& Map<Key, T, Compare>::at(const Key& key) {
  auto it = find(key);
  if (it == end()) {
    throw std::out_of_range("Key not found in map");
  }
  return it->second;
}

template <typename Key, typename T, typename Compare>
const T& Map<Key, T, Compare>::at(const Key& key) const {
  auto it = find(key);
  if (it == end()) {
    throw std::out_of_range("Key not found in map");
  }
  return it->second;
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::iterator Map<Key, T, Compare>::find(
    const Key& key) noexcept {
  value_type search_pair(key, T());
  return tree_.find(search_pair);
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::const_iterator Map<Key, T, Compare>::find(
    const Key& key) const noexcept {
  value_type search_pair(key, T());
  return tree_.find(search_pair);
}

template <typename Key, typename T, typename Compare>
bool Map<Key, T, Compare>::contains(const Key& key) const noexcept {
  return find(key) != end();
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::size_type Map<Key, T, Compare>::count(
    const Key& key) const noexcept {
  return contains(key) ? 1 : 0;
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::iterator Map<Key, T, Compare>::lower_bound(
    const Key& key) noexcept {
  value_type search_pair(key, T());
  return tree_.lower_bound(search_pair);
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::const_iterator Map<Key, T, Compare>::lower_bound(
    const Key& key) const noexcept {
  value_type search_pair(key, T());
  return tree_.lower_bound(search_pair);
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::iterator Map<Key, T, Compare>::upper_bound(
    const Key& key) noexcept {
  value_type search_pair(key, T());
  return tree_.upper_bound(search_pair);
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::const_iterator Map<Key, T, Compare>::upper_bound(
    const Key& key) const noexcept {
  value_type search_pair(key, T());
  return tree_.upper_bound(search_pair);
}

template <typename Key, typename T, typename Compare>
std::pair<typename Map<Key, T, Compare>::iterator,
          typename Map<Key, T, Compare>::iterator>
Map<Key, T, Compare>::equal_range(const Key& key) noexcept {
  return {lower_bound(key), upper_bound(key)};
}

template <typename Key, typename T, typename Compare>
std::pair<typename Map<Key, T, Compare>::const_iterator,
          typename Map<Key, T, Compare>::const_iterator>
Map<Key, T, Compare>::equal_range(const Key& key) const noexcept {
  return {lower_bound(key), upper_bound(key)};
}

template <typename Key, typename T, typename Compare>
template <typename... Args>
std::pair<typename Map<Key, T, Compare>::iterator, bool>
Map<Key, T, Compare>::emplace(Args&&... args) {
  return tree_.emplace(std::forward<Args>(args)...);
}

}  // namespace s21
#endif