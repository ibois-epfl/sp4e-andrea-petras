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

  template <int Direction>
  static Matrix<complex> generic_transform(Matrix<complex>& m);
};

/* ------------------------------------------------------ */

inline Matrix<complex> FFT::transform(Matrix<complex>& m_in) {
  return FFT::generic_transform<FFTW_FORWARD>(m_in);
}

/* ------------------------------------------------------ */

inline Matrix<complex> FFT::itransform(Matrix<complex>& m_in) {
  auto&& m_out = FFT::generic_transform<FFTW_BACKWARD>(m_in);
  auto size = m_in.size();
  m_out /= size * size;
  return m_out;
}

/* ------------------------------------------------------ */

template <int Direction>
inline Matrix<complex> FFT::generic_transform(Matrix<complex>& m_in) {

  auto size = m_in.size();
  if (size == 0)
    throw std::runtime_error("empty matrix: cannot perform DFT");

  Matrix<complex> m_out(size);
  auto in = (fftw_complex*)m_in.data();
  auto out = (fftw_complex*)m_out.data();
  auto p = fftw_plan_dft_2d(size, size, in, out, Direction, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);
  return m_out;
}

/* ------------------------------------------------------ */

inline Matrix<std::complex<int>> FFT::computeFrequencies(int size) {

  using T = std::complex<int>;
  Matrix<std::complex<int>> freqs(size);
  constexpr UInt dmax = 2;

  for (auto entry : index(freqs)) {

    auto i = std::get<0>(entry);
    auto j = std::get<1>(entry);
    auto& freq = std::get<2>(entry);
    std::array<int, 2> wavevector;
    std::array<int, 2> tuple{int(i), int(j)};

    for (UInt d = 0; d < dmax; d++) {
      // Type conversion
      int td = tuple[d];
      int nd = size;
      int q = (tuple[d] < size / 2) ? td : td - nd;
      wavevector[d] = q;
    }
    freq = std::complex<int>{wavevector[0], wavevector[1]};
  }

  return freqs;
}

#endif  // FFT_HH
