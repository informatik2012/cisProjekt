#include <stdlib.h>     /* srand, rand */
#include <cassert> 
#include "random.hpp"

namespace Random
{
  void init(unsigned int seed)
  {
    srand(seed);
  }
  long getLong(long min, long max)
  {
    long longToReturn;
    long diff =(unsigned long) ((long long) max - (long long) min); 
    longToReturn = (long) (min + lrand48() % (diff + 1));
    return longToReturn;
  }
}

