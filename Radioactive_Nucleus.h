/*  
Assignment 5 - Radioactive Nucleus header file. All basic functionality which only requires one line is included.
Student Number - 10608637
Created - 31/03/25 
Date - 31/03/25 
*/

// Header guards
#ifndef RADIOACTIVE_NUCLEUS_H
#define RADIOACTIVE_NUCLEUS_H

// Import basic libraries and headers
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Nucleus.h"

// Beginning of Radioactive_Nucleus class
class Radioactive_Nucleus : public Nucleus
{
public:
// Constructors 
  // Deafult Constructor
  Radioactive_Nucleus()= default;
  // Parameterised Constructor
  Radioactive_Nucleus(std::vector<std::shared_ptr<Particle>>& m_decay_tree, std::string nucleus_name,
                      double atomic_mass,
                      double atomic_number,
                      std::string atomic_symbol,
                      double half_life,
                      bool has_decayed);
  // Copy Constructor
  Radioactive_Nucleus(const Radioactive_Nucleus& p);
  // Destructor
  ~Radioactive_Nucleus();
  // Move Constructor
  Radioactive_Nucleus(Radioactive_Nucleus&& p) noexcept;
  // Copy assignment operator
  Radioactive_Nucleus& operator=(const Radioactive_Nucleus& p);
  // Move assignment operator
  Radioactive_Nucleus& operator=(Radioactive_Nucleus&& p) noexcept;

// Getters
// Added a new getter for the additional member variables "half_life" and "has_decayed" unique to this class
  double get_half_life() const {return m_half_life;}
  bool get_has_decayed() const {return m_has_decayed;}


// Setters
// Added a new setter for the additional member variable "half_life" and "has_decayed" unique to this class
  void set_half_life(const double half_life){m_half_life=half_life;}
  void set_has_decayed(const bool has_decayed){m_has_decayed=has_decayed;}

// All other functionality  
  // Print function
  void print_data() const override;
  // Decay function
  std::shared_ptr<Particle> decay(std::string product2, double decay_energy);
  // Add to container function allows me to create polymorphic containers which store different types of particle
  void add_to_container(std::vector<std::shared_ptr<Particle>>& container) override;

private:
// Member variables
  // Inherited member data commented out
  /*
  std::string m_particle_name;
  double m_particle_mass;
  double m_particle_charge;
  std::string m_atomic_symbol;
  */
  // Un-inherited member data
  double m_half_life;
  bool m_has_decayed;
};

#endif // RADIOACTIVE_NUCLEUS_H