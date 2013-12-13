#include "particlesState.hpp"
GridPoint ONEPOINT(1,1,1);

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
      if(leftBottomCorner <= particles[i].position && particles[i].position <= rightTopCorner)
      {
        neighbourPoints.push_back(particles[i].position);
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
                  (GridPoint::LOWERBOUND <= (particles[i].position)[j]
                  && (particles[i].position)[j] <= rightTopCorner[j]) 
              || (leftBottomCorner[j] <= (particles[i].position)[j]
                  && (particles[i].position)[j] <= GridPoint::UPPERBOUND))
          )
        {
        }
        else if(doubleConditionsRightTop[j]
            && (
                  (leftBottomCorner[j] <= (particles[i].position)[j]
                  && (particles[i].position)[j] <= GridPoint::UPPERBOUND) 
              || (GridPoint::LOWERBOUND <= (particles[i].position)[j]
                  && (particles[i].position)[j] <= rightTopCorner[j]))
          )
        {
        }
        else if(leftBottomCorner[j] <= (particles[i].position)[j]
                  && (particles[i].position)[j] <= rightTopCorner[j])
        {
        }
        else
        {
          break;
        }

      }
      if(j == 3)
      {
         neighbourPoints.push_back(particles[i].position);
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

