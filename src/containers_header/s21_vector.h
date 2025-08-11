#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <stdexcept>
#include <utility>

namespace s21 {

template <typename T>
class vector {
 private:
  T* data_;
  size_t size_;
  size_t capacity_;

  void reallocate(size_t new_capacity);

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  class VectorIterator {
   private:
    T* ptr_;

   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    VectorIterator();
    explicit VectorIterator(T* ptr);

    reference operator*();
    VectorIterator& operator++();
    VectorIterator operator++(int);
    VectorIterator& operator--();
    VectorIterator operator--(int);
    bool operator==(const VectorIterator& other) const;
    bool operator!=(const VectorIterator& other) const;

    T* get_ptr() const;
  };

  class VectorConstIterator {
   private:
    T* ptr_;

   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    VectorConstIterator();
    explicit VectorConstIterator(const T* ptr);

    reference operator*() const;
    VectorConstIterator& operator++();
    VectorConstIterator operator++(int);
    VectorConstIterator& operator--();
    VectorConstIterator operator--(int);
    bool operator==(const VectorConstIterator& other) const;
    bool operator!=(const VectorConstIterator& other) const;
  };

  using iterator = VectorIterator;
  using const_iterator = VectorConstIterator;

  // конструткоры
  vector();
  explicit vector(size_type n);
  vector(std::initializer_list<value_type> const& items);
  vector(const vector& other);
  vector(vector&& other) noexcept;
  ~vector();

  vector& operator=(vector&& other) noexcept;

  // Доступ к элементам
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  T* data();

  // Итераторы
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  // Методы емкости
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();

  // Модификаторы
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other);
};

// ========= МЕТОДЫ ИТЕРАТОРОВ =========

template <typename T>
vector<T>::VectorIterator::VectorIterator() : ptr_(nullptr) {}

template <typename T>
vector<T>::VectorIterator::VectorIterator(T* ptr) : ptr_(ptr) {}

template <typename T>
typename vector<T>::VectorIterator::reference
vector<T>::VectorIterator::operator*() {
  return *ptr_;
}

template <typename T>
typename vector<T>::VectorIterator& vector<T>::VectorIterator::operator++() {
  ++ptr_;
  return *this;
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator++(int) {
  VectorIterator temp = *this;
  ++ptr_;
  return temp;
}

template <typename T>
typename vector<T>::VectorIterator& vector<T>::VectorIterator::operator--() {
  --ptr_;
  return *this;
}

template <typename T>
typename vector<T>::VectorIterator vector<T>::VectorIterator::operator--(int) {
  VectorIterator temp = *this;
  --ptr_;
  return temp;
}

template <typename T>
bool vector<T>::VectorIterator::operator==(const VectorIterator& other) const {
  return ptr_ == other.ptr_;
}

template <typename T>
bool vector<T>::VectorIterator::operator!=(const VectorIterator& other) const {
  return ptr_ != other.ptr_;
}

template <typename T>
T* vector<T>::VectorIterator::get_ptr() const {
  return ptr_;
}

template <typename T>
vector<T>::VectorConstIterator::VectorConstIterator() : ptr_(nullptr) {}

template <typename T>
vector<T>::VectorConstIterator::VectorConstIterator(const T* ptr) : ptr_(ptr) {}

template <typename T>
typename vector<T>::VectorConstIterator::reference
vector<T>::VectorConstIterator::operator*() const {
  return *ptr_;
}

template <typename T>
typename vector<T>::VectorConstIterator&
vector<T>::VectorConstIterator::operator++() {
  ++ptr_;
  return *this;
}

template <typename T>
typename vector<T>::VectorConstIterator
vector<T>::VectorConstIterator::operator++(int) {
  VectorConstIterator temp = *this;
  ++ptr_;
  return temp;
}

template <typename T>
typename vector<T>::VectorConstIterator&
vector<T>::VectorConstIterator::operator--() {
  --ptr_;
  return *this;
}

template <typename T>
typename vector<T>::VectorConstIterator
vector<T>::VectorConstIterator::operator--(int) {
  VectorConstIterator temp = *this;
  --ptr_;
  return temp;
}

template <typename T>
bool vector<T>::VectorConstIterator::operator==(
    const VectorConstIterator& other) const {
  return ptr_ == other.ptr_;
}

template <typename T>
bool vector<T>::VectorConstIterator::operator!=(
    const VectorConstIterator& other) const {
  return ptr_ != other.ptr_;
}

// ========= КОНЕЦ =========

// ========= КОНСТРУТОРЫ =========

template <typename T>
vector<T>::vector() : data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
vector<T>::vector(size_type n) : size_(n), capacity_(n) {
  try {
    data_ = new T[n]();
  } catch (const std::bad_alloc& e) {
    throw;
  }
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const& items)
    : size_(items.size()), capacity_(items.size()) {
  try {
    data_ = new T[capacity_]();
    size_t i = 0;
    for (const auto& item : items) {
      data_[i++] = item;
    }
  } catch (const std::bad_alloc& e) {
    delete[] data_;
    throw;
  }
}

template <typename T>
vector<T>::vector(const vector& other)
    : size_(other.size_), capacity_(other.capacity_) {
  try {
    data_ = new T[capacity_]();
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = other.data_[i];
    }
  } catch (const std::bad_alloc& e) {
    delete[] data_;
    throw;
  }
}

template <typename T>
vector<T>::vector(vector&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
  other.data_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

template <typename T>
vector<T>::~vector() {
  delete[] data_;
}

template <typename T>
vector<T>& vector<T>::operator=(vector&& other) noexcept {
  if (this != &other) {
    delete[] data_;
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }
  return *this;
}

// ======== КОНЕЦ ========

// ======== МЕТОДЫ ДОСТУПА К ЭЛЕМЕНТАМ =========

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return data_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  if (size_ == 0) {
    throw std::out_of_range("Vector is empty");
  }
  return data_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  if (size_ == 0) {
    throw std::out_of_range("Vector is empty");
  }
  return data_[size_ - 1];
}

template <typename T>
T* vector<T>::data() {
  return data_;
}

// ======== КОНЕЦ ========

// ======== МЕТОДЫ ДОСТУПА К ИТЕРАТОРАМ ========

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return iterator(data_);
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return iterator(data_ + size_);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::begin() const {
  return const_iterator(data_);
}

template <typename T>
typename vector<T>::const_iterator vector<T>::end() const {
  return const_iterator(data_ + size_);
}

// ======== КОНЕЦ ========

// ======== МЕТОДЫ ЕМКОСТИ ========

template <typename T>
bool vector<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  return (size_t)(-1) / sizeof(T);
}

// ======== КОНЕЦ ========

// ======== МОДИФИКАТОРЫ =========

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size > capacity_) {
    size_t new_capacity =
        (capacity_ == 0) ? (size > 0 ? size : 1) : capacity_ * 2;
    if (new_capacity < size) new_capacity = size;
    reallocate(new_capacity);
  }
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    reallocate(size_);
  }
}

template <typename T>
void vector<T>::clear() {
  size_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_t pos_index = pos.get_ptr() - data_;
  if (pos_index > size_) {
    throw std::out_of_range("Invalid iterator position");
  }
  if (size_ == capacity_) {
    size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
    reallocate(new_capacity);
    pos = iterator(data_ + pos_index);
  }
  for (size_t i = size_; i > pos_index; --i) {
    data_[i] = std::move(data_[i - 1]);
  }
  data_[pos_index] = value;
  ++size_;
  return iterator(data_ + pos_index);
}

template <typename T>
void vector<T>::erase(iterator pos) {
  size_t pos_index = pos.get_ptr() - data_;
  if (pos_index >= size_) {
    throw std::out_of_range("Invalid iterator position");
  }
  for (size_t i = pos_index; i < size_ - 1; ++i) {
    data_[i] = std::move(data_[i + 1]);
  }
  --size_;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (size_ == capacity_ || capacity_ == 0) {
    size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
    if (new_capacity <= size_) new_capacity = size_ + 1;
    reserve(new_capacity);
  }
  data_[size_++] = value;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ == 0) {
    throw std::out_of_range("Vector is empty");
  }
  --size_;
}

template <typename T>
void vector<T>::swap(vector& other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

// ======== КОНЕЦ ========

// ======== ДОП. ФУНКЦИИ ========

template <typename T>
void vector<T>::reallocate(size_t new_capacity) {
  T* new_data = new T[new_capacity]();
  for (size_t i = 0; i < size_; ++i) {
    new_data[i] = std::move(data_[i]);
  }
  delete[] data_;
  data_ = new_data;
  capacity_ = new_capacity;
}

// ======== КОНЕЦ ========

}  // namespace s21

#endif