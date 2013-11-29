

class GridPoint
{
  public:
    GridPoint();
    GridPoint(long x,long y, long z);
    GridPoint(GridPoint posStart, GridPoint posEnd);
  private:
    long x,y,z;
}
