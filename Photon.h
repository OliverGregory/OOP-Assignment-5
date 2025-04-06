/*  
Assignment 5 - Photon header file. All basic functionality which only requires one line is included.
Student Number - 10608637
Created - 31/03/25 
Date - 31/03/25 
*/

// Header guards
#ifndef PHOTON_H
#define PHOTON_H

// Import basic libraries
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Quanta.h"

// Beginning of Photon class
class Photon : public Quanta
{
public:
// Constructors 
  // Deafult Constructor
  Photon()= default;
  // Parameterised Constructor
  Photon(std::vector<std::shared_ptr<Particle>>& m_decay_tree, std::string quanta_name,
         double energy);
  // Copy Constructor
  Photon(const Photon& p);
  // Destructor
  ~Photon();
  // Move Constructor
  Photon(Photon&& p) noexcept;
  // Copy assignment operator
  Photon& operator=(const Photon& p);
  // Move assignment operator
  Photon& operator=(Photon&& p) noexcept;

// No Additional member data so no setters or getters    

// All other functionality
  // Print function
  void print_data() const override;
  // Add to container function allows me to create polymorphic containers which store different types of particle
  void add_to_container(std::vector<std::shared_ptr<Particle>>& container) override;
  //
  friend double photoelectric_effect(Photon& photon);
  //
  friend void compton_effect(Photon& photon, double theta);
  //
  friend std::vector<std::shared_ptr<Particle>> pair_production(Photon& photon, std::string produced_type);

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

#endif // PHOTON_H