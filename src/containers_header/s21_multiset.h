#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include "s21_red_black_tree.h"

namespace s21 {

template <typename Key, typename Compare = std::less<Key>>
class multiset {
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
  using const_iterator = typename tree_type::iterator;

  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& ms);
  multiset(multiset&& ms) noexcept;
  ~multiset();
  multiset& operator=(const multiset& ms);
  multiset& operator=(multiset&& ms) noexcept;

  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void clear();
  iterator insert(const value_type& value);
  iterator erase(iterator pos);
  void swap(multiset& other);
  void merge(multiset& other);

  size_type count(const Key& key) const;
  iterator find(const Key& key) const;
  bool contains(const Key& key) const;
  std::pair<iterator, iterator> equal_range(const Key& key) const;
  iterator lower_bound(const Key& key);
  const_iterator lower_bound(const Key& key) const;
  iterator upper_bound(const Key& key);
  const_iterator upper_bound(const Key& key) const;
};

// Реализация методов вне класса

template <typename Key, typename Compare>
multiset<Key, Compare>::multiset() : tree_() {}

template <typename Key, typename Compare>
multiset<Key, Compare>::multiset(std::initializer_list<value_type> const& items) : tree_() {
  for (const auto& item : items) {
    insert(item);
  }
}

template <typename Key, typename Compare>
multiset<Key, Compare>::multiset(const multiset& ms) : tree_(ms.tree_) {}

template <typename Key, typename Compare>
multiset<Key, Compare>::multiset(multiset&& ms) noexcept : tree_(std::move(ms.tree_)) {}

template <typename Key, typename Compare>
multiset<Key, Compare>::~multiset() {}

template <typename Key, typename Compare>
multiset<Key, Compare>& multiset<Key, Compare>::operator=(const multiset& ms) {
  tree_ = ms.tree_;
  return *this;
}

template <typename Key, typename Compare>
multiset<Key, Compare>& multiset<Key, Compare>::operator=(multiset&& ms) noexcept {
  tree_ = std::move(ms.tree_);
  return *this;
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::begin() noexcept {
  return tree_.begin();
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::const_iterator multiset<Key, Compare>::begin() const noexcept {
  return tree_.begin();
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::end() noexcept {
  return tree_.end();
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::const_iterator multiset<Key, Compare>::end() const noexcept {
  return tree_.end();
}

template <typename Key, typename Compare>
bool multiset<Key, Compare>::empty() const noexcept {
  return tree_.empty();
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::size_type multiset<Key, Compare>::size() const noexcept {
  return tree_.size();
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::size_type multiset<Key, Compare>::max_size() const noexcept {
  return tree_.max_size();
}

template <typename Key, typename Compare>
void multiset<Key, Compare>::clear() {
  tree_.clear();
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::insert(const value_type& value) {
  return tree_.insert_multi(value).first;
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::erase(iterator pos) {
  return tree_.erase(pos);
}

template <typename Key, typename Compare>
void multiset<Key, Compare>::swap(multiset& other) {
  tree_.swap(other.tree_);
}

template <typename Key, typename Compare>
void multiset<Key, Compare>::merge(multiset& other) {
  iterator it = other.begin();
  while (it != other.end()) {
    insert(*it);
    it = other.erase(it);
  }
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::size_type multiset<Key, Compare>::count(const Key& key) const {
  size_type cnt = 0;
    for (auto it = begin(); it != end(); ++it) {
      if (!Compare()(*it, key) && !Compare()(key, *it)) {
        ++cnt;
      }
    }
    return cnt;
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::find(const Key& key) const {
  return tree_.find(key);
}

template <typename Key, typename Compare>
bool multiset<Key, Compare>::contains(const Key& key) const {
  return find(key) != end();
}

template <typename Key, typename Compare>
std::pair<typename multiset<Key, Compare>::iterator, typename multiset<Key, Compare>::iterator>
multiset<Key, Compare>::equal_range(const Key& key) const {
  return tree_.equal_range(key);
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::lower_bound(const Key& key) {
  return tree_.lower_bound(key);
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::const_iterator
multiset<Key, Compare>::lower_bound(const Key& key) const {
  return tree_.lower_bound(key);
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::upper_bound(const Key& key) {
  return tree_.upper_bound(key);
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::const_iterator
multiset<Key, Compare>::upper_bound(const Key& key) const {
  return tree_.upper_bound(key);
}

}  // namespace s21
#endif