#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "particlesState.hpp"

class Simulation
{
public:
  //Simulation(ParticlesState *firstState, ParticlesState *secondState, unsigned long stepCount);

  Simulation(std::vector<unsigned long> *masses, ParticlesState *firstState, ParticlesState *secondState, unsigned long stepCount,
      std::string outputDir, double lennardJonesA = 0.0, double lennardJonesB = 0.0);

  ParticlesState* SimulationStep();
  void writeEnergiesToFile();
  void writeMiddleDistancesToFile();
  void writeMinAndMaxCoordinateToFile();
  void runSimulation();

	~Simulation();
  	


private:
  std::vector<unsigned long> masses;
  ParticlesState *particlesStates;
  unsigned long currentState;
  unsigned long stepCount;
  std::string outputDir;
  double lennardJonesA;
  double lennardJonesB;
  GridPoint maxCoordinate;
  GridPoint minCoordinate;
};
#endif
