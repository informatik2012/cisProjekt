#ifndef PARTICLESSTATE_HPP
#define PARTICLESSTATE_HPP

#include <vector>
#include "gridPoint.hpp"
#include "particle.hpp"

class ParticlesState
{
  public:
    ParticlesState(int OBJECT);
    std::vector<GridPoint> getNeightbours(GridPoint origin, long radius);
  private:
    unsigned long iteration;
    unsigned long N;
    GridPoint *particlePositions;
};

#endif
