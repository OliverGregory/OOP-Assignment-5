/*  
Assignment 5 -Stable Nucleus header file. All basic functionality which only requires one line is included.
Student Number - 10608637
Created - 31/03/25 
Date - 31/03/25 
*/

// Header guards
#ifndef STABLE_NUCLEUS_H
#define STABLE_NUCLEUS_H

// Import basic libraries and headers
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Nucleus.h"

// Beginning of Stable_Nucleus class
class Stable_Nucleus : public Nucleus
{
public:
// Constructors 
  // Deafult Constructor
  Stable_Nucleus()= default;
  // Parameterised Constructor
  Stable_Nucleus(std::vector<std::shared_ptr<Particle>>& m_decay_tree, std::string nucleus_name,
                 double atomic_mass,
                 double atomic_number,
                 std::string atomic_symbol);
  // Copy Constructor
  Stable_Nucleus(const Stable_Nucleus& p);
  // Destructor
  ~Stable_Nucleus();
  // Move Constructor
  Stable_Nucleus(Stable_Nucleus&& p) noexcept;
  // Copy assignment operator
  Stable_Nucleus& operator=(const Stable_Nucleus& p);
  // Move assignment operator
  Stable_Nucleus& operator=(Stable_Nucleus&& p) noexcept;

// No Additional member data so no setters or getters  

// All other functionality  
  // Print function
  void print_data() const override;
  // Add to container function allows me to create polymorphic containers which store different types of particle
  void add_to_container(std::vector<std::shared_ptr<Particle>>& container) override;

private:
// Member variables
  // Inherited member data commented out
  /*
  std::string m_particle_name;
  double m_particle_mass;
  double m_particle_charge;
  std::string m_atomic_symbol;
  */
  // Un-inherited member data

};

#endif // STABLE_NUCLEUS_H