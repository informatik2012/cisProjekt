#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml/rapidxml.hpp"
#include "random.hpp"
#include "gridPoint.hpp"
#include "particlesState.hpp"
#include "tests.hpp"
#include "settings.hpp"

using namespace rapidxml;
using namespace std;

int main( int argc, const char* argv[] )
{
  bool doTests = true;
  Random::init((unsigned long)time(NULL) * getpid());
  GridPoint p1(0,0,0);
  GridPoint p2(1,2,3);
  GridPoint p3(p1,p2);
  ParticlesState myState(1000);
  /*
  for(unsigned long i = 0; i < myState.N; ++i)
  {
    cout << "y: " << myState[i][1] << endl;
  }*/
  if(doTests)
  {
    doChecks();
  }
  Settings *settings = Settings::getSettingsFromFile(argv[1]);
  settings->simulation->runSimulation();
  //delete settings;
}


