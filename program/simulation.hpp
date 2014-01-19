#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "particlesState.hpp"

class Simulation
{
public:
  Simulation(ParticlesState *firstState, ParticlesState *secondState, unsigned long stepCount);

  Simulation(ParticlesState *firstState, ParticlesState *secondState, unsigned long stepCount,
      std::string outputDir, double lennardJonesA = 0.0, double lennardJonesB = 0.0);

  ParticlesState* SimulationStep();
  void writeEnergiesToFile();
  void runSimulation();

	~Simulation();
  	


private:
  ParticlesState *particlesStates;
  unsigned long currentState;
  unsigned long stepCount;
  std::string outputDir;
  double lennardJonesA;
  double lennardJonesB;
};
#endif
