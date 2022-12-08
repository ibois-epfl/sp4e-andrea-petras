#ifndef FFT_HH
#define FFT_HH
/* ------------------------------------------------------ */
#include "matrix.hh"
#include "my_types.hh"
#include <fftw3.h>
/* ------------------------------------------------------ */

struct FFT {

  static Matrix<complex> transform(Matrix<complex>& m);
  static Matrix<complex> itransform(Matrix<complex>& m);

  static Matrix<std::complex<int>> computeFrequencies(int size);
};

/* ------------------------------------------------------ */

inline Matrix<complex> FFT::transform(Matrix<complex>& m_in)
{
  Matrix<complex> m_out(m_in.size());
  fftw_plan plan = fftw_plan_dft_2d(m_in.size(), m_in.size(), (fftw_complex*)m_in.data(), (fftw_complex*)m_out.data(), FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(plan);
  fftw_destroy_plan(plan);
  return m_out;
}

/* ------------------------------------------------------ */

inline Matrix<complex> FFT::itransform(Matrix<complex>& m_in)
{
  Matrix<complex> m_out(m_in.size());
  fftw_plan plan = fftw_plan_dft_2d(m_in.size(), m_in.size(), (fftw_complex*)m_in.data(), (fftw_complex*)m_out.data(), FFTW_BACKWARD, FFTW_ESTIMATE);
  fftw_execute(plan);
  fftw_destroy_plan(plan);
  m_out /= m_in.size() * m_in.size();
  return m_out;
}

/* ------------------------------------------------------ */

inline Matrix<std::complex<int>> FFT::computeFrequencies(int size) {}

#endif  // FFT_HH
