#include "particlesState.hpp"
GridPoint ONEPOINT(1,1,1);

const double ParticlesState::lennardJonesA = 12.0;
const double ParticlesState::lennardJonesB = 12.0;


ParticlesState::ParticlesState(unsigned long N, unsigned long iteration):N(N),iteration(iteration)
{
  particlePositions = new GridPoint[N];
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
ParticlesState::ParticlesState(ParticlesState *first, unsigned long constVelocity)
  :N(first->N),iteration(first->nextIt())
{
  particlePositions = new GridPoint[N];
  for(long i = 0; i < N; ++i)
  {
    bool alreadyInserted;
    do
    {
      alreadyInserted = false;
      particlePositions[i] = GridPoint(particlePositions[i], constVelocity);
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
  if(particlePositions != NULL)
  {
    delete[] particlePositions;
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

GridPoint ParticlesState::getForceOfParticles(unsigned long i, unsigned long j)
{
  const long distance = particlePositions[i].distanceTo(particlePositions[j]);
  const long distance2 = distance * distance;
  const long distance4 = distance2 * distance2;
  const long distance6 = distance4 * distance2;
  const long distance8 = distance4 * distance2;
  const long distance14 = distance6 * distance8;
  const double coeff = lennardJonesA/distance14 - lennardJonesB/distance8;
  const GridPoint distVector = (particlePositions[j] - particlePositions[i]);
  GridPoint force = GridPoint();
  for(int k = 0; k < 3; ++k)
  {
    force[k] = (long) (coeff * distVector[i]);
  }
  return force;
}

GridPoint ParticlesState::getAcceleration(unsigned long particle)
{
  GridPoint acceleration = GridPoint();
  for(unsigned long i = 0; i < N; ++i)
  {
    if(i != particle)
    {
      acceleration = acceleration + getForceOfParticles(particle, i);
    }
  }
  return GridPoint(0,0,0);
}


GridPoint & ParticlesState::operator [](unsigned long i)
{
  return particlePositions[i];
}

