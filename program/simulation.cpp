
#include "simulation.hpp"
#include <limits.h>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "gridPoint.hpp"
#include "particlesState.hpp"
#include "settings.hpp"

Simulation::Simulation(ParticlesState *firstState, ParticlesState *secondState, unsigned long stepCount):stepCount(stepCount)
{
  particlesStates =  static_cast<ParticlesState*> (::operator new (sizeof(ParticlesState[stepCount + 2])));
  particlesStates[0] = *firstState;
  particlesStates[1] = *secondState;
  currentState = 1;
}

ParticlesState* Simulation::SimulationStep()
{
  particlesStates[currentState + 1] = ParticlesState(particlesStates[currentState].N, currentState+1);

  const unsigned long N = particlesStates[currentState].N;

  const unsigned long cM1 = currentState - 1;
  const unsigned long c = currentState;
  const unsigned long cP1 = currentState + 1;
  for(unsigned long i = 0; i < N; ++i)
  {
    particlesStates[cP1][i] = 2*particlesStates[c][i] - particlesStates[cM1][i] + particlesStates[c].getAcceleration(i);
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

void Simulation::runSimulation()
{
  for(unsigned long i; i < stepCount; ++i)
  {
    SimulationStep();
  }
}

Simulation::~Simulation()
{
  delete particlesStates;
}	

