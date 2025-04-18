/*  
Assignment 5 - Implementation of the Photon class.
Student Number - 10608637
Created - 31/03/25 
Date - 31/03/25 
*/

// Import basic libraries and headers
#include <iostream>
#include <sstream>
#include "Photon.h"

// Constructors
// Parameterised Constructor
Photon::Photon(std::vector<std::shared_ptr<Particle>>& decay_tree, std::string quanta_name,
               double photon_energy):
Quanta(decay_tree, quanta_name, 0, 0, photon_energy)
{
  // Every time we construct a non_abstract particle of type 'Photon' it gets added to the polymorphic container
  add_to_container(decay_tree);
  // Useful message for debugging and understanding memory
  //std::cout<<"Constructing 'Photon' derived class: "<< m_particle_name <<"\n";
}

// Copy Constructor required... invokes rule of 5
Photon::Photon(const Photon& p):
Quanta(p.m_decay_tree, p.m_particle_name, p.m_particle_mass, p.m_particle_charge, p.m_energy)
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Copying 'Photon' derived class: "<< m_particle_name <<"\n";
}

// Destructor
Photon::~Photon()
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Destroying 'Photon' derived class: "<< m_particle_name <<"\n";
}

// Move Constructor
Photon::Photon(Photon&& p) noexcept:
Quanta(p.m_decay_tree, p.m_particle_name, p.m_particle_mass, p.m_particle_charge, p.m_energy)
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Moving 'Photon' derived class: "<< m_particle_name <<"\n";
}

// Copy assignment operator
Photon& Photon::operator=(const Photon& p)
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
  //std::cout<<"Calling copy assignment for 'Photon' derived class: "<< m_particle_name <<"\n";

  return *this;
}

// Move assignment operator
Photon& Photon::operator=(Photon&& p) noexcept
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
  //std::cout<<"Calling move assignment for 'Photon' derived class: "<< m_particle_name <<"\n";

  return *this;
}


// Other functionality
// 
void Photon::print_data() const
{
  std::cout.precision(3);
  std::cout<< "Type of quanta: "<< m_particle_name<< "\n";
  std::cout<< "Rest mass: "<< m_particle_mass << " MeV/c^2\n";
  std::cout<< "Charge: "<< m_particle_charge << " e\n";
  std::cout<< "Photon Energy: "<< m_energy << " MeV\n\n";
  //std::cout<< "Memory address: "<< this<< "\n\n";
}

// Add to container function allows me to create polymorphic containers which store different types of particle
void Photon::add_to_container(std::vector<std::shared_ptr<Particle>>& container)
{
  container.push_back(std::make_shared<Photon>(*this));
}
