template <typename T>
struct CustomIterator {
  using value_type = T;

  CustomIterator(std::size_t index, T* ptr) : index(index), ptr(ptr){};

  T& operator*() { return ptr[index]; };

  void operator++() { index++; };

  bool operator!=(CustomIterator& other) { return this->index != other.index; };

  std::size_t index;
  T* ptr;
};

CustomIterator<Scalar> begin() {
  return CustomIterator<Scalar>(0, this->data());
};

CustomIterator<Scalar> end() {
  return CustomIterator<Scalar>(this->size(), this->data());
};

CustomIterator<const Scalar> begin() const {
  return CustomIterator<const Scalar>(0, this->data());
};

CustomIterator<const Scalar> end() const {
  return CustomIterator<const Scalar>(this->size(), this->data());
};
