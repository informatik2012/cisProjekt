#ifndef PARTICLESSTATE_HPP
#define PARTICLESSTATE_HPP

#include <vector>
#include "gridPoint.hpp"
#include "gridPointDouble.hpp"
#include "particle.hpp"

class ParticlesState
{
  public:
    ParticlesState(unsigned long N,unsigned long iteration = 0);
    ParticlesState(unsigned long N, GridPoint bottomLeft, GridPoint topRight, unsigned long iteration = 0);
    ParticlesState(std::vector<GridPoint> *particlePositions, unsigned long iteration = 0);
    ParticlesState(ParticlesState *first, std::vector<unsigned long> *velocities);
    ~ParticlesState();
    unsigned long nextIt();

    std::vector<GridPoint> getNeightbours(GridPoint origin, long radius);
 
    GridPointDouble getForceOfParticles(unsigned long i, unsigned long j, const double lennardJonesA, const double lennardJonesB);
    GridPointDouble getAcceleration(unsigned long particle, const double lennardJonesA, const double lennardJonesB);

    double getPotential(unsigned long i, unsigned long j, const double lennardJonesA, const double   lennardJonesB);

    double getTotalPotEnergy(ParticlesState *previousParticlesState, const double lennardJonesA, const double lennardJonesB);


    double getMiddleDistance();
    void writeToFile(std::string file, unsigned long i);


    double getTotalKinEnergy(std::vector<unsigned long> *masses, ParticlesState *previousParticlesState);

    GridPoint & operator [](unsigned long i);
    unsigned long N;
//    static const double lennardJonesA;
//    static const double lennardJonesB;
  private:
    unsigned long iteration;
    GridPoint *particlePositions;
};

#endif
