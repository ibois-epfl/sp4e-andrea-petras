#ifndef __CSV_READER__HH__
#define __CSV_READER__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"
#include <string>

//! Read system from csv input file
class CsvReader : public Compute {

  /* ------------------------------------------------------------------------ */
  /* Constructors/Destructors                                                 */
  /* ------------------------------------------------------------------------ */
public:
  //! Construct from filename
  CsvReader(const std::string& filename);

  /* ------------------------------------------------------------------------ */
  /* Methods                                                                  */
  /* ------------------------------------------------------------------------ */
public:
  //! Left here for convenience (calls compute)
  void read(System& system);
  //! Read input file into system
  void compute(System& system);

protected:
  std::string filename;
};

/* -------------------------------------------------------------------------- */
#endif  //__CSV_READER__HH__
