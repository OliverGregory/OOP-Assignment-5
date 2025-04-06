/*  
Assignment 5 - Implementation of the Radioactive Nucleus class.
Student Number - 10608637
Created - 31/03/25 
Date - 31/03/25 
*/

// Import basic libraries and headers
#include <iostream>
#include <sstream>
#include "Radioactive_Nucleus.h"
#include "Electron.h"
#include "Photon.h"


// Constructors
// Parameterised Constructor
Radioactive_Nucleus::Radioactive_Nucleus(std::vector<std::shared_ptr<Particle>>& decay_tree, std::string nucleus_name, 
                                         double atomic_mass,
                                         double atomic_number,
                                         std::string atomic_symbol,
                                         double half_life,
                                         bool has_decayed):
Nucleus(decay_tree, nucleus_name, atomic_mass, atomic_number, atomic_symbol), m_half_life{half_life}, m_has_decayed{has_decayed}
{
  // Every time we construct a non_abstract particle of type 'Photon' it gets added to the polymorphic container
  add_to_container(decay_tree);  
  // Useful message for debugging and understanding memory
  //std::cout<<"Constructing 'Radioactive_Nucleus' derived class: "<< m_particle_name <<"\n";
}

// Copy Constructor required... invokes rule of 5
Radioactive_Nucleus::Radioactive_Nucleus(const Radioactive_Nucleus& p):
Nucleus(p.m_decay_tree, p.m_particle_name, p.m_particle_mass, p.m_particle_charge, p.m_atomic_symbol),
        m_half_life{p.m_half_life}, m_has_decayed{p.m_has_decayed}
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Copying 'Radioactive_Nucleus' derived class: "<< m_particle_name <<"\n";
}

// Destructor
Radioactive_Nucleus::~Radioactive_Nucleus()
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Destroying 'Radioactive_Nucleus' derived class: "<< m_particle_name <<"\n";
}

// Move Constructor
Radioactive_Nucleus::Radioactive_Nucleus(Radioactive_Nucleus&& p) noexcept:
Nucleus(p.m_decay_tree, p.m_particle_name, p.m_particle_mass, p.m_particle_charge, p.m_atomic_symbol),
        m_half_life{p.m_half_life}, m_has_decayed{p.m_has_decayed}
{
  // Useful message for debugging and understanding memory
  //std::cout<<"Moving 'Radioactive_Nucleus' derived class: "<< m_particle_name <<"\n";
}

// Copy assignment operator
Radioactive_Nucleus& Radioactive_Nucleus::operator=(const Radioactive_Nucleus& p)
{
  if(&p == this)
  {
    return *this;
  }
  m_decay_tree = p.m_decay_tree;
  m_particle_name = p.m_particle_name;
  m_particle_mass = p.m_particle_mass;
  m_particle_charge = p.m_particle_charge;
  m_atomic_symbol = p.m_atomic_symbol;
  m_half_life = p.m_half_life;
  m_has_decayed = p.m_has_decayed;
  // Useful message for debugging and understanding memory
  //std::cout<<"Calling copy assignment for 'Radioactive_Nucleus' derived class: "<< m_particle_name <<"\n";

  return *this;
}

// Move assignment operator
Radioactive_Nucleus& Radioactive_Nucleus::operator=(Radioactive_Nucleus&& p) noexcept
{
  if(&p == this)
  {
    return *this;
  }
  m_decay_tree = p.m_decay_tree;
  m_particle_name = p.m_particle_name;
  m_particle_mass = p.m_particle_mass;
  m_particle_charge = p.m_particle_charge;
  m_atomic_symbol = p.m_atomic_symbol;
  m_half_life = p.m_half_life;
  m_has_decayed = p.m_has_decayed;
  // Useful message for debugging and understanding memory
  //std::cout<<"Calling move assignment for 'Radioactive_Nucleus' derived class: "<< m_particle_name <<"\n";

  return *this;
}


// Other functionality
void Radioactive_Nucleus::print_data() const
{
  std::cout.precision(3);
  std::cout<< "Name: "<< m_particle_name<< "\n";
  std::cout<< "Atomic mass: "<< m_particle_mass*DALTON << " MeV/c^2\n";
  std::cout<< "Atomic number: "<< m_particle_charge << " e\n";
  std::cout<< "Atomic symbol: "<< m_atomic_symbol << "\n";
  std::cout<< "Half life: "<< m_half_life << " years\n";
  std::cout<< "Has decayed? "<< m_has_decayed <<"\n\n";
  //std::cout<< "Memory address: "<< this<< "\n\n";
}

// Decay function for a radioactive nucleus takes in an identifier string to determine what decay is happening and the decay energy
std::shared_ptr<Particle> Radioactive_Nucleus::decay(std::string product2, double decay_energy)
{
  this->set_has_decayed(true); // set flag to true

  if(product2 == "electron")
  {
    std::cout<<"\nCalling Decay for Radioactive Nucleus: '"<< m_particle_name <<"' via beta-minus decay\n";
    std::shared_ptr<Electron> prod = std::make_shared<Electron>(this->m_decay_tree, "beta electron", -1, decay_energy);
    std::cout<<"Printing data for radiated quanta:\n";
    prod->print_data();
    return prod;
  }
  if(product2 == "positron")
  {
    std::cout<<"\nCalling Decay for Radioactive Nucleus: '"<< m_particle_name <<"' via beta-plus decay\n";
    std::shared_ptr<Electron> prod = std::make_shared<Electron>(this->m_decay_tree, "beta positron", +1, decay_energy);
    std::cout<<"Printing data for radiated quanta:\n";
    prod->print_data();
    return prod;
  }
  if(product2 == "photon")
  {
    std::cout<<"\nCalling Decay for Radioactive Nucleus: '"<< m_particle_name <<"' via gamma decay\n";
    std::shared_ptr<Photon> prod = std::make_shared<Photon>(this->m_decay_tree, m_particle_name+" gamma photon", decay_energy);
    std::cout<<"Printing data for radiated quanta:\n";
    prod->print_data();
    return prod;
  }
  else
  {
    std::cerr<<"Error! Invalid particle type for <product2> argument\nPhoton must produce either 'electron', 'positron' or 'photon'\n";
    return{};
  }
}

// Add to container function allows me to create polymorphic containers which store different types of particle
void Radioactive_Nucleus::add_to_container(std::vector<std::shared_ptr<Particle>>& container)
{
  container.push_back(std::make_shared<Radioactive_Nucleus>(*this));
}
