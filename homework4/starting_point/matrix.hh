#ifndef MATRIX_HH
#define MATRIX_HH
/* ------------------------------------------------------ */
#include "my_types.hh"
#include <Eigen/Dense>
#include <algorithm>
#include <array>
#include <tuple>
#include <vector>
/* ------------------------------------------------------ */

template <typename T>
class SquareMatrix
    : public Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor> {
  using parent =
      Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor>;

public:
  SquareMatrix(std::size_t size) : parent(size, size) {}
  SquareMatrix(const SquareMatrix& other) : parent(other) {}

public:
  std::size_t size() { return this->rows(); }
};

template <typename T>
using Matrix = SquareMatrix<T>;

/* ------------------------------------------------------ */

template <typename T>
struct MatrixIndexIterator : public Matrix<T>::template CustomIterator<T> {
  MatrixIndexIterator(UInt index, UInt size, T* ptr)
      : Matrix<T>::template CustomIterator<T>(index, ptr), size(size) {}

  std::tuple<UInt, UInt, T&> operator*() {
    UInt i = this->index % this->size;
    UInt j = this->index / this->size;
    return std::tuple<UInt, UInt, T&>(i, j, this->ptr[this->index]);
  }

  std::size_t size;
};

/* ------------------------------------------------------ */
template <typename T>
struct IndexedMatrix {

  IndexedMatrix(Matrix<T>& mat) : mat(mat){};

  MatrixIndexIterator<T> begin() {
    return MatrixIndexIterator<T>(0, mat.size(), mat.data());
  };

  MatrixIndexIterator<T> end() {
    return MatrixIndexIterator<T>(mat.size() * mat.size(), mat.size(),
                                  mat.data());
  };

private:
  Matrix<T>& mat;
};
/* ------------------------------------------------------ */

template <typename T>
IndexedMatrix<T> index(Matrix<T>& mat) {
  return IndexedMatrix<T>(mat);
}
/* ------------------------------------------------------ */

#endif  // MATRIX
