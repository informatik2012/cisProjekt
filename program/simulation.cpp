
#include "simulation.hpp"
#include <limits.h>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "gridPoint.hpp"
#include "particlesState.hpp"
#include "settings.hpp"
/*
template<typename T>inline T SQR(T x)
	{  return(x*x);  }
template<typename T>inline T POW3(T x)
	{  return(x*x*x);  }
*/
Simulation::Simulation(ParticlesState *firstState, ParticlesState *secondState, unsigned long stepCount)
{
  particlesStates =  static_cast<ParticlesState*> (::operator new (sizeof(ParticlesState[stepCount + 2])));
  particlesStates[0] = *firstState;
  particlesStates[1] = *secondState;
  currentState = 1;
}
/*
	    // Calculate the potential energy. 
		// This is a Lennard-Jones potential: 
		// Argument: 1/r^2. 
		static double Simulation::potential_1r2(double r2)
		{
			double r6=r2*r2*r2;
			return(4.0*r6*(r6-1.0));
		}
		// Argument: r
		// Note: The min of the potential is at r=1.1225. 
		static double Simulation::potential(double r)
		{  return(potential_1r2(1.0/(r*r)));  }
		
		// Calc 1/|r| * \partial V(|r|) / \partial |r|: 
		// Argument: 1/r^2. 
		static double Simulation::potentialD_1r2(double r2)   // verkehrt rum?
		{
			double r6=r2*r2*r2;
			return(48.0*r6*r2*(0.5-r6));
		}
		
		// Calc r+dv/dr = -24*(2*r^-12-r^-6). Argument r. 
		static double Simulation::potential_w(double r)
		{
			double r6=1.0/POW3(SQR(r));  // r^-6   problem problem?!
			return(24*r6*(1-2*r6));
		}
*/


ParticlesState* Simulation::SimulationStep()
{
  particlesStates[currentState + 1] = ParticlesState(particlesStates[currentState].N, currentState+1);

  const unsigned long N = particlesStates[currentState].N;

  const unsigned long cM1 = currentState - 1;
  const unsigned long c = currentState;
  const unsigned long cP1 = currentState + 1;
  for(unsigned long i = 0; i < N; ++i)
  {
    particlesStates[cP1][i] = particlesStates[c][i] + particlesStates[cM1][i]; 
  }
  ++currentState;
  return &(particlesStates[currentState + 1]);
  /*
  particleArray = new GridPoint[N];

  for (std::vector<GridPoint>::iterator i = particleArray.begin(); i != particleArray.end(); ++i)
  {
    std::vector<GridPoint> ParticlesState::getNeightbours(GridPoint neighbourPoints, long r_c); 

    position[i] = Calculate(position[i], neighbourPoints);  // 

  }
  return particleArray;
*/
}
Simulation::~Simulation()
{
  delete particlesStates;
}	

