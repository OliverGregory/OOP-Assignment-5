/*  
Assignment 5 - Quanta header file. All basic functionality which only requires one line is included.
Student Number - 10608637
Created - 31/03/25 
Date - 31/03/25 
*/

// Header guards
#ifndef QUANTA_H
#define QUANTA_H

// Import basic libraries
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Particle.h"

// Beginning of Quanta class
class Quanta : public Particle
{
public:
// Constructors 
  // Deafult Constructor
  Quanta()= default;
  // Parameterised Constructor
  Quanta(std::vector<std::shared_ptr<Particle>>& m_decay_tree, std::string quanta_name, 
         double rest_mass,
         double charge,
         double energy);
  // Copy Constructor
  Quanta(const Quanta& p);
  // Destructor
  virtual ~Quanta();
  // Move Constructor
  Quanta(Quanta&& p) noexcept;
  // Copy assignment operator
  Quanta& operator=(const Quanta& p);
  // Move assignment operator
  Quanta& operator=(Quanta&& p) noexcept;


// Getters
  double get_energy() const {return m_energy;}


// Setters- need validation here to make sure nothing is unphysical
  void set_energy(const double energy){m_energy=energy;}
  

// All other functionality- all pure virtual functions in these abstract classes
  // Print function
  virtual void print_data() const =0;
  // Add_to_container function adds 'Particle' objects to a single container utilising polymorphism
  //   Every time a nucleus is constructed and decays, ALL particles subsequently producesd in the
  //   decay tree get added to a corresponding container for that nucleus
  void add_to_container(std::vector<std::shared_ptr<Particle>>& container) = 0;


protected:
// Member variables
  // Inherited member data commented out
  /*
  std::string m_particle_name;
  double m_particle_mass;
  double m_particle_charge;
  */
  // Un-inherited member data
  double m_energy;
};

#endif // QUANTA_H