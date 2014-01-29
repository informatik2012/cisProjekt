#include <stdlib.h>     /* srand, rand */
#include <cassert> 
#include "random.hpp"
#include <limits.h>
#define _USE_MATH_DEFINES
#include <math.h>

namespace Random
{
  void init(unsigned long seed)
  {
    srand48(seed);
  }
  long getLong(long min, long max)
  {
    long longToReturn;
    long diff =(unsigned long) ((long long) max - (long long) min); 
    longToReturn = (long) (min + lrand48() % (diff + 1));
    return longToReturn;
  }
  double getRandomPhi()
  {
    return 2*M_PI*(drand48() - 0.5);
  }
  double getRandomTheta()
  {
    return M_PI*drand48();
  }
}

