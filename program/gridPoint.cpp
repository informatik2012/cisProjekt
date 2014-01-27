#include <iostream>
#include <stdio.h>
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

GridPoint::GridPoint(GridPoint oldPosition, unsigned long velocity)
{
  double phi   = Random::getRandomPhi();
  double theta = Random::getRandomTheta();
  double const velocityD = (double) velocity;
  double const sinTheta = sin(theta);
  GridPoint velocityVec(
      round((long) velocityD * sinTheta * cos(phi)),
      round((long) velocityD * sinTheta * sin(phi)),
      round((long) velocityD * cos(theta))
        );
  oldPosition =  oldPosition + velocityVec;
 
  positions[0] = oldPosition[0];
  positions[1] = oldPosition[1];
  positions[2] = oldPosition[2];
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

double GridPoint::distanceTo(const GridPoint point)
{
  //unsigned long differences[3];
  double result = 0;
  for(unsigned long i = 0; i < 3; ++i)
  {
    unsigned long difference; 
    difference = (positions[i] >= point[i]) ?
                        positions[i] - point[i] 
                      : point[i] - positions[i];
    if(GridPoint::RANGE / 2 + 1 < difference)
    {
      // eventuell +/-1
      difference =  GridPoint::RANGE - difference; 
    }

    result += (double) difference * (double) difference;
  }

  result = round(sqrt(result));
  if(result <= 0.0) result = 1.0;
  assert(result > 0.0);
  assert(result <= (double) GridPoint::RANGE);
  if((unsigned long) result <= 0.0)
  {
    std::cout << result;
  }
  return result;
}

double GridPoint::getLengthSquare()
{
  double result = 0.0;
  for(unsigned int i = 0; i < 3; ++i)
  {
    result += ((double) positions[i]) * ((double) positions[i]);
  }
  return result;
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
  for(int i = 0; i < 3; ++i)
  {
    if(a[i] > b[i]) return false;
  }
  return true;
}

bool operator<(GridPoint const & a, GridPoint const & b)
{
  for(int i = 0; i < 3; ++i)
  {
    if(a[i] >= b[i]) return false;
  }
  return true;
}

bool operator>(GridPoint const & a, GridPoint const & b)
{
  for(int i = 0; i < 3; ++i)
  {
    if(a[i] <= b[i]) return false;
  }
  return true;
}


bool operator>=(GridPoint const & a, GridPoint const & b)
{
  for(int i = 0; i < 3; ++i)
  {
    if(a[i] < b[i]) return false;
  }
  return true;
}

bool operator==(GridPoint const & a, GridPoint const & b)
{
  for(int i = 0; i < 3; ++i)
  {
    if(a[i] != b[i]) return false;
  }
  return true;
}

GridPoint operator+(GridPoint const & a, long const & b)
{
  GridPoint result = a;
  long maxMb = GridPoint::UPPERBOUND - b;
  for(int i = 0; i < 3; ++i)
  {
    result.addToComponent(i, b);
  }
  return result;
}

GridPoint operator-(GridPoint const & a, long const & b)
{
  GridPoint result = a;
  long minPb = GridPoint::LOWERBOUND + b;
  for(int i = 0; i < 3; ++i)
  {
    result.addToComponent(i, -b);
  }
  return result;
}

GridPoint operator/(GridPoint const & a, long const & b)
{
  GridPoint result = a;
  assert(b != 0);
  for(int i = 0; i < 3; ++i)
  {
    result[i] /= b;
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
  for(int i = 0; i < 3; ++i)
  {
    result[i] *= b;
    //assert((b > 0 && result[i] >= a[i]) || (b < 0 &&  result[i] <= a[i]));
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
  for(int i = 0; i < 3; ++i)
  {
    result.addToComponent(i, b[i]);
  }
  return result;
}

GridPoint operator+(GridPoint const & a, GridPointDouble const & b)
{
  GridPoint result = a;
  for(int i = 0; i < 3; ++i)
  {
    result.addToComponent(i, (long) b[i]);
  }
  return result;
}

GridPoint operator-(GridPoint const & a, GridPoint const & b)
{
  GridPoint result = a;
  for(int i = 0; i < 3; ++i)
  {
    result.addToComponent(i, -b[i]);
  }
  return result;
}
std::ostream& operator<<(std::ostream& os, const GridPoint& point)
{
  os << "x:" << point[0] << ", y: " << point[1] << ", z: " << point[2] << std::endl;
  return os;
}
