/*
Assignment 5 - Practice inheritance in C++ classes
Student Number - 10608637
Created - 31/03/25
Date - 31/03/25
*/

// Libraries
#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>

// Headers
// Interface is found in .h files
// Implementation is found in .cpp files
#include "Photon.h"
#include "Electron.h"
#include "Radioactive_Nucleus.h"
#include "Stable_Nucleus.h"

// Photoelectric effect function is a friend of the 'Photon' class so it can access photon energy despite not being a member function
//   I don't understand why this needs to be a friend function, it's not like this is some broad effect which is entirely independent
//   of photons and MUST be defined outside the class, this could easily be a member function, is it not just a glorified getter?
//   I've made it slightly more exciting so that when photoelectric_effect(photon) is called we construct a new "photoelectron" and add
//   it to the same polymorphic container as the incident photon, its energy is the energy of the incident photon subtract the electron
//   mass; essentially assuming the work function is the electron mass, since the material upon which this photon is incident is unknown.
double photoelectric_effect(Photon& photon)
{
  std::cout<<"\nCalling Photoelectric Effect for Photon: '"<< photon.m_particle_name <<"'\n";
  std::shared_ptr<Electron> e2 = std::make_shared<Electron>(photon.m_decay_tree, "photoelectron", -1, (photon.m_energy-ELECTRON_MASS));
  return photon.m_energy;
}


// Compton effect function is a friend of the 'Photon' class so it can access photon energy despite not being a member function
//   Here, I assume we are treating the Compton effect as a broad physical phenomena whereby a photon interacts with any charged 
//   particle (usually electrons). It is not a property of photons hence why it is a friend function not a member function. The
//   function could potentially be extended to take in another 'Particle' object perhaps an electron or even nucleus and update
//   their energy accordingly as well.
void compton_effect(Photon& photon, double theta)
{
  std::cout<<"\n----Printing Compton Effect Data----\n";
  std::cout<<"Pre-scattering Data:\n";
  photon.print_data();
  std::cout<<"Calling Compton Effect for Photon: '"<< photon.m_particle_name <<"'\n\n";
  photon.m_energy = photon.m_energy / (1 + (photon.m_energy /ELECTRON_MASS) * (1 - std::cos(theta)));
  std::cout<<"Post-scattering Data:\n";
  photon.print_data();
}


// Pair production function is a friend of the 'Photon' class so it can access photon energy despite not being a member function
//   Again, we are treating pair production as a broad physical phenomena not just a property of photons by using a friend function 
//   instead of a member function. In this case, since we are only modelling photons and have no other neutral bosons to which pair
//   production would apply, I believe it is somewhat redundant making this a friend function which lives outside the photon class.
//   Were we to have a "Boson" class then it would make more sense since then we could have this pair production function be a friend 
//   of the photons and Z bosons but not the W bosons. 
std::vector<std::shared_ptr<Particle>> pair_production(Photon& photon, std::string produced_type)
{
  std::vector<std::shared_ptr<Particle>> pair_container{}; // create a vector to store our pair production products in
  double threshold{photon.m_energy}; // store the photons energy in a variable called threshold for validation purposes

  // Basic example of electron-positron production
  if(produced_type=="electron")
  {
    std::cout<<"\nCalling Electron Pair Production for Photon: '"<< photon.m_particle_name <<"'\n";

    if(threshold >= 2*ELECTRON_MASS)
    {
      std::shared_ptr<Electron> e1 = std::make_shared<Electron>(pair_container, "produced electron", -1, (threshold-2*ELECTRON_MASS)/2);
      std::shared_ptr<Electron> e2 = std::make_shared<Electron>(pair_container, "produced positron", +1, (threshold-2*ELECTRON_MASS)/2);
    }
    else
    {
      std::cout<< "\nError! '"<< photon.m_particle_name <<"' has insufficient energy for electron pair production\n";
      std::cout<< "It has "<< photon.m_energy <<"MeV\n";
      std::cout<< "It requires "<< 2*ELECTRON_MASS <<"MeV\n";
    }
  }
  // Here I've implemented proton-anti-proton production too, I really believe this pair production feature would benefit from a
  //   broader selection of particles and doesnt really fit with this assignment, I think it has really cool potential but I'm 
  //   limited here to nuclei and electrons. I've chosen the proton to be type 'Stable_Nucleus' becuase protons are stable, I have
  //   chosen the anti-proton to be type 'Radioactive_nucleus' even though they dont decay in the typical sense, they have extremely
  //   short lifetimes so I have given it a small half life. This is another nice example of polymorphism too in the pair_container
  //   in which I return them.
  else if(produced_type=="proton")
  {
    const double m_p{938}; // Roughly the mass of a proton in MeV

    std::cout<<"\nCalling Proton Pair Production for Photon: '"<< photon.m_particle_name <<"'\n";

    if(threshold >= 2*m_p) 
    {
      std::shared_ptr<Stable_Nucleus> n1 = std::make_shared<Stable_Nucleus>(pair_container, "produced proton", 
        threshold/2, +1, "H");
      std::shared_ptr<Radioactive_Nucleus> n2 = std::make_shared<Radioactive_Nucleus>(pair_container, "produced anti-proton", 
        threshold/2, -1, "H-bar", 0.00000001, false);
    }
    else
    {
      std::cout<< "Error! '"<< photon.m_particle_name <<"' has insufficient energy for proton pair production\n";
      std::cout<< "It has "<< photon.m_energy <<"MeV\n";
      std::cout<< "It requires "<< 2*m_p <<"MeV\n";
    }
  }
  else
  {
    std::cerr<<"Error! Invalid particle type for <produced_type> argument\nPhoton must produce either 'proton' or 'electron'\n";
  }
  return pair_container;
}

// Radiate function is a friend of the 'Electron' class so it can access electron energy despite not being a member function
//   This function makes the most sense being a friend function since all charged particles can emit Bremsstrahlung radiation.
//   If I had the time I would have liked to incorporate a 'kineti_energy' member variable for the nucelei classes, in theory I
//   could then make them emit breaking readiation too using a friend function in near identical manner.
//   Instead of pre-generating the electrons, here i use RNG and a while loop to construct new 'Photon' objects until the electron 
//   energy reaches 0 (or close enough). Once the electron has stoppped no more breaking radiation is released. all of the newly
//   produced photons are stored in one container
std::vector<std::shared_ptr<Particle>> radiate(Electron& electron)
{
  std::vector<std::shared_ptr<Particle>> radiated_photons{}; // create a vector to store our radiated photons in products in
  int iterations = 0;
  const int max_iterations = 5; // Putting a hard limit of 5 photons created by the Bremsstrahlung

  while (electron.m_energy > 0 && iterations<max_iterations)
  {
    std::cout<<"\nCalling Radiate for Electron: '"<< electron.m_particle_name <<"'\n";

    // Store the electron energy in a variable called kinetic_energy for validation purposes, when the electron runs out of 
    //   kinetic energy it has emitted all of its breaking radiation
    double kinetic_energy{electron.m_energy};
    int kinetic_energy_int {static_cast<int>(std::floor(kinetic_energy))};

    // If energy is too low, exit early
    if (kinetic_energy_int <= 0)
    {
      std::cout << "Energy too low to continue.\n";
      break;
    }

    // Generates random numbers between 1 and kinetic_energy_int, nothing fancy
    int random_energy = std::rand() % kinetic_energy_int;
    electron.m_energy -= random_energy; // Subtract from electron's energy

    std::shared_ptr<Electron> e1 = std::make_shared<Electron>(electron.m_decay_tree, electron.m_particle_name, 
      electron.m_particle_charge, electron.m_energy);
    std::shared_ptr<Photon> e2 = std::make_shared<Photon>(radiated_photons, "radiated photon"+std::to_string(iterations+1), random_energy);

    iterations++;
  }
  return radiated_photons;
}

// Main program
int main()
{
  // Signal the start of the program
  std::cout<<"\n----Starting Program----\n";



  // Sodium
  std::cout<<"\n----Start of Sodium Data----\n";
  // This is our polymorphic container, it has within it all the data for our Sodium decay tree. Particles part of the same decay tree 
  //   are linked by the same container. Roughly each container corresponds to one decay diagram.
  std::vector<std::shared_ptr<Particle>> sodium_container{};
  // This is our initial radioactive Sodium nucleus
  std::shared_ptr<Radioactive_Nucleus> sodium = std::make_shared<Radioactive_Nucleus>(sodium_container, "Sodium", 22, 11, "Na", 2.603, false);

  // The Sodium nucleus decays into an electron with 0.545 MeV
  sodium->decay("positron", 0.545);

  // This Neon nucleus is the other one of our decay products from either of the above beta decays
  //   half life not given so set to 0
  std::shared_ptr<Radioactive_Nucleus> neon = std::make_shared<Radioactive_Nucleus>(sodium_container, "Neon", 22, 10, "Ne", 0, false);
  
  // The Neon nucleus decays into a photon with 1274.5 MeV
  std::shared_ptr<Particle> sodium_photon{neon->decay("photon", 1274.5)};
  std::shared_ptr<Photon> sodium_photon_new = std::static_pointer_cast<Photon>(sodium_photon);
  // Pair production with 1274.5 MeV photon should succeed
  std::vector<std::shared_ptr<Particle>> produced_electrons_sodium{pair_production(*sodium_photon_new, "electron")};
  // Print the data from the vector of pair production products
  std::cout<<"\n----Printing Pair Production Data----\n";
  for(auto& i:produced_electrons_sodium)
  {
    i->print_data();
  }
  

  // Radiate function forone of the pair produced electrons
  std::shared_ptr<Particle> breaking_electron {produced_electrons_sodium[0]};
  std::shared_ptr<Electron> breaking_electron_new = std::static_pointer_cast<Electron>(breaking_electron);
  std::vector<std::shared_ptr<Particle>> radiation_container{radiate(*breaking_electron_new)};

  std::cout<<"\n----Printing Bremsstrahlung Data----\n";
  for(auto& i:radiation_container)
  {
    i->print_data();
  }
  std::cout<<"----End of Bremsstrahlung Data----\n";


  // This stable Neon nucleus is the our final state nucleus- instantated this as an example of 'Stable_Nucleus' class
  std::shared_ptr<Stable_Nucleus> neon_stable = std::make_shared<Stable_Nucleus>(sodium_container, "Neon", 22, 10, "Ni");

  // Print data for our first decay tree, using the getters to create isotope name for fun
  std::cout<<"\n----Printing "<< sodium->get_atomic_symbol()+"-"+std::to_string(static_cast<int>(sodium->get_particle_mass())) <<" Decay History----\n";
  for(auto& i:sodium_container)
  {
    i->print_data();
  }
  // Final print functions to show that the has_decayed flag has actually been updated
  std::cout<< sodium->get_atomic_symbol()+"-"+std::to_string(static_cast<int>(sodium->get_particle_mass())) <<" Final state:\n";
  sodium->print_data();
  std::cout<<"----End of Sodium Data----\n";



  // Caesium
  std::cout<<"\n----Start of Caesium Data----\n";
  // This is our polymorphic container, it has within it all the data for our Caesium decay tree. Particles part of the same decay tree 
  //   are linked by the same container. Roughly each container corresponds to one decay diagram.
  std::vector<std::shared_ptr<Particle>> caesium_container{};
  // This is our initial radioactive Caesium nucleus
  std::shared_ptr<Radioactive_Nucleus> caesium = std::make_shared<Radioactive_Nucleus>(caesium_container, "Caesium", 137, 55, "Cs", 30.17, false);

  // The Caesium nucleus decays into an electron with 0.512 MeV or 1.174 MeV
  caesium->decay("electron", 0.512);
  caesium->decay("electron", 1.174);

  // This Barium nucleus is the other one of our decay products from either of the above beta decays
  std::shared_ptr<Radioactive_Nucleus> barium = std::make_shared<Radioactive_Nucleus>(caesium_container, "Barium", 137, 56, "Ba", 0, false);
  
  // The Barium nucleus decays into a photon with 0.661 MeV
  std::shared_ptr<Particle> barium_photon{barium->decay("photon", 0.661)};
  std::shared_ptr<Photon> barium_photon_new = std::dynamic_pointer_cast<Photon>(barium_photon);
  // Pair production with 0.661 MeV photon should fail
  std::vector<std::shared_ptr<Particle>> produced_electrons_caesium{pair_production(*barium_photon_new, "electron")};
  // Print the data from the vector of pair production products
  std::cout<<"\n----Printing Pair Production Data----\n";
  for(auto& i:produced_electrons_caesium)
  {
    i->print_data();
  }

  // This stable Barium nucleus is the our final state nucleus- instantated this as an example of 'Stable_Nucleus' class
  std::shared_ptr<Stable_Nucleus> barium_stable = std::make_shared<Stable_Nucleus>(caesium_container, "Barium", 137, 56, "Ba");

  // Print data for our first decay tree, using the getters to create isotope name for fun
  std::cout<<"\n----Printing "<< caesium->get_atomic_symbol()+"-"+std::to_string(static_cast<int>(caesium->get_particle_mass())) <<" Decay History----\n";
  for(auto& i:caesium_container)
  {
    i->print_data();
  }
  // Final print functions to show that the has_decayed flag has actually been updated
  std::cout<< caesium->get_atomic_symbol()+"-"+std::to_string(static_cast<int>(caesium->get_particle_mass())) <<" Final state:\n";
  caesium->print_data();
  std::cout<<"----End of Caesium Data----\n";



  // Cobalt
  std::cout<<"\n----Start of Cobalt Data----\n";
  // This is our polymorphic container, it has within it all the data for our Cobalt decay tree. Particles part of the same decay tree 
  //   are linked by the same container. Roughly each container corresponds to one decay diagram.
  std::vector<std::shared_ptr<Particle>> cobalt_container{};
  // This is our initial radioactive Cobalt nucleus
  std::shared_ptr<Radioactive_Nucleus> cobalt = std::make_shared<Radioactive_Nucleus>(cobalt_container, "Cobalt", 60, 27, "Co", 5.272, false);

  // The Cobalt nucleus decays into an electron with 0.31 MeV or 1.48 MeV
  cobalt->decay("electron", 0.31);
  cobalt->decay("electron", 1.48);

  // This Nickel nucleus is the other one of our decay products from either of the above beta decays
  //   half life not given so set to 0
  std::shared_ptr<Radioactive_Nucleus> nickel = std::make_shared<Radioactive_Nucleus>(cobalt_container, "Nickel", 60, 28, "Ni", 0, false);
  
  // The Nickel nucleus decays into a photon with 1.1732 MeV or 1.3325 MeV 
  std::shared_ptr<Particle> nickel_photon_1{nickel->decay("photon", 1.1732)};
  std::shared_ptr<Photon> nickel_photon_1_new = std::static_pointer_cast<Photon>(nickel_photon_1);
  std::shared_ptr<Particle> nickel_photon_2{nickel->decay("photon", 1.3325)};
  std::shared_ptr<Photon> nickel_photon_2_new = std::static_pointer_cast<Photon>(nickel_photon_2);

  // Compton Scattering one of the nickel gamma rays through 0.2 radians
  compton_effect(*nickel_photon_1_new, 0.2);

  // Demonstrating the photoelecrtric effect with the other nickel gamma ray
  photoelectric_effect(*nickel_photon_2_new);

  // This stable Nickel nucleus is the our final state nucleus- instantated this as an example of 'Stable_Nucleus' class
  std::shared_ptr<Stable_Nucleus> nickel_stable = std::make_shared<Stable_Nucleus>(cobalt_container, "Nickel", 60, 28, "Ni");

  // Print data for our first decay tree, using the getters to create isotope name for fun
  std::cout<<"\n----Printing "<< cobalt->get_atomic_symbol()+"-"+std::to_string(static_cast<int>(cobalt->get_particle_mass())) <<" Decay History----\n";
  for(auto& i:cobalt_container)
  {
    i->print_data();
  }
  // Final print functions to show that the has_decayed flag has actually been updated
  std::cout<< cobalt->get_atomic_symbol()+"-"+std::to_string(static_cast<int>(cobalt->get_particle_mass())) <<" Final state:\n";
  cobalt->print_data();
  std::cout<<"----End of Cobalt Data----\n";


  
  // Iron
  std::cout<<"\n----Start of Iron Data----\n";
  // Iron nucleus instantated here purely as an example of 'Stable_Nucleus' class required in spec
  // Not part of any of the decay trees shown so gets its own container
  std::vector<std::shared_ptr<Particle>> iron_container{};
  std::shared_ptr<Stable_Nucleus> iron_stable = std::make_shared<Stable_Nucleus>(iron_container, "Iron", 56, 26, "Fe");
  iron_stable->print_data();
  std::cout<<"----End of Iron Data----\n";



  // Signal the end of the program
  std::cout<<"\n----Ending Program----\n\n";

  /* EXTRA TEST CODE FOR NUCLEUS PAIR PRODUCTION FEEL FREE TO UNCOMMENT
  std::vector<std::shared_ptr<Particle>> test_container{};

  // Construct a photon with high energy and one with lower energy for demonstrating the friend functions 
  std::shared_ptr<Photon> g1 = std::make_shared<Photon>(test_container, "photon1", 7);
  std::shared_ptr<Photon> g2 = std::make_shared<Photon>(test_container, "photon2", 2000);


  // Demonstraing functionality of the pair_production function
  // First the basic implementation of electron pair production
  std::vector<std::shared_ptr<Particle>> produced_electrons_container{pair_production(*g1, "electron")};
  // Showing what happens when you pair produce without sufficient energy
  std::vector<std::shared_ptr<Particle>> produced_protons_container1{pair_production(*g1, "proton")};
  // Example of successful pair production for protons just for fun
  std::vector<std::shared_ptr<Particle>> produced_protons_container2{pair_production(*g2, "proton")};
  // Printing all the data for the vectors of particles which are returned by pair_production()

  std::cout<<"\n----Printing Pair Production Data----\n";
  for(auto& i:produced_electrons_container)
  {
    i->print_data();
  }
  
  for(auto& i:produced_protons_container2)
  {
    i->print_data();
  }
  */

  return 0;
}
