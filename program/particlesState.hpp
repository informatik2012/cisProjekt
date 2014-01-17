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
 
    GridPoint getForceOfParticles(unsigned long i, unsigned long j, const double lennardJonesA, const double lennardJonesB);
    GridPoint getAcceleration(unsigned long particle, const double lennardJonesA, const double lennardJonesB);
    void writeToFile(std::string file, unsigned long i);

    GridPoint & operator [](unsigned long i);
    unsigned long N;
//    static const double lennardJonesA;
//    static const double lennardJonesB;
  private:
    unsigned long iteration;
    GridPoint *particlePositions;
};

#endif
