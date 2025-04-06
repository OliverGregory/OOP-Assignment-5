My compile line: `g++ -o Assignment-5 *.cpp`
To excecute: `./Assignment-5`

Since this assignment seems to be largely open to interpretation I've tried to incorporate as much inheritence
  and polymorphism as I can. I have used Particle as the base class then since photons, electron, and nuclei all 
  have the same basic properties like mass and charge and require a print function, I decided that there should
  be a Nucleus derived class with two further derived classes Stable_Nucleus and Radioactive_Nucleus. Similarly 
  I have a Quanta class which inherits from Particle, then Electron and Photon both inherit from that. Particle,
  Nucleus and Quanta are all abstract classes.

I also use a vectors of smart pointers which can store Particles of any derived type using polymorphism, I use these 
  polymorphic containers to store every particle in a decay chain. So if a nucleus decays to another nucleus and emits
  an electron which then emits photons etc... all particles automatically get added to the same container upon 
  construction. So I have a container for each of the diagrams shown in the specification, a sodium container, cobalt 
  container etc... If I had more time I would implement these containers as a class of their own and try to create a 
  tree data structure which could eliminate a lot of code repitition.

I think the way I have designed th code leaves a lot of room for potential expansion. It would be relatiely easy to 
  model almost any decay tree and store it all in one place and extend to any additional particle classes.