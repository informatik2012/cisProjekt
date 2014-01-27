#include <iostream>
#include <stdio.h>
#include <limits.h>
#include "gridPointDouble.hpp"

GridPointDouble::GridPointDouble()
{
  positions[0] = 0;
  positions[1] = 0;
  positions[2] = 0;
}

GridPointDouble::GridPointDouble(double x,double y, double z)
{
  positions[0] = x;
  positions[1] = y;
  positions[2] = z;
}

double GridPointDouble::getX()
{
  return positions[0];
}

double GridPointDouble::getY()
{
  return positions[1];
}

double GridPointDouble::getZ()
{
  return positions[2];
}

double GridPointDouble::operator [](int i) const
{
  return positions[i];
}

double & GridPointDouble::operator [](int i)
{
  return positions[i];
}


GridPointDouble operator+(GridPointDouble const & a, GridPointDouble const & b)
{
  GridPointDouble result;
  for(int i = 0; i < 3; ++i)
  {
      result[i] = a[i] + b[i];
  }
  return result;
}


GridPointDouble operator-(GridPointDouble const & a, GridPointDouble const & b)
{
  GridPointDouble result;
  for(int i = 0; i < 3; ++i)
  {
      result[i] = a[i] - b[i];
  }
  return result;
}

std::ostream& operator<<(std::ostream& os, const GridPointDouble& point)
{
  os << "x:" << point[0] << ", y: " << point[1] << ", z: " << point[2] << std::endl;
  return os;
}
