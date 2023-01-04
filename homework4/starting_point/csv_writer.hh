#ifndef __CSV_WRITER__HH__
#define __CSV_WRITER__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"
#include <string>

//! Write system state to csv file
class CsvWriter : public Compute {
  // Constructors/Destructors
public:
  //! Construct from filename
  CsvWriter(const std::string& filename);

  // Methods
public:
  //! Write file (calls compute)
  void write(System& system);
  //! Write file
  void compute(System& system);

protected:
  std::string filename;
};

/* -------------------------------------------------------------------------- */
#endif  //__CSV_WRITER__HH__
