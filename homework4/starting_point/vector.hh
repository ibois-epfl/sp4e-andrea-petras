#ifndef __VECTOR__HH__
#define __VECTOR__HH__

/* -------------------------------------------------------------------------- */
#include "my_types.hh"
#include <Eigen/Dense>
/* -------------------------------------------------------------------------- */

/// Alias type to Eigen 3D vector
using Vector = Eigen::Vector3d;

/// standard output stream operator
inline std::ostream& operator<<(std::ostream& stream, const Vector& _this) {
  for (auto&& v : _this)
    stream << v << " ";
  return stream;
}

/* -------------------------------------------------------------------------- */
/// standard input stream operator
inline std::istream& operator>>(std::istream& stream, Vector& _this) {
  for (auto&& v : _this)
    stream >> v;
  return stream;
}

#endif  //__VECTOR__HH__
