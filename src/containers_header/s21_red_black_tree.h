#ifndef S21_RED_BLACK_TREE_H
#define S21_RED_BLACK_TREE_H

#include <cstddef>
#include <functional>
#include <utility>

namespace s21 {

template <typename T, typename Compare = std::less<T>>
class RedBlackTree {
 private:
  struct Node {
    T value;
    Node* parent;
    Node* left;
    Node* right;
    bool is_red;

    Node(const T& val) : value(val), parent(nullptr), left(nullptr), right(nullptr), is_red(true) {}
  };

  Node* root_;
  size_t size_;
  Compare comp_;

 public:
  using value_type = T;
  using size_type = size_t;

  class TreeIterator {
   private:
    Node* node_;
    Node* root_;
    friend class RedBlackTree;

   public:
    TreeIterator(Node* node = nullptr, Node* root = nullptr);
    value_type& operator*();
    const value_type& operator*() const;
    T* operator->();
    const T* operator->() const;
    TreeIterator& operator++();
    TreeIterator operator++(int);
    TreeIterator& operator--();
    TreeIterator operator--(int);
    bool operator==(const TreeIterator& other) const;
    bool operator!=(const TreeIterator& other) const;
  };

  using iterator = TreeIterator;
  using const_iterator = TreeIterator;

  RedBlackTree();
  RedBlackTree(const RedBlackTree& other);
  RedBlackTree(RedBlackTree&& other) noexcept;
  ~RedBlackTree();
  RedBlackTree& operator=(const RedBlackTree& other);
  RedBlackTree& operator=(RedBlackTree&& other) noexcept;

  iterator begin() const;
  iterator end() const;
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert_unique(const value_type& value);
  std::pair<iterator, bool> insert_multi(const value_type& value);
  iterator erase(iterator pos);
  iterator find(const value_type& value) const;
  iterator lower_bound(const T& value) const;
  iterator upper_bound(const T& value) const;
  std::pair<iterator, iterator> equal_range(const T& value) const;
  void swap(RedBlackTree& other) noexcept;
  void merge(RedBlackTree& other);
  size_type count(const T& value) const;

 private:
  void destroy_tree(Node* node);
  Node* insert_node(Node* node, const T& value);
  void fix_insert(Node* node);
  void rotate_left(Node* node);
  void rotate_right(Node* node);
  Node* find_min(Node* node) const;
  void transplant(Node* u, Node* v);
  void fix_delete(Node* x);
};

template <typename T, typename Compare>
RedBlackTree<T, Compare>::TreeIterator::TreeIterator(Node* node, Node* root)
    : node_(node), root_(root) {}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::value_type&
RedBlackTree<T, Compare>::TreeIterator::operator*() {
  return node_->value;
}

template <typename T, typename Compare>
const typename RedBlackTree<T, Compare>::value_type&
RedBlackTree<T, Compare>::TreeIterator::operator*() const {
  return node_->value;
}

template <typename T, typename Compare>
T* RedBlackTree<T, Compare>::TreeIterator::operator->() {
  return &(node_->value);
}

template <typename T, typename Compare>
const T* RedBlackTree<T, Compare>::TreeIterator::operator->() const {
  return &(node_->value);
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::TreeIterator&
RedBlackTree<T, Compare>::TreeIterator::operator++() {
  if (node_) {
    if (node_->right) {
      node_ = node_->right;
      while (node_->left) {
        node_ = node_->left;
      }
    } else {
      Node* parent = node_->parent;
      while (parent && node_ == parent->right) {
        node_ = parent;
        parent = parent->parent;
      }
      node_ = parent;
    }
  }
  return *this;
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::TreeIterator
RedBlackTree<T, Compare>::TreeIterator::operator++(int) {
  TreeIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::TreeIterator&
RedBlackTree<T, Compare>::TreeIterator::operator--() {
  if (!node_) {
    node_ = root_;
    if (node_) {
      while (node_->right) {
        node_ = node_->right;
      }
    }
  } else if (node_->left) {
    node_ = node_->left;
    while (node_->right) {
      node_ = node_->right;
    }
  } else {
    Node* parent = node_->parent;
    while (parent && node_ == parent->left) {
      node_ = parent;
      parent = parent->parent;
    }
    node_ = parent;
  }
  return *this;
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::TreeIterator
RedBlackTree<T, Compare>::TreeIterator::operator--(int) {
  TreeIterator temp = *this;
  --(*this);
  return temp;
}

template <typename T, typename Compare>
bool RedBlackTree<T, Compare>::TreeIterator::operator==(const TreeIterator& other) const {
  return node_ == other.node_;
}

template <typename T, typename Compare>
bool RedBlackTree<T, Compare>::TreeIterator::operator!=(const TreeIterator& other) const {
  return node_ != other.node_;
}

// Реализация RedBlackTree (только необходимые методы)

template <typename T, typename Compare>
RedBlackTree<T, Compare>::RedBlackTree() : root_(nullptr), size_(0), comp_() {}

template <typename T, typename Compare>
RedBlackTree<T, Compare>::RedBlackTree(const RedBlackTree& other)
    : root_(nullptr), size_(0), comp_(other.comp_) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert_multi(*it);
  }
}

template <typename T, typename Compare>
RedBlackTree<T, Compare>::RedBlackTree(RedBlackTree&& other) noexcept
    : root_(other.root_), size_(other.size_), comp_(other.comp_) {
  other.root_ = nullptr;
  other.size_ = 0;
}

template <typename T, typename Compare>
RedBlackTree<T, Compare>::~RedBlackTree() {
  clear();
}

template <typename T, typename Compare>
RedBlackTree<T, Compare>& RedBlackTree<T, Compare>::operator=(const RedBlackTree& other) {
  if (this != &other) {
    RedBlackTree temp(other);
    swap(temp);
  }
  return *this;
}

template <typename T, typename Compare>
RedBlackTree<T, Compare>& RedBlackTree<T, Compare>::operator=(RedBlackTree&& other) noexcept {
  if (this != &other) {
    clear();
    root_ = other.root_;
    size_ = other.size_;
    comp_ = other.comp_;
    other.root_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::iterator RedBlackTree<T, Compare>::begin() const {
  Node* current = root_;
  while (current && current->left) {
    current = current->left;
  }
  return iterator(current, root_);
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::iterator RedBlackTree<T, Compare>::end() const {
  return iterator(nullptr, root_);
}

template <typename T, typename Compare>
bool RedBlackTree<T, Compare>::empty() const {
  return size_ == 0;
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::size_type RedBlackTree<T, Compare>::size() const {
  return size_;
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::size_type RedBlackTree<T, Compare>::max_size() const {
  return static_cast<size_t>(-1) / sizeof(Node);
}

template <typename T, typename Compare>
void RedBlackTree<T, Compare>::clear() {
  destroy_tree(root_);
  root_ = nullptr;
  size_ = 0;
}

template <typename T, typename Compare>
std::pair<typename RedBlackTree<T, Compare>::iterator, bool>
RedBlackTree<T, Compare>::insert(const value_type& value) {
  iterator existing = find(value);
  if (existing != end() && !comp_(value, *existing) && !comp_(*existing, value)) {
    return {existing, false};
  }

  Node* new_node = insert_node(root_, value);
  if (!root_) {
    root_ = new_node;
  }

  if (new_node) {
    fix_insert(new_node);
    Node* current = root_;
    while (current) {
      if (!comp_(value, current->value) && !comp_(current->value, value)) {
        break;
      }
      current = comp_(value, current->value) ? current->left : current->right;
    }
    ++size_;
    return {iterator(current, root_), true};
  }

  return {end(), false};
}

template <typename T, typename Compare>
std::pair<typename RedBlackTree<T, Compare>::iterator, bool>
RedBlackTree<T, Compare>::insert_unique(const value_type& value) {
  auto found = find(value);
  if (found != end()) {
    return {found, false};
  }
  return insert(value);
}

template <typename T, typename Compare>
std::pair<typename RedBlackTree<T, Compare>::iterator, bool>
RedBlackTree<T, Compare>::insert_multi(const value_type& value) {
  Node* new_node = insert_node(root_, value);
  if (!root_) {
    root_ = new_node;
  }

  if (new_node) {
    fix_insert(new_node);
    Node* current = root_;
    while (current) {
      if (!comp_(value, current->value) && !comp_(current->value, value)) {
        break;
      }
      current = comp_(value, current->value) ? current->left : current->right;
    }
    ++size_;
    return {iterator(current, root_), true};
  }

  return {end(), false};
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::iterator
RedBlackTree<T, Compare>::erase(iterator pos) {
  if (!pos.node_ || !root_) return end();

  Node* z = pos.node_;
  iterator next_iter = pos;
  ++next_iter;

  Node* y = z;
  Node* x = nullptr;
  bool y_original_color = y->is_red;

  if (!z->left) {
    x = z->right;
    transplant(z, z->right);
  } else if (!z->right) {
    x = z->left;
    transplant(z, z->left);
  } else {
    y = find_min(z->right);
    y_original_color = y->is_red;
    x = y->right;
    if (y->parent == z) {
      if (x) x->parent = y;
    } else {
      transplant(y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    transplant(z, y);
    y->left = z->left;
    y->left->parent = y;
    y->is_red = z->is_red;
  }
  if (x && !y_original_color) {
    fix_delete(x);
  } else if (root_) {
    root_->is_red = false;
  }

  --size_;
  delete z;
  return next_iter;
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::iterator
RedBlackTree<T, Compare>::find(const value_type& value) const {
  Node* current = root_;
  while (current) {
    if (!comp_(value, current->value) && !comp_(current->value, value)) {
      return iterator(current, root_);
    }
    current = comp_(value, current->value) ? current->left : current->right;
  }
  return end();
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::iterator
RedBlackTree<T, Compare>::lower_bound(const T& value) const {
  Node* current = root_;
  Node* result = nullptr;
  while (current) {
    if (!comp_(current->value, value)) {
      result = current;
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return iterator(result, root_);
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::iterator
RedBlackTree<T, Compare>::upper_bound(const T& value) const {
  Node* current = root_;
  Node* result = nullptr;
  while (current) {
    if (comp_(value, current->value)) {
      result = current;
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return iterator(result, root_);
}

template <typename T, typename Compare>
std::pair<typename RedBlackTree<T, Compare>::iterator, typename RedBlackTree<T, Compare>::iterator>
RedBlackTree<T, Compare>::equal_range(const T& value) const {
  return {lower_bound(value), upper_bound(value)};
}

template <typename T, typename Compare>
void RedBlackTree<T, Compare>::swap(RedBlackTree& other) noexcept {
  std::swap(root_, other.root_);
  std::swap(size_, other.size_);
  std::swap(comp_, other.comp_);
}

template <typename T, typename Compare>
void RedBlackTree<T, Compare>::merge(RedBlackTree& other) {
  for (auto it = other.begin(); it != other.end();) {
    auto result = insert(*it);
    if (result.second) {
      it = other.erase(it);
    } else {
      ++it;
    }
  }
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::size_type
RedBlackTree<T, Compare>::count(const T& value) const {
  size_type count = 0;
  for (auto it = lower_bound(value); it != upper_bound(value); ++it) {
    ++count;
  }
  return count;
}

template <typename T, typename Compare>
void RedBlackTree<T, Compare>::destroy_tree(Node* node) {
  if (node) {
    destroy_tree(node->left);
    destroy_tree(node->right);
    delete node;
  }
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::Node*
RedBlackTree<T, Compare>::insert_node(Node* node, const T& value) {
  if (!node) {
    try {
      return new Node(value);
    } catch (const std::bad_alloc& e) {
      throw;
    }
  }
  if (comp_(value, node->value)) {
    node->left = insert_node(node->left, value);
    node->left->parent = node;
  } else {
    node->right = insert_node(node->right, value);
    node->right->parent = node;
  }
  return node;
}

template <typename T, typename Compare>
void RedBlackTree<T, Compare>::fix_insert(Node* node) {
  while (node->parent && node->parent->is_red) {
    if (node->parent == node->parent->parent->left) {
      Node* uncle = node->parent->parent->right;
      if (uncle && uncle->is_red) {
        node->parent->is_red = false;
        uncle->is_red = false;
        node->parent->parent->is_red = true;
        node = node->parent->parent;
      } else {
        if (node == node->parent->right) {
          node = node->parent;
          rotate_left(node);
        }
        node->parent->is_red = false;
        node->parent->parent->is_red = true;
        rotate_right(node->parent->parent);
      }
    } else {
      Node* uncle = node->parent->parent->left;
      if (uncle && uncle->is_red) {
        node->parent->is_red = false;
        uncle->is_red = false;
        node->parent->parent->is_red = true;
        node = node->parent->parent;
      } else {
        if (node == node->parent->left) {
          node = node->parent;
          rotate_right(node);
        }
        node->parent->is_red = false;
        node->parent->parent->is_red = true;
        rotate_left(node->parent->parent);
      }
    }
  }
  if (root_) root_->is_red = false;
}

template <typename T, typename Compare>
void RedBlackTree<T, Compare>::rotate_left(Node* node) {
  Node* right_child = node->right;
  node->right = right_child->left;
  if (right_child->left) {
    right_child->left->parent = node;
  }
  right_child->parent = node->parent;
  if (!node->parent) {
    root_ = right_child;
  } else if (node == node->parent->left) {
    node->parent->left = right_child;
  } else {
    node->parent->right = right_child;
  }
  right_child->left = node;
  node->parent = right_child;
}

template <typename T, typename Compare>
void RedBlackTree<T, Compare>::rotate_right(Node* node) {
  Node* left_child = node->left;
  node->left = left_child->right;
  if (left_child->right) {
    left_child->right->parent = node;
  }
  left_child->parent = node->parent;
  if (!node->parent) {
    root_ = left_child;
  } else if (node == node->parent->left) {
    node->parent->left = left_child;
  } else {
    node->parent->right = left_child;
  }
  left_child->right = node;
  node->parent = left_child;
}

template <typename T, typename Compare>
typename RedBlackTree<T, Compare>::Node*
RedBlackTree<T, Compare>::find_min(Node* node) const {
  while (node && node->left) {
    node = node->left;
  }
  return node;
}

template <typename T, typename Compare>
void RedBlackTree<T, Compare>::transplant(Node* u, Node* v) {
  if (!u->parent) {
    root_ = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  if (v) {
    v->parent = u->parent;
  }
}

template <typename T, typename Compare>
void RedBlackTree<T, Compare>::fix_delete(Node* x) {
  while (x != root_ && (!x || !x->is_red)) {
    if (x == nullptr || x == x->parent->left) {
      Node* w = x ? x->parent->right : nullptr;
      if (w && w->is_red) {
        w->is_red = false;
        x->parent->is_red = true;
        rotate_left(x->parent);
        w = x->parent->right;
      }
      if (w && (!w->left || !w->left->is_red) && (!w->right || !w->right->is_red)) {
        w->is_red = true;
        x = x->parent;
      } else if (w) {
        if (!w->right || !w->right->is_red) {
          if (w->left) w->left->is_red = false;
          w->is_red = true;
          rotate_right(w);
          w = x->parent->right;
        }
        w->is_red = x->parent->is_red;
        x->parent->is_red = false;
        if (w->right) w->right->is_red = false;
        rotate_left(x->parent);
        x = root_;
      }
    } else {
      Node* w = x->parent->left;
      if (w && w->is_red) {
        w->is_red = false;
        x->parent->is_red = true;
        rotate_right(x->parent);
        w = x->parent->left;
      }
      if (w && (!w->right || !w->right->is_red) && (!w->left || !w->left->is_red)) {
        w->is_red = true;
        x = x->parent;
      } else if (w) {
        if (!w->left || !w->left->is_red) {
          if (w->right) w->right->is_red = false;
          w->is_red = true;
          rotate_left(w);
          w = x->parent->left;
        }
        w->is_red = x->parent->is_red;
        x->parent->is_red = false;
        if (w->left) w->left->is_red = false;
        rotate_right(x->parent);
        x = root_;
      }
    }
  }
  if (x) x->is_red = false;
}

}  // namespace s21
#endif