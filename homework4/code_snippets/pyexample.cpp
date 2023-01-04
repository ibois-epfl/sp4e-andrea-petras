#include <exception>
#include <iostream>
#include <memory>
#include <vector>

/* ------------------------------------------ */
// simple function
/* ------------------------------------------ */
int add(int i, int j) { return i + j; }

/* ------------------------------------------ */
// simple function with default arguments
/* ------------------------------------------ */
int add_with_defaults(int i = 1, int j = 2) { return i + j; }

/* ------------------------------------------ */
// global variables
/* ------------------------------------------ */
std::string yopla = "yopla";
int global_variable = 12;

/* ------------------------------------------ */
// class
/* ------------------------------------------ */
struct Animal {
  Animal(const std::string &name) : name(name){};
  virtual void scream() { std::cout << name << ": AAAAAA" << std::endl; }
  std::string name;

  void setName(const std::string &name) { this->name = name; }
  std::string getName() { return this->name; }
};

/* ------------------------------------------ */

struct Dog : Animal {
  Dog(const std::string &name) : Animal(name) {}
  void scream() override { std::cout << "ouaff" << std::endl; }
  bool hasNiche() { return true; }

  void overloadedFoo(int a){};
  void overloadedFoo(const std::string a) const {};
};
/* ------------------------------------------ */
enum ParticleType { atom, planet, pingpongball, material };
/* ------------------------------------------ */

/* ------------------------------------------ */
// function fabricating objects
/* ------------------------------------------ */

auto makeAnimalUnique() {
  // create unique ptr
  return std::make_unique<Dog>("puppy");
}

/* ------------------------------------------ */
// memory management
/* ------------------------------------------ */

Animal *animal_data = new Animal("toto");
Animal *get_animal() { return animal_data; }

struct AnimalShared {
  std::string name;
};

std::shared_ptr<AnimalShared> get_shared_ptr() {
  return std::make_shared<AnimalShared>();
}

std::vector<std::shared_ptr<AnimalShared>> vec_animal_shared;
void register_animal_shared(std::shared_ptr<AnimalShared> ptr) {
  vec_animal_shared.push_back(ptr);
};

template <typename Func> void apply(Func F) {
  std::vector<double> v{1., 2., 3., 4.};
  for (auto &val : v)
    F(val);
}

void _raise() { throw std::runtime_error("toto"); }

#include "pyexample_pybind.cpp"
