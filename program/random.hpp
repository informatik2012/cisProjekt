#ifndef RANDOM_HPP
#define RANDOM_HPP

namespace Random
{
    void init(unsigned long seed);
    long getLong(long min, long max);
    double getRandomPhi();
    double getRandomTheta();
};

#endif
