/*  
Assignment 5 - Implementation of the Particle class.
Student Number - 10608637
Created - 31/03/25 
Date - 31/03/25 
*/

// Import basic libraries and headers
#include <iostream>
#include <sstream>
#include "Particle.h"

// Global variable
const double ELECTRON_MASS = 0.511; // electron mass in MeV/c^2
const double DALTON = 931.5; // dalton in MeV/c^2

// Constructors
// Parameterised Constructor
Particle::Particle(std::vector<std::shared_ptr<Particle>>& decay_tree, std::string particle_name,
                   double particle_mass,
                   double particle_charge):
m_decay_tree{decay_tree}, m_particle_name{particle_name}, m_particle_mass{particle_mass}, m_particle_charge{particle_charge}
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Constructing 'Particle' abstract class: "<< m_particle_name <<"\n";
}

// Copy Constructor required... invokes rule of 5
Particle::Particle(const Particle& p):
m_decay_tree{p.m_decay_tree}, m_particle_name{p.m_particle_name}, m_particle_mass{p.m_particle_mass}, m_particle_charge{p.m_particle_charge}
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Copying 'Particle' abstract class: "<< m_particle_name <<"\n";
}

// Destructor
Particle::~Particle()
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Destroying 'Particle' abstract class: "<< m_particle_name <<"\n";
}

// Move Constructor
Particle::Particle(Particle&& p) noexcept:
m_decay_tree{p.m_decay_tree}, m_particle_name{p.m_particle_name}, m_particle_mass{p.m_particle_mass}, m_particle_charge{p.m_particle_charge}
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Moving 'Particle' abstract class: "<< m_particle_name <<"\n";
}

// Copy assignment operator
Particle& Particle::operator=(const Particle& p)
{
  if(&p == this)
  {
    return *this;
  }
  m_decay_tree = p.m_decay_tree;
  m_particle_name = p.m_particle_name;
  m_particle_mass = p.m_particle_mass;
  m_particle_charge = p.m_particle_charge;
  // Useful message for debugging and understanding memory
  //std::cout<<"Calling copy assignment for 'Particle' abstract class: "<< m_particle_name <<"\n";

  return *this;
}

// Move assignment operator
Particle& Particle::operator=(Particle&& p) noexcept
{
  if(&p == this)
  {
    return *this;
  }
  m_decay_tree = p.m_decay_tree;
  m_particle_name = p.m_particle_name;
  m_particle_mass = p.m_particle_mass;
  m_particle_charge = p.m_particle_charge;
  // Useful message for debugging and understanding memory
  //std::cout<<"Calling move assignment for 'Particle' abstract class: "<< m_particle_name <<"\n";

  return *this;
}
