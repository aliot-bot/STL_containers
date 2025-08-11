#ifndef S21_LIST_H
#define S21_LIST_H

#include <stdexcept>
#include <utility>

namespace s21 {

template <typename T>
class list {
 private:
  struct Node {
    T value;
    Node* next;
    Node* prev;
    Node(const T& val = T(), Node* n = nullptr, Node* p = nullptr)
        : value(val), next(n), prev(p) {}
  };

  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  Node* end_node_ = nullptr;
  size_t size_ = 0;

  void initialize_end_node();

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  // класс для итератора
  class ListIterator {
   public:
    Node* ptr_;
    ListIterator(Node* ptr = nullptr) : ptr_(ptr) {}
    T& operator*() { return ptr_->value; }
    ListIterator& operator++();
    ListIterator& operator--();
    bool operator==(const ListIterator& other) const;
    bool operator!=(const ListIterator& other) const;
  };

  // класс для констатного итератора
  class ListConstIterator {
   public:
    const Node* ptr_;
    ListConstIterator(const Node* ptr = nullptr) : ptr_(ptr) {}
    const T& operator*() const { return ptr_->value; }
    ListConstIterator& operator++();
    ListConstIterator& operator--();
    bool operator==(const ListConstIterator& other) const;
    bool operator!=(const ListConstIterator& other) const;
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  // конструкторы
  list();
  list(std::initializer_list<value_type> const& items);
  list(const list& other);
  list(list&& other) noexcept;
  explicit list(size_type n);
  ~list();

  // операторы
  list& operator=(list&& other) noexcept;

  // доступ к элементам класса
  reference front();
  reference back();
  const_reference front() const;
  const_reference back() const;

  // доступ к итераторам
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  // методы емкости
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  // модификаторы
  void clear();
  iterator insert(iterator pos, const_reference value);
  void push_back(const_reference value);
  void push_front(const_reference value);
  void erase(iterator pos);
  void pop_back();
  void pop_front();
  void swap(list& other);
  void copy_from(const list& other);
  void move_from(list&& other) noexcept;
  void merge(list& other);
  void splice(const_iterator pos, list& other);
  void reverse();
  void unique();
  void sort();
};

// ========== МЕТОДЫ ИТЕРАТОРА ============

template <typename T>
typename list<T>::ListIterator& list<T>::ListIterator::operator++() {
  ptr_ = ptr_->next;
  return *this;
}

template <typename T>
typename list<T>::ListIterator& list<T>::ListIterator::operator--() {
  ptr_ = ptr_->prev;
  return *this;
}

template <typename T>
bool list<T>::ListIterator::operator==(const ListIterator& other) const {
  return ptr_ == other.ptr_;
}

template <typename T>
bool list<T>::ListIterator::operator!=(const ListIterator& other) const {
  return ptr_ != other.ptr_;
}

template <typename T>
typename list<T>::ListConstIterator& list<T>::ListConstIterator::operator++() {
  ptr_ = ptr_->next;
  return *this;
}

template <typename T>
typename list<T>::ListConstIterator& list<T>::ListConstIterator::operator--() {
  ptr_ = ptr_->prev;
  return *this;
}

template <typename T>
bool list<T>::ListConstIterator::operator==(
    const ListConstIterator& other) const {
  return ptr_ == other.ptr_;
}

template <typename T>
bool list<T>::ListConstIterator::operator!=(
    const ListConstIterator& other) const {
  return ptr_ != other.ptr_;
}

// =========== КОНЕЦ ============

// =========== КОНСТРУТОРЫ СПИСКА ===========

template <typename T>
list<T>::list() {
  initialize_end_node();
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const& items) : list() {
  for (const auto& item : items) {
    push_back(item);
  }
}

template <typename T>
list<T>::list(const list& other) : list() {
  for (const auto& item : other) {
    push_back(item);
  }
}

template <typename T>
list<T>::list(list&& other) noexcept
    : head_(nullptr), tail_(nullptr), end_node_(nullptr), size_(0) {
  initialize_end_node();
  move_from(std::move(other));
}

template <typename T>
list<T>::list(size_type n) : list() {
  for (size_type i = 0; i < n; ++i) {
    push_back(T());
  }
}

template <typename T>
list<T>::~list() {
  clear();
  delete end_node_;
}

// =========== КОНЕЦ =============

template <typename T>
list<T>& list<T>::operator=(list&& other) noexcept {
  if (this != &other) {
    clear();
    move_from(std::move(other));
  }
  return *this;
}

// =========== МЕТОДЫ ДОСТУПА К ЭЛЕМЕНТАМ КОНЕЙТНЕРА ===========

template <typename T>
typename list<T>::reference list<T>::front() {
  if (empty()) throw std::out_of_range("list is empty");
  return head_->value;
}

template <typename T>
typename list<T>::reference list<T>::back() {
  if (empty()) throw std::out_of_range("list is empty");
  return tail_->value;
}

template <typename T>
typename list<T>::const_reference list<T>::front() const {
  if (empty()) throw std::out_of_range("list is empty");
  return head_->value;
}

template <typename T>
typename list<T>::const_reference list<T>::back() const {
  if (empty()) throw std::out_of_range("list is empty");
  return tail_->value;
}

// =========== КОНЕЦ ===========

// =========== ДОСТУП К ИТЕРАТОРАМ ============

template <typename T>
typename list<T>::iterator list<T>::begin() {
  return iterator(head_ ? head_ : end_node_);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator(end_node_);
}

template <typename T>
typename list<T>::const_iterator list<T>::begin() const {
  return const_iterator(head_ ? head_ : end_node_);
}

template <typename T>
typename list<T>::const_iterator list<T>::end() const {
  return const_iterator(end_node_);
}

// =========== МЕТОДЫ ЕМКОСТИ ===========

template <typename T>
bool list<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename list<T>::size_type list<T>::size() const {
  return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const {
  return static_cast<size_t>(-1) / sizeof(Node);
}

template <typename T>
void list<T>::clear() {
  while (!empty()) {
    pop_front();
  }
}

// =========== КОНЕЦ ===========

// =========== МОДИФИКАТОРЫ ===========

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node* new_node = new Node(value);

  if (empty()) {
    head_ = tail_ = new_node;
    new_node->next = end_node_;
    new_node->prev = end_node_;
    end_node_->next = new_node;
    end_node_->prev = new_node;
  } else if (pos == begin()) {
    new_node->next = head_;
    new_node->prev = end_node_;
    head_->prev = new_node;
    head_ = new_node;
    end_node_->next = head_;
  } else if (pos == end()) {
    new_node->next = end_node_;
    new_node->prev = tail_;
    tail_->next = new_node;
    tail_ = new_node;
    end_node_->prev = tail_;
  } else {
    new_node->next = pos.ptr_;
    new_node->prev = pos.ptr_->prev;
    pos.ptr_->prev->next = new_node;
    pos.ptr_->prev = new_node;
  }

  ++size_;
  return iterator(new_node);
}

template <typename T>
void list<T>::push_back(const_reference value) {
  insert(end(), value);
}

template <typename T>
void list<T>::push_front(const_reference value) {
  insert(begin(), value);
}

template <typename T>
void list<T>::erase(iterator pos) {
  if (pos == end() || empty()) throw std::out_of_range("Invalid position");

  if (pos == begin()) {
    head_ = head_->next;
    if (head_) {
      head_->prev = end_node_;
      end_node_->next = head_;
    } else {
      tail_ = nullptr;
      end_node_->next = end_node_;
      end_node_->prev = end_node_;
    }
  } else if (pos.ptr_ == tail_) {
    tail_ = tail_->prev;
    if (tail_) {
      tail_->next = end_node_;
      end_node_->prev = tail_;
    } else {
      head_ = nullptr;
      end_node_->next = end_node_;
      end_node_->prev = end_node_;
    }
  } else {
    pos.ptr_->prev->next = pos.ptr_->next;
    pos.ptr_->next->prev = pos.ptr_->prev;
  }

  delete pos.ptr_;
  --size_;
}

template <typename T>
void list<T>::pop_back() {
  if (empty()) throw std::out_of_range("list is empty");
  erase(--end());
}

template <typename T>
void list<T>::pop_front() {
  if (empty()) throw std::out_of_range("list is empty");
  erase(begin());
}

template <typename T>
void list<T>::swap(list& other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(end_node_, other.end_node_);
  std::swap(size_, other.size_);
}

template <typename T>
void list<T>::merge(list& other) {
  if (this != &other) {
    iterator it = begin();
    while (!other.empty()) {
      if (it == end() || other.front() <= *it) {
        insert(it, other.front());
        other.pop_front();
      } else {
        ++it;
      }
    }
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list& other) {
  if (this != &other && !other.empty()) {
    for (auto it = other.begin(); it != other.end();) {
      auto next = it;
      ++next;
      insert(pos, *it);
      other.erase(it);
      it = next;
    }
  }
}

template <typename T>
void list<T>::reverse() {
  if (size_ > 1) {
    Node* current = head_;
    while (current != end_node_) {
      std::swap(current->prev, current->next);
      current = current->prev;
    }
    std::swap(head_, tail_);
    end_node_->next = head_;
    head_->prev = end_node_;
    end_node_->prev = tail_;
    tail_->next = end_node_;
  }
}

template <typename T>
void list<T>::unique() {
  if (size_ > 1) {
    iterator curr = begin();
    while (curr != end() && curr.ptr_->next != end_node_) {
      if (*curr == *iterator(curr.ptr_->next)) {
        erase(iterator(curr.ptr_->next));
      } else {
        ++curr;
      }
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (size_ > 1) {
    bool swapped;
    do {
      swapped = false;
      iterator curr = begin();
      while (curr.ptr_->next != end_node_) {
        iterator next = iterator(curr.ptr_->next);
        if (*curr > *next) {
          std::swap(curr.ptr_->value, next.ptr_->value);
          swapped = true;
        }
        curr = next;
      }
    } while (swapped);
  }
}

// ========== КОНЕЦ =========

// ========== ДОП. МЕТОДЫ ===========

template <typename T>
void list<T>::copy_from(const list& other) {
  for (const_iterator it = other.begin(); it != other.end(); ++it) {
    push_back(*it);
  }
}

template <typename T>
void list<T>::move_from(list&& other) noexcept {
  if (other.head_) {
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;

    head_->prev = end_node_;
    tail_->next = end_node_;
    end_node_->next = head_;
    end_node_->prev = tail_;
  }

  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename T>
void list<T>::initialize_end_node() {
  end_node_ = new Node();
  end_node_->next = end_node_;
  end_node_->prev = end_node_;
}

}  // namespace s21

#endif