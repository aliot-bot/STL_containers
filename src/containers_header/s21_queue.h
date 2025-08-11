#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include "s21_list.h"

namespace s21 {
template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  queue();
  queue(std::initializer_list<value_type> const& items);
  queue(const queue& other);
  queue(queue&& other) noexcept;
  ~queue();
  queue& operator=(queue&& other);

  // Методы доступа
  const_reference front() const;
  const_reference back() const;

  // Методы емкости
  bool empty() const;
  size_type size() const;

  // Модификаторы
  void push(const_reference value);
  void pop();
  void swap(queue& other);

 private:
  s21::list<value_type> data_;
};

template <typename T>
queue<T>::queue() = default;

template <typename T>
queue<T>::queue(std::initializer_list<value_type> const& items) : data_() {
  for (const auto& item : items) {
    data_.push_back(item);
  }
}

template <typename T>
queue<T>::queue(const queue& other) : data_(other.data_) {}

template <typename T>
queue<T>::queue(queue&& other) noexcept : data_(std::move(other.data_)) {}

template <typename T>
queue<T>::~queue() = default;

template <typename T>
typename queue<T>::queue& queue<T>::operator=(queue&& other) {
  if (this != &other) {
    data_ = std::move(other.data_);
  }
  return *this;
}

template <typename T>
typename queue<T>::const_reference queue<T>::front() const {
  if (empty()) throw std::out_of_range("Queue is empty");
  return data_.front();
}

template <typename T>
typename queue<T>::const_reference queue<T>::back() const {
  if (empty()) throw std::out_of_range("Queue is empty");
  return data_.back();
}

template <typename T>
bool queue<T>::empty() const {
  return data_.empty();
}

template <typename T>
typename queue<T>::size_type queue<T>::size() const {
  return data_.size();
}

template <typename T>
void queue<T>::push(const_reference value) {
  data_.push_back(value);
}

template <typename T>
void queue<T>::pop() {
  if (empty()) throw std::out_of_range("Queue is empty");
  data_.pop_front();
}

template <typename T>
void queue<T>::swap(queue& other) {
  data_.swap(other.data_);
}

}  // namespace s21
#endif