/*  
Assignment 5 - Implementation of the Stable Nucleus class.
Student Number - 10608637
Created - 31/03/25 
Date - 31/03/25 
*/

// Import basic libraries and headers
#include <iostream>
#include <sstream>
#include "Stable_Nucleus.h"


// Constructors
// Parameterised Constructor
Stable_Nucleus::Stable_Nucleus(std::vector<std::shared_ptr<Particle>>& decay_tree, std::string nucleus_name, 
                               double atomic_mass,
                               double atomic_number,
                               std::string atomic_symbol):
Nucleus(decay_tree, nucleus_name, atomic_mass, atomic_number, atomic_symbol)
{
  // Every time we construct a non_abstract particle of type 'Photon' it gets added to the polymorphic container
  add_to_container(decay_tree);
  // Useful message for debugging and understanding memory
  //std::cout<<"Constructing 'Stable_Nucleus' derived class: "<< m_particle_name <<"\n";
}

// Copy Constructor required... invokes rule of 5
Stable_Nucleus::Stable_Nucleus(const Stable_Nucleus& p):
Nucleus(p.m_decay_tree, p.m_particle_name, p.m_particle_mass, p.m_particle_charge, p.m_atomic_symbol)
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Copying 'Stable_Nucleus' derived class: "<< m_particle_name <<"\n";
}

// Destructor
Stable_Nucleus::~Stable_Nucleus()
{
  // Useful message for debugging and understanding memory  
  //std::cout<<"Destroying 'Stable_Nucleus' derived class: "<< m_particle_name <<"\n";
}

// Move Constructor
Stable_Nucleus::Stable_Nucleus(Stable_Nucleus&& p) noexcept:
Nucleus(p.m_decay_tree, p.m_particle_name, p.m_particle_mass, p.m_particle_charge, p.m_atomic_symbol)
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Moving 'Stable_Nucleus' derived class: "<< m_particle_name <<"\n";
}

// Copy assignment operator
Stable_Nucleus& Stable_Nucleus::operator=(const Stable_Nucleus& p)
{
  if(&p == this)
  {
    return *this;
  }
  m_decay_tree = p.m_decay_tree;
  m_particle_name = p.m_particle_name;
  m_particle_mass = p.m_particle_mass;
  m_particle_charge = p.m_particle_charge;
  m_atomic_symbol = p.m_atomic_symbol;
  // Useful message for debugging and understanding memory
  //std::cout<<"Calling copy assignment for 'Stable_Nucleus' derived class: "<< m_particle_name <<"\n";

  return *this;
}

// Move assignment operator
Stable_Nucleus& Stable_Nucleus::operator=(Stable_Nucleus&& p) noexcept
{
  if(&p == this)
  {
    return *this;
  }
  m_decay_tree = p.m_decay_tree;
  m_particle_name = p.m_particle_name;
  m_particle_mass = p.m_particle_mass;
  m_particle_charge = p.m_particle_charge;
  m_atomic_symbol = p.m_atomic_symbol;
  // Useful message for debugging and understanding memory
  //std::cout<<"Calling move assignment for 'Stable_Nucleus' derived class: "<< m_particle_name <<"\n";

  return *this;
}


// Other functionality
void Stable_Nucleus::print_data() const
{
  std::cout.precision(3);
  std::cout<< "Name: "<< m_particle_name<< "\n";
  std::cout<< "Atomic mass: "<< m_particle_mass*DALTON << " MeV/c^2\n";
  std::cout<< "Atomic number: "<< m_particle_charge << " e\n";
  std::cout<< "Atomic symbol: "<< m_atomic_symbol << "\n\n";
  //std::cout<< "Memory address: "<< this<< "\n\n";
}

// Add to container function allows me to create polymorphic containers which store different types of particle
void Stable_Nucleus::add_to_container(std::vector<std::shared_ptr<Particle>>& container)
{
  container.push_back(std::make_shared<Stable_Nucleus>(*this));
}
