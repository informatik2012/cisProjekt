#ifndef RANDOM_HPP
#define RANDOM_HPP

namespace Random
{
    void init(unsigned int seed);
    long getLong(long min, long max);
    double getRandomPhi();
    double getRandomTheta();
};

#endif
