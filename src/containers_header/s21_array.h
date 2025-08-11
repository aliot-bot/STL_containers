#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <cstddef>
#include <stdexcept>
#include <initializer_list>
#include <utility>

namespace s21 {

template <typename T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  array();
  array(std::initializer_list<value_type> const& items);
  array(const array& a);
  array(array&& a) noexcept;
  ~array();
  array& operator=(array&& a) noexcept;

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  iterator data() noexcept;

  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void swap(array& other) noexcept;
  void fill(const_reference value);

 private:
  T elements_[N];
};

template <typename T, size_t N>
array<T, N>::array() {
  for (size_type i = 0; i < N; ++i) {
    elements_[i] = T();
  }
}

template <typename T, size_t N>
array<T, N>::array(std::initializer_list<value_type> const& items) {
  if (items.size() > N) {
    throw std::out_of_range("Initializer list size exceeds array capacity");
  }
  size_type i = 0;
  for (const auto& item : items) {
    elements_[i++] = item;
  }
  for (; i < N; ++i) {
    elements_[i] = T();
  }
}

template <typename T, size_t N>
array<T, N>::array(const array& a) {
  for (size_type i = 0; i < N; ++i) {
    elements_[i] = a.elements_[i];
  }
}

template <typename T, size_t N>
array<T, N>::array(array&& a) noexcept {
  for (size_type i = 0; i < N; ++i) {
    elements_[i] = std::move(a.elements_[i]);
  }
}

template <typename T, size_t N>
array<T, N>::~array() {}

template <typename T, size_t N>
array<T, N>& array<T, N>::operator=(array&& a) noexcept {
  for (size_type i = 0; i < N; ++i) {
    elements_[i] = std::move(a.elements_[i]);
  }
  return *this;
}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("Index out of range");
  }
  return elements_[pos];
}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return elements_[pos];
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
  return elements_[0];
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  return elements_[N - 1];
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::data() noexcept {
  return elements_;
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::begin() noexcept {
  return elements_;
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::end() noexcept {
  return elements_ + N;
}

template <typename T, size_t N>
typename array<T, N>::const_iterator array<T, N>::begin() const noexcept {
  return elements_;
}

template <typename T, size_t N>
typename array<T, N>::const_iterator array<T, N>::end() const noexcept {
  return elements_ + N;
}

template <typename T, size_t N>
bool array<T, N>::empty() const noexcept {
  return N == 0;
}

template <typename T, size_t N>
typename array<T, N>::size_type array<T, N>::size() const noexcept {
  return N;
}

template <typename T, size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const noexcept {
  return N;
}

template <typename T, size_t N>
void array<T, N>::swap(array& other) noexcept {
  for (size_type i = 0; i < N; ++i) {
    std::swap(elements_[i], other.elements_[i]);
  }
}

template <typename T, size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < N; ++i) {
    elements_[i] = value;
  }
}

}  // namespace s21
#endif