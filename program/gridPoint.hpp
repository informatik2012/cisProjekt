#ifndef GRIDPOINT_HPP
#define GRIDPOINT_HPP

#include <iostream>

class GridPoint
{
  public:
    GridPoint();
    GridPoint(long x,long y, long z);
    GridPoint(GridPoint posStart, GridPoint posEnd);
    GridPoint(GridPoint oldPosition, unsigned long velocity);

    long getX();
    long getY();
    long getZ();
    long operator [](int i) const;
    long & operator [](int i);

    void addToComponent(const unsigned long compIndex, const long summand);
    long distanceTo(const GridPoint point);
    double getLengthSquare();

    static GridPoint ONEPOINT;
    static const long LOWERBOUND;
    static const long UPPERBOUND;
    static const unsigned long RANGE;
  private:
    long positions[3];

};


bool operator<=(GridPoint const & a, GridPoint const & b);
bool operator>=(GridPoint const & a, GridPoint const & b);
bool operator<(GridPoint const & a, GridPoint const & b);
bool operator>(GridPoint const & a, GridPoint const & b);
bool operator==(GridPoint const & a, GridPoint const & b);

GridPoint operator+(GridPoint const & a, long const & b);
GridPoint operator-(GridPoint const & a, long const & b);
GridPoint operator*(GridPoint const & a, long const & b);
GridPoint operator/(GridPoint const & a, long const & b);

GridPoint operator*(long const & a, GridPoint const & b);

GridPoint operator+(GridPoint const & a, GridPoint const & b);
GridPoint operator-(GridPoint const & a, GridPoint const & b);

std::ostream& operator<<(std::ostream& os, const GridPoint& point);


#endif
