#include "csv_reader.hh"
#include "particles_factory_interface.hh"
#include <fstream>
#include <sstream>
/* -------------------------------------------------------------------------- */
CsvReader::CsvReader(const std::string& filename) : filename(filename) {}
/* -------------------------------------------------------------------------- */
void CsvReader::read(System& system) { this->compute(system); }
/* -------------------------------------------------------------------------- */

void CsvReader::compute(System& system) {

  std::ifstream is(filename.c_str());
  std::string line;

  if (is.is_open() == false) {
    std::cerr << "cannot open file " << filename << std::endl;
    throw;
  }

  while (is.good()) {
    getline(is, line);

    if (line[0] == '#' || line.size() == 0)
      continue;

    auto p = ParticlesFactoryInterface::getInstance().createParticle();
    std::stringstream sstr(line);
    sstr >> *p;
    system.addParticle(std::move(p));
  }

  is.close();
}

/* -------------------------------------------------------------------------- */
