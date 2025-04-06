/*  
Assignment 5 - Implementation of the Quanta class.
Student Number - 10608637
Created - 31/03/25 
Date - 31/03/25 
*/

// Import basic libraries and headers
#include "Quanta.h"
#include <iostream>
#include <sstream>


// Constructors
// Parameterised Constructor
Quanta::Quanta(std::vector<std::shared_ptr<Particle>>& decay_tree, std::string quanta_name, 
               double rest_mass,
               double charge,
               double energy):
Particle(decay_tree, quanta_name, rest_mass, charge), m_energy{energy}
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Constructing 'Quanta' abstract class: "<< m_particle_name <<"\n";
}

// Copy Constructor required... invokes rule of 5
Quanta::Quanta(const Quanta& p):
Particle(p.m_decay_tree, p.m_particle_name, p.m_particle_mass, p.m_particle_charge), m_energy{p.m_energy}
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Copying 'Quanta' abstract class: "<< m_particle_name <<"\n";
}

// Destructor
Quanta::~Quanta()
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Destroying 'Quanta' abstract class: "<< m_particle_name <<"\n";
}

// Move Constructor
Quanta::Quanta(Quanta&& p) noexcept:
Particle(p.m_decay_tree, p.m_particle_name, p.m_particle_mass, p.m_particle_charge), m_energy{p.m_energy}
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Moving 'Quanta' abstract class: "<< m_particle_name <<"\n";
}

// Copy assignment operator
Quanta& Quanta::operator=(const Quanta& p)
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
  //std::cout<<"Calling copy assignment for 'Quanta' abstract class: "<< m_particle_name <<"\n";

  return *this;
}

// Move assignment operator
Quanta& Quanta::operator=(Quanta&& p) noexcept
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
  //std::cout<<"Calling move assignment for 'Quanta' abstract class: "<< m_particle_name <<"\n";

  return *this;
}
