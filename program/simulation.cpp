#include "simulation.hpp"
#include <limits.h>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include "gridPoint.hpp"
#include "gridPointDouble.hpp"
#include "particlesState.hpp"
#include "settings.hpp"

Simulation::Simulation(std::vector<unsigned long> *masses, ParticlesState *firstState, ParticlesState *secondState, unsigned long stepCount, std::string outputDir, double lennardJonesA, double lennardJonesB):masses(*masses), stepCount(stepCount), outputDir(outputDir), lennardJonesA(lennardJonesA), lennardJonesB(lennardJonesB)
{
  if(access(outputDir.c_str(), 0) != 0)
  {
    mkdir(outputDir.c_str(), 0777);
  }
  particlesStates =  static_cast<ParticlesState*> (::operator new (sizeof(ParticlesState[stepCount + 2])));
  particlesStates[0] = *firstState;
  particlesStates[0].writeToFile(outputDir, 0);
  particlesStates[1] = *secondState;
  particlesStates[1].writeToFile(outputDir, 1);
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
    GridPointDouble acceleration = particlesStates[c].getAcceleration(i, &masses, lennardJonesA, lennardJonesB);
    GridPoint halfAcceleration;
    for(int j = 0; j < 3; ++j)
    {
      long halfAccelerationJ = (long) (0.5 * acceleration[j]);
      if(GridPoint::LOWERBOUND <= halfAccelerationJ && halfAccelerationJ <= GridPoint::UPPERBOUND)
      {
        halfAcceleration[j] = (long) (0.5 * acceleration[j]);
      }
      else
      {
        std::cout << "Acceleration too big" << std::endl;
        exit(1);
      }
    }
    particlesStates[cP1][i] = particlesStates[c][i] + particlesStates[c][i] - particlesStates[cM1][i] + halfAcceleration;
    for(int j = 0; j < 3; ++j)
    {
      if(particlesStates[cP1][i][j] > maxCoordinate[j])
      {
        maxCoordinate[j] = particlesStates[cP1][i][j];
      }
      else if(particlesStates[cP1][i][j] < minCoordinate[j])
      {
        minCoordinate[j] = particlesStates[cP1][i][j];
      }
    }
    //std::cout << particlesStates[c].getAcceleration(i, lennardJonesA, lennardJonesB);
    //std::cout << lennardJonesA;
    //std::cout << particlesStates[cP1][i];
  }

  particlesStates[cP1].writeToFile(outputDir, cP1);

  ++currentState;


  return &(particlesStates[cP1]);
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


void Simulation::writeEnergiesToFile()
{
  std::stringstream filePathStream;
  filePathStream << outputDir << "energies.dat";
  std::fstream f;
  f.open(filePathStream.str().c_str(), std::fstream::in | std::fstream::out | std::fstream::trunc);
  f << "i\tkin\tpot\ttotal" << std::endl;
  double totPotEnergy = 0.0;
  for(unsigned long i = 1; i <= stepCount; ++i)
  {
    double totKinEnergy = particlesStates[i].getTotalKinEnergy(&masses, &(particlesStates[i-1]));
    if(i > 1)
    {
      totPotEnergy += particlesStates[i].getTotalPotEnergy(&(particlesStates[i-1]), lennardJonesA, lennardJonesB);
    }
    f << i << "\t" << totKinEnergy;
    f << "\t" << totPotEnergy;
    f << "\t" << (totKinEnergy + totPotEnergy);
    f << std::endl; 

  }
  f.close();

}

void Simulation::writeMiddleDistancesToFile()
{
  std::stringstream filePathStream;
  filePathStream << outputDir << "distances.dat";
  std::fstream f;
  f.open(filePathStream.str().c_str(), std::fstream::in | std::fstream::out | std::fstream::trunc);
  f << "i\tdistances" << std::endl;
  
  for(unsigned long i = 0; i <= stepCount; ++i)
  {
    f << i << "\t" << particlesStates[i].getMiddleDistance();
    f << std::endl; 
  }
  f.close();

}

void Simulation::writeMinAndMaxCoordinateToFile()
{
  std::stringstream filePathStream;
  filePathStream << outputDir << "minandmax.dat";
  std::fstream f;
  f.open(filePathStream.str().c_str(), std::fstream::in | std::fstream::out | std::fstream::trunc);

  long minTotal = minCoordinate[1];
  long maxTotal = maxCoordinate[1];
  if(minCoordinate[0] < minCoordinate[1])
  {
    minTotal = minCoordinate[0];
  }
  if(minCoordinate[2] < minTotal)
  {
      minTotal = minCoordinate[2];
  }
  if(maxCoordinate[0] > maxCoordinate[1])
  {
    maxTotal = maxCoordinate[0];
  }
  if(maxCoordinate[2] > maxTotal)
  {
    maxTotal = maxCoordinate[2];
  }
  f << "SIMU_MIN_TOT=" << minTotal << std::endl;
  f << "SIMU_MIN_X=" << minCoordinate[0] << std::endl;
  f << "SIMU_MIN_Y=" << minCoordinate[1] << std::endl;
  f << "SIMU_MIN_Z=" << minCoordinate[2] << std::endl;
  f << "SIMU_MAX_TOT=" << maxTotal << std::endl;
  f << "SIMU_MAX_X=" << maxCoordinate[0] << std::endl;
  f << "SIMU_MAX_Y=" << maxCoordinate[1] << std::endl;
  f << "SIMU_MAX_Z=" << maxCoordinate[2] << std::endl;  

  f.close();
}

void Simulation::runSimulation()
{
  maxCoordinate = GridPoint(0,0,0);
  minCoordinate = GridPoint(0,0,0);
  for(unsigned long i = 0; i < stepCount; ++i)
  {
    SimulationStep();
  }
  writeEnergiesToFile();
  writeMiddleDistancesToFile();
  writeMinAndMaxCoordinateToFile();
}


Simulation::~Simulation()
{
  delete particlesStates;
}	

