#ifndef S21_SET_H
#define S21_SET_H

#include "s21_red_black_tree.h"

namespace s21 {

template <typename Key, typename Compare = std::less<Key>>
class set {
 private:
  using tree_type = RedBlackTree<Key, Compare>;
  tree_type tree_;

 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;
  using iterator = typename tree_type::iterator;

  set();
  set(std::initializer_list<value_type> const& items);
  set(const set& other);
  set(set&& other) noexcept;
  ~set();
  set& operator=(const set& other);
  set& operator=(set&& other) noexcept;

  iterator begin();
  iterator end();
  iterator end() const;
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  iterator erase(iterator pos);
  void swap(set& other);
  void merge(set& other);
  iterator find(const Key& key) const;
  bool contains(const Key& key) const;
  size_type count(const Key& key) const;
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);
  std::pair<iterator, iterator> equal_range(const Key& key);
};

template <typename Key, typename Compare>
set<Key, Compare>::set() : tree_() {}

template <typename Key, typename Compare>
set<Key, Compare>::set(std::initializer_list<value_type> const& items)
    : tree_() {
  for (const auto& item : items) {
    tree_.insert_unique(item);
  }
}

template <typename Key, typename Compare>
set<Key, Compare>::set(const set& other) : tree_(other.tree_) {}

template <typename Key, typename Compare>
set<Key, Compare>::set(set&& other) noexcept : tree_(std::move(other.tree_)) {}

template <typename Key, typename Compare>
set<Key, Compare>::~set() {}

template <typename Key, typename Compare>
set<Key, Compare>& set<Key, Compare>::operator=(const set& other) {
  tree_ = other.tree_;
  return *this;
}

template <typename Key, typename Compare>
set<Key, Compare>& set<Key, Compare>::operator=(set&& other) noexcept {
  tree_ = std::move(other.tree_);
  return *this;
}

template <typename Key, typename Compare>
typename set<Key, Compare>::iterator set<Key, Compare>::begin() {
  return tree_.begin();
}

template <typename Key, typename Compare>
typename set<Key, Compare>::iterator set<Key, Compare>::end() {
  return tree_.end();
}

template <typename Key, typename Compare>
typename set<Key, Compare>::iterator set<Key, Compare>::end() const {
  return tree_.end();
}

template <typename Key, typename Compare>
bool set<Key, Compare>::empty() const {
  return tree_.empty();
}

template <typename Key, typename Compare>
typename set<Key, Compare>::size_type set<Key, Compare>::size() const {
  return tree_.size();
}

template <typename Key, typename Compare>
typename set<Key, Compare>::size_type set<Key, Compare>::max_size() const {
  return tree_.max_size();
}

template <typename Key, typename Compare>
void set<Key, Compare>::clear() {
  tree_.clear();
}

template <typename Key, typename Compare>
std::pair<typename set<Key, Compare>::iterator, bool> set<Key, Compare>::insert(
    const value_type& value) {
  return tree_.insert(value);
}

template <typename Key, typename Compare>
typename set<Key, Compare>::iterator set<Key, Compare>::erase(iterator pos) {
  return tree_.erase(pos);
}

template <typename Key, typename Compare>
void set<Key, Compare>::swap(set& other) {
  tree_.swap(other.tree_);
}

template <typename Key, typename Compare>
void set<Key, Compare>::merge(set& other) {
  for (auto it = other.begin(); it != other.end();) {
    auto result = insert(*it);
    if (result.second) {
      it = other.erase(it);
    } else {
      ++it;
    }
  }
}

template <typename Key, typename Compare>
typename set<Key, Compare>::iterator set<Key, Compare>::find(
    const Key& key) const {
  return tree_.find(key);
}

template <typename Key, typename Compare>
bool set<Key, Compare>::contains(const Key& key) const {
  return find(key) != end();
}

template <typename Key, typename Compare>
typename set<Key, Compare>::size_type set<Key, Compare>::count(
    const Key& key) const {
  return tree_.count(key);
}

template <typename Key, typename Compare>
typename set<Key, Compare>::iterator set<Key, Compare>::lower_bound(
    const Key& key) {
  return tree_.lower_bound(key);
}

template <typename Key, typename Compare>
typename set<Key, Compare>::iterator set<Key, Compare>::upper_bound(
    const Key& key) {
  return tree_.upper_bound(key);
}

template <typename Key, typename Compare>
std::pair<typename set<Key, Compare>::iterator,
          typename set<Key, Compare>::iterator>
set<Key, Compare>::equal_range(const Key& key) {
  return tree_.equal_range(key);
}

}  // namespace s21
#endif