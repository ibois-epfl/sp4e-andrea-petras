#ifndef __VECTOR__HH__
#define __VECTOR__HH__

/* -------------------------------------------------------------------------- */
#include "my_types.hh"
/* -------------------------------------------------------------------------- */
#include <array>

/**
 * @brief 3D Vector class
 *
 * Note that no constructor is needed for this class
 */
class Vector {
public:
  //! Dimension of vector
  static const UInt dim = 3;

  // Methods
public:
  //! access given component
  Real& operator[](UInt i);
  //! access given component (const)
  const Real& operator[](UInt i) const;
  //! square of euclidian norm
  Real squaredNorm() const;

  // Operators that make sense for vectors
  Vector& operator+=(const Vector& vec);
  Vector& operator-=(const Vector& vec);
  Vector& operator*=(Real val);
  Vector& operator/=(Real val);

  //! Copy operator
  Vector& operator=(const Vector& vec);
  //! Assign a value
  Vector& operator=(Real val);

public:
  //! Output to stream
  friend std::ostream& operator<<(std::ostream& stream, const Vector& _this);
  //! Initialize from stream
  friend std::istream& operator>>(std::istream& stream, Vector& _this);

private:
  //! Vector values (initilized to zero by default)
  std::array<Real, dim> values = {0};
};

/* -------------------------------------------------------------------------- */
/* Separate function definitions */
/* -------------------------------------------------------------------------- */

/// standard output stream operator
std::ostream& operator<<(std::ostream& stream, const Vector& _this);
/// standard input stream operator
std::istream& operator>>(std::istream& stream, Vector& _this);

// We define the operators +, -, *, / with vectors and scalars
Vector operator+(const Vector& a, const Vector& b);
Vector operator-(const Vector& a, const Vector& b);

// Symmetry of multiplication
Vector operator*(const Vector& a, Real val);
Vector operator*(Real val, const Vector& a);

// For convenience
Vector operator/(const Vector& a, Real val);

// Include inline implementation
#include "vector_inline.hh"

#endif  //__VECTOR__HH__
