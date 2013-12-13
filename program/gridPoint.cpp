#include <limits.h>
#include <math.h>
#include <assert.h>
#include "gridPoint.hpp"
#include "random.hpp"

const long GridPoint::LOWERBOUND = -9223372036854775807;
const long GridPoint::UPPERBOUND =  9223372036854775807;
const unsigned long GridPoint::RANGE = (unsigned long) GridPoint::UPPERBOUND - GridPoint::LOWERBOUND + 1; 

GridPoint GridPoint::ONEPOINT(1,1,1);

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

long GridPoint::distanceTo(const GridPoint point)
{
  //unsigned long differences[3];
  double result = 0;
  for(unsigned long i = 0; i < 3; ++i)
  {
    double difference; 
    difference = (positions[i] >= point[i]) ?
                        positions[i] - point[i] 
                      : point[i] - positions[i];
    if(GridPoint::RANGE / 2 + 1 < difference)
    {
      // eventuell +/-1
      difference = GridPoint::RANGE - difference + 1; 
    }

    result += difference * difference;
  }
  result = sqrt((double) result);

  return (result > (double) UPPERBOUND?UPPERBOUND:(long) result);
}
void GridPoint::addToComponent(const unsigned long compIndex, const long summand)
{
  if(UPPERBOUND >= summand && summand >= 0)
  {
    const long maxMs = GridPoint::UPPERBOUND - summand;
    if(maxMs >= positions[compIndex])
    {
      positions[compIndex] += summand;
    }
    else
    {
      positions[compIndex] = GridPoint::LOWERBOUND - maxMs + (positions[compIndex] - 1);
    } 
  }
  else if(LOWERBOUND <= summand && summand < 0)
  {
    const long maxMs = GridPoint::LOWERBOUND - summand;
    if(maxMs <= positions[compIndex])
    {
      positions[compIndex] += summand;
    }
    else
    {
      positions[compIndex] = GridPoint::UPPERBOUND - maxMs + (positions[compIndex] + 1);
    } 
  }
}

bool operator<=(GridPoint const & a, GridPoint const & b)
{
  for(int i = 1; i < 3; ++i)
  {
    if(a[i] > b[i]) return false;
  }
  return true;
}

bool operator<(GridPoint const & a, GridPoint const & b)
{
  for(int i = 1; i < 3; ++i)
  {
    if(a[i] >= b[i]) return false;
  }
  return true;
}

bool operator>(GridPoint const & a, GridPoint const & b)
{
  for(int i = 1; i < 3; ++i)
  {
    if(a[i] <= b[i]) return false;
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
  long maxMb = GridPoint::UPPERBOUND - b;
  for(int i = 1; i < 3; ++i)
  {
    result.addToComponent(i, b);
  }
  return result;
}

GridPoint operator-(GridPoint const & a, long const & b)
{
  GridPoint result = a;
  long minPb = GridPoint::LOWERBOUND + b;
  for(int i = 1; i < 3; ++i)
  {
    result.addToComponent(i, -b);
  }
  return result;
}

GridPoint operator*(GridPoint const & a, long const & b)
{
  GridPoint result = a;
  if(b == 0)
  {
    return GridPoint(0,0,0);
  }
  assert(GridPoint::UPPERBOUND >= fabs(b));
  for(int i = 1; i < 3; ++i)
  {
    result[i] *= b;
    assert((b > 0 && result[i] >= a[i]) || (b < 0 &&  result[i] <= a[i]));
  }
  return result;
}

GridPoint operator*(long const & a, GridPoint const & b)
{
  return b * a;
}

GridPoint operator+(GridPoint const & a, GridPoint const & b)
{
  GridPoint result = a;
  for(int i = 1; i < 3; ++i)
  {
    result.addToComponent(i, b[i]);
  }
}


GridPoint operator-(GridPoint const & a, GridPoint const & b)
{
  GridPoint result = a;
  for(int i = 1; i < 3; ++i)
  {
    result.addToComponent(i, -b[i]);
  }
}
