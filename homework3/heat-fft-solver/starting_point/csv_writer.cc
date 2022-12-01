#include "csv_writer.hh"
#include <cstdlib>
#include <fstream>
/* -------------------------------------------------------------------------- */
CsvWriter::CsvWriter(const std::string& filename) : filename(filename) {}

/* -------------------------------------------------------------------------- */
void CsvWriter::write(System& system) { this->compute(system); }

/* -------------------------------------------------------------------------- */

void CsvWriter::compute(System& system) {

  std::ofstream os(filename.c_str());

  if (os.is_open() == false) {
    std::cerr << "cannot open file " << filename << std::endl
              << "check that the dumps folder exists" << std::endl;
    std::exit(1);
  }

  UInt nb_particles = system.getNbParticles();

  for (UInt p = 0; p < nb_particles; ++p) {
    os << system.getParticle(p) << std::endl;
  }

  os.close();

}
