/*  
Assignment 5 - Nucleus header file. All basic functionality which only requires one line is included.
Student Number - 10608637
Created - 31/03/25 
Date - 31/03/25 
*/

// Header guards
#ifndef NUCLEUS_H
#define NUCLEUS_H

// Import basic libraries
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Particle.h"

// Beginning of Nucleus class
class Nucleus : public Particle
{
public:
// Constructors 
  // Deafult Constructor
  Nucleus()= default;
  // Parameterised Constructor
  Nucleus(std::vector<std::shared_ptr<Particle>>& m_decay_tree, std::string nucleus_name,
          double atomic_mass,
          double atomic_number,
          std::string atomic_symbol);
  // Copy Constructor
  Nucleus(const Nucleus& p);
  // Destructor
  virtual ~Nucleus();
  // Move Constructor
  Nucleus(Nucleus&& p) noexcept;
  // Copy assignment operator
  Nucleus& operator=(const Nucleus& p);
  // Move assignment operator
  Nucleus& operator=(Nucleus&& p) noexcept;


// Getters
  std::string get_atomic_symbol() const {return m_atomic_symbol;}


// Setters- no realistic validation here
  void set_atomic_symbol(const std::string atomic_symbol){m_atomic_symbol=atomic_symbol;}


// All other functionality- all pure virtual functions in these abstract classes 
  // Print function
  virtual void print_data() const = 0;
  // Add_to_container function adds 'Particle' objects to a single container utilising polymorphism
  //   Every time a nucleus is constructed and decays, ALL particles subsequently producesd in the
  //   decay tree get added to a corresponding container for that nucleus
  virtual void add_to_container(std::vector<std::shared_ptr<Particle>>& container) = 0;

protected:
// Member variables
  // Inherited member data commented out
  /*
  std::string m_particle_name;
  double m_particle_mass;
  double m_particle_charge;
  */
  // Un-inherited member data
  std::string m_atomic_symbol;
};

#endif // NUCLEUS_H