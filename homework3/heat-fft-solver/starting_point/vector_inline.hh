#include "vector.hh"

inline Real& Vector::operator[](UInt i) { return values[i]; }

inline const Real& Vector::operator[](UInt i) const { return values[i]; }

inline Real Vector::squaredNorm() const {
  Real res = 0;
  for (auto& val : values) {
    res += val * val;
  }
  return res;
}

/* -------------------------------------------------------------------------- */

inline Vector& Vector::operator+=(const Vector& vec) {
  for (UInt i = 0; i < dim; ++i)
    values[i] += vec[i];
  return *this;
}

inline Vector& Vector::operator-=(const Vector& vec) {
  for (UInt i = 0; i < dim; ++i)
    values[i] -= vec[i];
  return *this;
}

inline Vector& Vector::operator*=(Real val) {
  for (auto& v : values)
    v *= val;
  return *this;
}

inline Vector& Vector::operator/=(Real val) {
  for (auto& v : values)
    v /= val;
  return *this;
}

/* -------------------------------------------------------------------------- */

inline Vector& Vector::operator=(const Vector& vec) {
  std::copy(vec.values.begin(), vec.values.end(), values.begin());
  return *this;
}

inline Vector& Vector::operator=(Real val) {
  std::fill(values.begin(), values.end(), val);
  return *this;
}

/* -------------------------------------------------------------------------- */

inline Vector operator+(const Vector& a, const Vector& b) {
  Vector res(a);
  res += b;
  return res;
}

inline Vector operator-(const Vector& a, const Vector& b) {
  Vector res(a);
  res -= b;
  return res;
}

inline Vector operator*(const Vector& a, Real val) {
  Vector res(a);
  res *= val;
  return res;
}

inline Vector operator*(Real val, const Vector& a) { return a * val; }

inline Vector operator/(const Vector& a, Real val) {
  Vector res(a);
  res /= val;
  return res;
}

/* -------------------------------------------------------------------------- */

/// standard output stream operator
inline std::ostream& operator<<(std::ostream& stream, const Vector& _this) {
  for (auto& v : _this.values)
    stream << v << " ";
  return stream;
}

/* -------------------------------------------------------------------------- */
/// standard input stream operator
inline std::istream& operator>>(std::istream& stream, Vector& _this) {
  for (auto& v : _this.values)
    stream >> v;
  return stream;
}
