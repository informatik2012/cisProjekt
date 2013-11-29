#include <limits.h>
#include "gridPoint.hpp"
#include "random.hpp"

GridPoint::GridPoint()
{
  positions[0] = 0;
  positions[1] = 0;
  positions[2] = 0;
}

GridPoint::GridPoint(long x,long y, long z)
{
  positions[0] = x;
  positions[1] = y;
  positions[2] = z;
}
GridPoint::GridPoint(GridPoint posStart, GridPoint posEnd)
{
  for(int i = 0; i < 3; ++i)
  {
    positions[i] = Random::getLong(posStart[i], posEnd[i]);
  }
}

long GridPoint::getX()
{
  return positions[0];
}

long GridPoint::getY()
{
  return positions[1];
}

long GridPoint::getZ()
{
  return positions[2];
}

long GridPoint::operator [](int i) const
{
  return positions[i];
}

long & GridPoint::operator [](int i)
{
  return positions[i];
}

bool operator<=(GridPoint const & a, GridPoint const & b)
{
  for(int i = 1; i < 3; ++i)
  {
    if(a[i] > b[i]) return false;
  }
  return true;
}

bool operator>=(GridPoint const & a, GridPoint const & b)
{
  for(int i = 1; i < 3; ++i)
  {
    if(a[i] < b[i]) return false;
  }
  return true;
}

GridPoint operator+(GridPoint const & a, long const & b)
{
  GridPoint result = a;
  long maxMb = LONG_MAX - b;
  for(int i = 1; i < 3; ++i)
  {
    if(maxMb >= a[i])
     {
       result[i] = result[i] +  b;
     }
     else
     {
       result[i] = LONG_MIN + maxMb - (a[i] + 1);
     }     
  }
  return result;
}

GridPoint operator-(GridPoint const & a, long const & b)
{
  GridPoint result = a;
  long minPb = LONG_MIN + b;
  for(int i = 1; i < 3; ++i)
  {
    if(minPb <= a[i])
     {
       result[i] = result[i] - b;
     }
     else
     {
       result[i] = LONG_MAX - minPb + (a[i] + 1);
     }     
  }
  return result;
}
