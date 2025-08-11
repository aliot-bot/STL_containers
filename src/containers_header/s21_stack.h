#ifndef S21_STACK_H
#define S21_STACK_H

#include "s21_list.h"

namespace s21 {
template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  stack();
  stack(std::initializer_list<value_type> const& items);
  stack(const stack& other);
  stack(stack&& other) noexcept;
  ~stack();
  stack& operator=(stack&& other);

  // Методы емкости
  bool empty() const;
  size_type size() const;

  // Методы для доступа к элементам класса
  const_reference top() const;

  // Модификаторы
  void push(const_reference value);
  void pop();
  void swap(stack& other);

 private:
  s21::list<value_type> data_;
};

template <typename T>
stack<T>::stack() = default;

template <typename T>
stack<T>::stack(std::initializer_list<value_type> const& items)
    : data_(items) {}

template <typename T>
stack<T>::stack(const stack& other) : data_(other.data_) {}

template <typename T>
stack<T>::stack(stack&& other) noexcept : data_(std::move(other.data_)) {}

template <typename T>
stack<T>::~stack() = default;

template <typename T>
typename stack<T>::stack& stack<T>::operator=(stack&& other) {
  if (this != &other) {
    data_ = std::move(other.data_);
  }
  return *this;
}

template <typename T>
bool stack<T>::empty() const {
  return data_.empty();
}

template <typename T>
typename stack<T>::size_type stack<T>::size() const {
  return data_.size();
}

template <typename T>
typename stack<T>::const_reference stack<T>::top() const {
  if (empty()) throw std::out_of_range("Stack is empty");
  return data_.back();
}

template <typename T>
void stack<T>::push(const_reference value) {
  data_.push_back(value);
}

template <typename T>
void stack<T>::pop() {
  if (empty()) throw std::out_of_range("Stack is empty");
  data_.pop_back();
}

template <typename T>
void stack<T>::swap(stack& other) {
  data_.swap(other.data_);
}
}  // namespace s21
#endif