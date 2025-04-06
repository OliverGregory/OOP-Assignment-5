/*  
Assignment 5 - Particle header file. All basic functionality which only requires one line is included.
Student Number - 10608637
Created - 31/03/25 
Date - 31/03/25 
*/

// Header guards
#ifndef PARTICLE_H
#define PARTICLE_H

// Import basic libraries
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Global variables- 
extern const double ELECTRON_MASS; // electron mass used extern to avoids multiple definition/linker errors
extern const double DALTON; // Using the dalton to convert between atomic mass and MeV

// Beginning of Particle class
class Particle
{
public:
// Constructors 
  // Deafult Constructor
  Particle()= default;
  // Parameterised Constructor
  Particle(std::vector<std::shared_ptr<Particle>>& m_decay_tree, std::string particle_name, double particle_mass, double particle_charge);
  // Copy Constructor
  Particle(const Particle& p);
  // Destructor
  virtual ~Particle();
  // Move Constructor
  Particle(Particle&& p) noexcept;
  // Copy assignment operator
  Particle& operator=(const Particle& p);
  // Move assignment operator
  Particle& operator=(Particle&& p) noexcept;


// Getters
  std::string get_particle_name() const {return m_particle_name;}
  double get_particle_mass() const {return m_particle_mass;}
  double get_particle_charge() const {return m_particle_charge;}


// Setters- need validation here to make sure nothing is unphysical
  void set_particle_name(const std::string particle_name){m_particle_name=particle_name;}
  void set_particle_mass(const double particle_mass){m_particle_mass=particle_mass;}
  void set_particle_charge(const double particle_charge){m_particle_charge=particle_charge;}
  

// All other functionality- all pure virtual functions in these abstract classes
  // Print function
  virtual void print_data() const = 0;
  // Add_to_container function adds 'Particle' objects to a single container utilising polymorphism
  //   Every time a nucleus is constructed and decays, ALL particles subsequently producesd in the
  //   decay tree get added to a corresponding container for that nucleus
  virtual void add_to_container(std::vector<std::shared_ptr<Particle>>& container) = 0;


protected:
// Member variables are protected so only derived classes can access them
  std::string m_particle_name;
  double m_particle_mass;
  double m_particle_charge;
  std::vector<std::shared_ptr<Particle>>& m_decay_tree;
};

#endif // PARTICLE_H