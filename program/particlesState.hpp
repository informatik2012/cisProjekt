#ifndef PARTICLESSTATE_HPP
#define PARTICLESSTATE_HPP

#include <vector>
#include "gridPoint.hpp"
#include "particle.hpp"

class ParticlesState
{
  public:
    ParticlesState(unsigned long N);
    ~ParticlesState();
    std::vector<GridPoint> getNeightbours(GridPoint origin, long radius);
    GridPoint & operator [](unsigned long i);
    const unsigned long N;
  private:
    unsigned long iteration;
    GridPoint *particlePositions;
};

#endif
