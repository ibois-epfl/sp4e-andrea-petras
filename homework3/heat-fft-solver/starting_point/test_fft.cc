#include "fft.hh"
#include "my_types.hh"
#include <gtest/gtest.h>

/*****************************************************************/
TEST(FFT, transform)
{
  UInt N = 512;
  Matrix<complex> m(N);

  Real k = 2 * M_PI / N;
  for (auto&& entry : index(m))
  {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    val = cos(k * i);
  }

  Matrix<complex> res = FFT::transform(m);

  for (auto&& entry : index(res))
  {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    // if (std::abs(val) > 1e-10)
    //   std::cout << i << "," << j << " = " << val << std::endl;

    if (i == 1 && j == 0)
      ASSERT_NEAR(std::abs(val), N * N / 2, 1e-10);
    else if (i == N - 1 && j == 0)
      ASSERT_NEAR(std::abs(val), N * N / 2, 1e-10);
    else
      ASSERT_NEAR(std::abs(val), 0, 1e-10);
  }
}
/*****************************************************************/

TEST(FFT, inverse_transform)
{
  UInt N = 512;
  Matrix<complex> m(N);
  Real k = 2 * M_PI / N;

  for (auto&& entry : index(m))
  {
      int i = std::get<0>(entry);
      int j = std::get<1>(entry);
      complex& val = std::get<2>(entry);

      if (i == 0 && j == N - 1 || i == 0 && j == 1 ) val = N*N/2;
      else val = 0.0;
  }

  Matrix<complex> res = FFT::itransform(m);

  for (auto&& entry : index(res)) {
      int i = std::get<0>(entry);
      int j = std::get<1>(entry);
      complex& val = std::get<2>(entry);

      ASSERT_NEAR(val.real(), cos(k * j), 1e-10);
  }
}
/*****************************************************************/
TEST(FFT, frequencies)
{
  UInt N = 512;
  Matrix<std::complex<int>> m(N);

  // implement the numpy.fft.fftfreq function
  // https://docs.scipy.org/doc/numpy/reference/generated/numpy.fft.fftfreq.html
  std::vector<int> freqs;
  if (N % 2 == 0)
  {
      for (int i = 0; i < N; i++)
      {
          if (i <= N / 2)
              freqs.push_back(i);
          else
              freqs.push_back(i - N);
      }
  }
  else
  {
      for (int i = 0; i < N; i++)
      {
          if (i <= N / 2)
              freqs.push_back(i);
          else
              freqs.push_back(i - N);
      }
  }

  Matrix<std::complex<int>> res = FFT::computeFrequencies(N);

  for (auto&& entry : index(res))
  {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);

    ASSERT_NEAR(val.real(), freqs[i], 1e-10);
    ASSERT_NEAR(val.imag(), freqs[j], 1e-10);
  }
}