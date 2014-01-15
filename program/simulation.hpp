#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "particlesState.hpp"

//  [ Lennard-Jones potential: V(r) = V0 * (r/sigma)^-12 - (r/sigma)^-6 ]
// -------------------------------------------
//  sigma   -> where potential is 0
//  epsilon  -> the minimum of the potential
//  m     -> 1       (mass)
//  x,y,z -> (x,y,z) / sigma
//  t     -> t * sqrt(eps/(m*sigma^2))
//  rho   -> rho * sigma^3
//  v     -> v * sqrt(m/epsilon)   (speed)
//  F     -> F * sigma/epsilon
//  E     -> E / epsilon
//  T     -> T * k_B/epsilon
//  V0    -> 4 
// --------------------------------------------

class Simulation
{
public:
  Simulation(ParticlesState *firstState, ParticlesState *secondState, unsigned long stepCount);

  ParticlesState* SimulationStep();
  void runSimulation();

	~Simulation();
  	


private:
  ParticlesState *particlesStates;
  unsigned long currentState;
  unsigned long stepCount;
};
#endif
