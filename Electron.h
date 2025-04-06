/*  
Assignment 5 - Electron header file. All basic functionality which only requires one line is included.
Student Number - 10608637
Created - 31/03/25 
Date - 31/03/25 
*/

// Header guards
#ifndef ELECTRON_H
#define ELECTRON_H

// Import basic libraries
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Quanta.h"

// Beginning of Electron class
class Electron : public Quanta
{
public:
// Constructors 
  // Deafult Constructor
  Electron()= default;
  // Parameterised Constructor
  Electron(std::vector<std::shared_ptr<Particle>>& m_decay_tree, std::string quanta_name,
           double charge,
           double energy);
  // Copy Constructor
  Electron(const Electron& p);
  // Destructor
  ~Electron();
  // Move Constructor
  Electron(Electron&& p) noexcept;
  // Copy assignment operator
  Electron& operator=(const Electron& p);
  // Move assignment operator
  Electron& operator=(Electron&& p) noexcept;

// No Additional member data so no setters or getters  

// All other functionality
  // Print function
  void print_data() const override;
  // This radiate function inherited from the particle class takes the place of the "radiate" function in my code
  friend std::vector<std::shared_ptr<Particle>> radiate(Electron& electron);
  // Add to container function allows me to create polymorphic containers which store different types of particle
  void add_to_container(std::vector<std::shared_ptr<Particle>>& container) override;
  

private:
// Member variables
  // Inherited member data commented out
  /*
  std::string m_particle_name;
  double m_particle_mass;
  double m_particle_charge;
  double m_energy;
  */
  // Un-inherited member data

};

#endif // ELECTRON_H