#include <assert.h>
#include <iostream>
#include "tests.hpp"
#include "gridPoint.hpp"

void doChecks()
{
  checkBoundaryConditions();
  checkGetDistanceBetweenPoints();
}

void checkBoundaryConditions()
{
  GridPoint p(GridPoint::UPPERBOUND, GridPoint::LOWERBOUND, GridPoint::UPPERBOUND);
  p.addToComponent(0,1);
  assert(p[0] == GridPoint::LOWERBOUND);

  p.addToComponent(1,-1);
  assert(p[1] == GridPoint::UPPERBOUND);

  p.addToComponent(2,-10);
  p.addToComponent(2,10);
  assert(p[2] == GridPoint::UPPERBOUND);

  p.addToComponent(2,10);
  p.addToComponent(2,-10);
  assert(p[2] == GridPoint::UPPERBOUND);


  p.addToComponent(2,1);
  assert(p[2] == GridPoint::LOWERBOUND);

  p.addToComponent(2,10);
  p.addToComponent(2,-10);
  assert(p[2] == GridPoint::LOWERBOUND);

  p.addToComponent(2,-10);
  p.addToComponent(2,10);
  assert(p[2] == GridPoint::LOWERBOUND);

}


void checkGetDistanceBetweenPoints()
{
 GridPoint p1(GridPoint::UPPERBOUND,GridPoint::LOWERBOUND + 9,GridPoint::UPPERBOUND);
 GridPoint p2(GridPoint::LOWERBOUND + 9,GridPoint::UPPERBOUND, GridPoint::UPPERBOUND - 5);
 assert(p1.distanceTo(p2) == 15);
}
 
