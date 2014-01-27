#ifndef GRIDPOINTDOUBLE_HPP
#define GRIDPOINTDOUBLE_HPP

#include <iostream>

class GridPointDouble
{
  public:
    GridPointDouble();
    GridPointDouble(double x, double y, double z);

    double getX();
    double getY();
    double getZ();
    double operator [](int i) const;
    double & operator [](int i);

  private:
    double positions[3];
};



GridPointDouble operator+(GridPointDouble const & a, GridPointDouble const & b);
GridPointDouble operator-(GridPointDouble const & a, GridPointDouble const & b);

std::ostream& operator<<(std::ostream& os, const GridPointDouble& point);

#endif
