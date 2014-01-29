#include "particlesState.hpp"
#include <fstream>
#include <sstream>
#include <assert.h>
#include <stdlib.h>
GridPoint ONEPOINT(1,1,1);

//const double ParticlesState::lennardJonesA = 12.0;
//const double ParticlesState::lennardJonesB = 12.0;


ParticlesState::ParticlesState(unsigned long N, unsigned long iteration):N(N),iteration(iteration)
{
  particlePositions = new GridPoint[N];
}
ParticlesState::ParticlesState(std::vector<GridPoint> *particlePositions, unsigned long iteration):N(particlePositions->size()),iteration(iteration)
{
  this->particlePositions = new GridPoint[particlePositions->size()];
  for(unsigned long i = 0; i < particlePositions->size(); ++i)
  {
    this->particlePositions[i] = (*particlePositions)[i];
  }
}


ParticlesState::ParticlesState(unsigned long N, GridPoint bottomLeft, GridPoint topRight, unsigned long iteration):N(N),iteration(iteration)
{
  particlePositions = new GridPoint[N];

  for(long i = 0; i < N; ++i)
  {
    bool alreadyInserted;
    do
    {
      alreadyInserted = false;
      particlePositions[i] = GridPoint(bottomLeft, topRight);
      for(long j; j < i; ++j)
      {
        if(particlePositions[j] == particlePositions[i])
        {
          alreadyInserted = true;
          break;
        }
      }
    } while(alreadyInserted);
  }
}
ParticlesState::ParticlesState(ParticlesState *first, std::vector<unsigned long> *velocities)
  :N(first->N),iteration(first->nextIt())
{
  assert(first->N == velocities->size());
  particlePositions = new GridPoint[N];
  for(long i = 0; i < N; ++i)
  {
    bool alreadyInserted;
    do
    {
      alreadyInserted = false;
      particlePositions[i] = GridPoint((*first)[i], (*velocities)[i]);
      for(long j; j < i; ++j)
      {
        if(particlePositions[j] == particlePositions[i])
        {
          alreadyInserted = true;
          break;
        }
      }
    } while(alreadyInserted);
  }
}
ParticlesState::~ParticlesState()
{
  // if(particlePositions != NULL)
  
  if(N > 0)
  {
    //delete[] particlePositions;
  }
}

unsigned long ParticlesState::nextIt()
{
  return (iteration + 1);
}
std::vector<GridPoint> ParticlesState::getNeightbours(GridPoint origin, long radius)
{
  std::vector<GridPoint> neighbourPoints;
  const GridPoint rPoint = radius * GridPoint::ONEPOINT;
  const GridPoint leftBottomCorner  = origin - rPoint;
  const GridPoint rightTopCorner = origin + rPoint;
  
  //if(leftBottomCorner < origin && origin < rightTopCorner)
  if(leftBottomCorner <= rightTopCorner)
  {
    for(unsigned long i = 0; i < N; ++i)
    {
      if(leftBottomCorner <= particlePositions[i] && particlePositions[i] <= rightTopCorner)
      {
        neighbourPoints.push_back(particlePositions[i]);
      }
    }
  }
  else
  {
    bool doubleConditionsLeftBottom[3];
    bool doubleConditionsRightTop[3];
    for(unsigned long j = 0; j < 3; ++j)
    {
      doubleConditionsLeftBottom[j] = (origin[j] < leftBottomCorner[j]);
      doubleConditionsRightTop[j] = (origin[j] > rightTopCorner[j]);
    }
    for(unsigned long i = 0; i < N; ++i)
    {
      unsigned long j;
      for(j = 0; j < 3; ++j)
      {
        if(doubleConditionsLeftBottom[j] 
            && (
                  (GridPoint::LOWERBOUND <= particlePositions[i][j]
                  && particlePositions[i][j] <= rightTopCorner[j]) 
              || (leftBottomCorner[j] <= particlePositions[i][j]
                  && particlePositions[i][j] <= GridPoint::UPPERBOUND))
          )
        {
        }
        else if(doubleConditionsRightTop[j]
            && (
                  (leftBottomCorner[j] <= particlePositions[i][j]
                  && particlePositions[i][j] <= GridPoint::UPPERBOUND) 
              || (GridPoint::LOWERBOUND <= particlePositions[i][j]
                  && particlePositions[i][j] <= rightTopCorner[j]))
          )
        {
        }
        else if(leftBottomCorner[j] <= particlePositions[i][j]
                  && particlePositions[i][j] <= rightTopCorner[j])
        {
        }
        else
        {
          break;
        }

      }
      if(j == 3)
      {
         neighbourPoints.push_back(particlePositions[i]);
      }
    }
  }
  for (std::vector<GridPoint>::iterator it=neighbourPoints.begin(); it!=neighbourPoints.end();)
  {
    if(origin.distanceTo(*it) > radius)
    {
      it = neighbourPoints.erase(it);
    }
    else 
    {
      ++it;
    }
  }
}

GridPointDouble ParticlesState::getForceOfParticles(unsigned long i, unsigned long j, const double lennardJonesA, const double lennardJonesB)
{
  const double distance = particlePositions[i].distanceTo(particlePositions[j]);
  if(distance <= 0.0)
  {
    std::cout << distance << std::endl;
  }
  assert(distance > 0.0);
  const double distance2 = distance * distance;
  const double distance4 = distance2 * distance2;
  const double distance6 = distance4 * distance2;
  const double distance8 = distance4 * distance4;
  const double distance14 = distance6 * distance8;
  const double coeff = lennardJonesA/distance14 - lennardJonesB/distance8;
  GridPoint distVector = (particlePositions[j] - particlePositions[i]);
  //for(int k = 0; k < 3; ++k)
  //{
  //  distVector[k] = (double) (particlePositions[j][k] - particlePositions[i][k]);
  //}

  GridPointDouble force = GridPointDouble();
  for(int k = 0; k < 3; ++k)
  {
    force[k] = (coeff * distVector[k]);
  }
  return force;
}

GridPointDouble ParticlesState::getAcceleration(unsigned long particle, std::vector<unsigned long> *masses,const double lennardJonesA, const double lennardJonesB)
{
  GridPointDouble acceleration = GridPointDouble();
  for(unsigned long i = 0; i < N; ++i)
  {
    if(i != particle)
    {
      acceleration = acceleration - getForceOfParticles(particle, i, lennardJonesA, lennardJonesB);
    }
  }
  for(int i = 0; i < 3; ++i)
  {
    acceleration[i] =  acceleration[i] / (*masses)[particle];
  }
  return acceleration;
}

double ParticlesState::getTotalKinEnergy(std::vector<unsigned long> *masses, ParticlesState *previousPState)
{
  double totalKinEnergy = 0.0;
  for(unsigned long i = 0; i < N; ++i)
  {
    totalKinEnergy +=  0.5 * (*masses)[i] * (particlePositions[i]-(*previousPState)[i]).getLengthSquare(); //<< "\t";
  }
  return totalKinEnergy;
}

double ParticlesState::getPotential(unsigned long i, unsigned long j, const double lennardJonesA, const double lennardJonesB)
{
  const double distance = particlePositions[i].distanceTo(particlePositions[j]);
  const double distance2 = distance * distance;
  const double distance4 = distance2 * distance2;
  const double distance6 = distance4 * distance2;
  const double distance12 = distance6 * distance6;
  const double energy = lennardJonesA/distance12 - lennardJonesB/distance6;
  return energy;
}

double ParticlesState::getTotalPotEnergy(ParticlesState *previousPState, const double lennardJonesA, const double lennardJonesB)
{
  double totalPotEnergy = 0.0;
  for(unsigned long i = 0; i < N; ++i)
  {
    for(unsigned long j = i + 1; j < N; ++j)
    {
      totalPotEnergy += getPotential(i, j, lennardJonesA, lennardJonesB) - previousPState->getPotential(i, j, lennardJonesA, lennardJonesB); //<< "\t";
      if(totalPotEnergy != totalPotEnergy)
      {
        std::cout << iteration << " " <<  i << " " << j << std::endl;
        exit(1);
      }
    }
  }
  return 2.0 * totalPotEnergy;
}


double ParticlesState::getMiddleDistance()
{
  double distance = 0.0;
  for(unsigned long i = 0; i < N; ++i)
  {
    for(unsigned long j = i+1; j < N; ++j)
    {
      distance += particlePositions[i].distanceTo(particlePositions[j]);
    }
  }
  return distance / ((N-1)*N*0.5);
}

void ParticlesState::writeToFile(std::string outputDir, unsigned long i)
{
  std::stringstream filePathStream;
  filePathStream << outputDir << i << ".dat";
  std::fstream f;
  f.open(filePathStream.str().c_str(), std::fstream::in | std::fstream::out | std::fstream::trunc);
  f << "x\ty\tz" << std::endl;
  for(unsigned long i = 0; i < N; ++i)
  {
    f << particlePositions[i].getX() << "\t" << particlePositions[i].getY();
    f << "\t" << particlePositions[i].getZ(); //<< "\t";

    //f << "\t" << points[i].energy << "\t";
    //f << points[i].mass;
    f << std::endl;
  }
  f.close();
}

GridPoint & ParticlesState::operator [](unsigned long i)
{
  return particlePositions[i];
}

