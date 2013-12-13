#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "gridPoint.hpp"

class Particle
{
  public:
    Particle(GridPoint position, int mass);
    GridPoint position;
    int mass;
};

#endif
