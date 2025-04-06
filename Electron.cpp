/*  
Assignment 5 - Implementation of the Electron class.
Student Number - 10608637
Created - 31/03/25 
Date - 31/03/25 
*/

// Import basic libraries and headers
#include <iostream>
#include <sstream>
#include "Electron.h"

// Constructors
// Parameterised Constructor
Electron::Electron(std::vector<std::shared_ptr<Particle>>& decay_tree, std::string quanta_name, 
                   double charge,
                   double electron_energy):
Quanta(decay_tree, quanta_name, ELECTRON_MASS, charge, electron_energy)
{
  // Every time we construct a non_abstract particle of type 'Electron' it gets added to the polymorphic container
  add_to_container(decay_tree);
  // Useful message for debugging and understanding memory
  //std::cout<<"Constructing 'Electron' derived class: "<< m_particle_name <<"\n";
}

// Copy Constructor required... invokes rule of 5
Electron::Electron(const Electron& p):
Quanta(p.m_decay_tree, p.m_particle_name, p.m_particle_mass, p.m_particle_charge, p.m_energy)
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Copying 'Electron' derived class: "<< m_particle_name <<"\n";
}

// Destructor
Electron::~Electron()
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Destroying 'Electron' derived class: "<< m_particle_name <<"\n";
}

// Move Constructor
Electron::Electron(Electron&& p) noexcept:
Quanta(p.m_decay_tree, p.m_particle_name, p.m_particle_mass, p.m_particle_charge, p.m_energy)
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Moving 'Electron' derived class: "<< m_particle_name <<"\n";
}

// Copy assignment operator
Electron& Electron::operator=(const Electron& p)
{
  if(&p == this)
  {
    return *this;
  }
  m_decay_tree = p.m_decay_tree;
  m_particle_name = p.m_particle_name;
  m_particle_mass = p.m_particle_mass;
  m_particle_charge = p.m_particle_charge;
  m_energy = p.m_energy;
  // Useful message for debugging and understanding memory
  //std::cout<<"Calling copy assignment for 'Electron' derived class: "<< m_particle_name <<"\n";

  return *this;
}

// Move assignment operator
Electron& Electron::operator=(Electron&& p) noexcept
{
  if(&p == this)
  {
    return *this;
  }
  m_decay_tree = p.m_decay_tree;
  m_particle_name = p.m_particle_name;
  m_particle_mass = p.m_particle_mass;
  m_particle_charge = p.m_particle_charge;
  m_energy = p.m_energy;
  // Useful message for debugging and understanding memory
  //std::cout<<"Calling move assignment for 'Electron' derived class: "<< m_particle_name <<"\n";

  return *this;
}


// Other functionality
// 
void Electron::print_data() const
{
  std::cout.precision(3);
  std::cout<< "Type of quanta: "<< m_particle_name<< "\n";
  std::cout<< "Rest mass: "<< m_particle_mass << " MeV/c^2\n";
  std::cout<< "Charge: "<< m_particle_charge << " e\n";
  std::cout<< "Electron Energy: "<< m_energy << " MeV\n\n";
  //std::cout<< "Memory address: "<< this<< "\n\n";
}

// Add to container function allows me to create polymorphic containers which store different types of particle
void Electron::add_to_container(std::vector<std::shared_ptr<Particle>>& container)
{
  container.push_back(std::make_shared<Electron>(*this));
}
