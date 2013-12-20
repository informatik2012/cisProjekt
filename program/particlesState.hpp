#ifndef PARTICLESSTATE_HPP
#define PARTICLESSTATE_HPP

#include <vector>
#include "gridPoint.hpp"
#include "particle.hpp"

class ParticlesState
{
  public:
    ParticlesState(unsigned long N,unsigned long iteration = 0);
    ParticlesState(unsigned long N, GridPoint bottomLeft, GridPoint topRight, unsigned long iteration = 0);
    ParticlesState(ParticlesState *first, unsigned long constVelocity);
    ~ParticlesState();
    unsigned long nextIt();

    std::vector<GridPoint> getNeightbours(GridPoint origin, long radius);
    GridPoint & operator [](unsigned long i);
    unsigned long N;
  private:
    unsigned long iteration;
    GridPoint *particlePositions;
};

#endif
