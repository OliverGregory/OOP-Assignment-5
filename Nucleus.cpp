/*  
Assignment 5 - Implementation of the Nucleus class.
Student Number - 10608637
Created - 31/03/25 
Date - 31/03/25 
*/

// Import basic libraries and headers
#include <iostream>
#include <sstream>
#include "Nucleus.h"


// Constructors
// Parameterised Constructor
Nucleus::Nucleus(std::vector<std::shared_ptr<Particle>>& decay_tree, std::string nucleus_name, 
                 double atomic_mass,
                 double atomic_number,
                 std::string atomic_symbol):
Particle(decay_tree, nucleus_name, atomic_mass, atomic_number), m_atomic_symbol{atomic_symbol}
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Constructing 'Nucleus' abstract class: "<< m_particle_name <<"\n";
}

// Copy Constructor required... invokes rule of 5
Nucleus::Nucleus(const Nucleus& p):
Particle(p.m_decay_tree, p.m_particle_name, p.m_particle_mass, p.m_particle_charge), m_atomic_symbol{p.m_atomic_symbol}
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Copying 'Nucleus' abstract class: "<< m_particle_name <<"\n";
}

// Destructor
Nucleus::~Nucleus()
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Destroying 'Nucleus' abstract class: "<< m_particle_name <<"\n";
}

// Move Constructor
Nucleus::Nucleus(Nucleus&& p) noexcept:
Particle(p.m_decay_tree, p.m_particle_name, p.m_particle_mass, p.m_particle_charge), m_atomic_symbol{p.m_atomic_symbol}
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Moving 'Nucleus' abstract class: "<< m_particle_name <<"\n";
}

// Copy assignment operator
Nucleus& Nucleus::operator=(const Nucleus& p)
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
  //std::cout<<"Calling copy assignment for 'Nucleus' abstract class: "<< m_particle_name <<"\n";

  return *this;
}

// Move assignment operator
Nucleus& Nucleus::operator=(Nucleus&& p) noexcept
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
  //std::cout<<"Calling move assignment for 'Nucleus' abstract class: "<< m_particle_name <<"\n";

  return *this;
}
