#ifndef GRIDPOINT_HPP
#define GRIDPOINT_HPP

class GridPoint
{
  public:
    GridPoint();
    GridPoint(long x,long y, long z);
    GridPoint(GridPoint posStart, GridPoint posEnd);
    long getX();
    long getY();
    long getZ();
    long operator [](int i) const;
    long & operator [](int i);
  private:
    long positions[3];

};
#endif
