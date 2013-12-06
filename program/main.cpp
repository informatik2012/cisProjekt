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

using namespace rapidxml;
using namespace std;

int main( int argc, const char* argv[] )
{
  bool doTests = true;
  Random::init(100);
  GridPoint p1(0,0,0);
  GridPoint p2(1,2,3);
  GridPoint p3(p1,p2);
  if(doTests)
  {
    doChecks();
  }
  cout << "Parsing firstworld.xml..." << endl;
  xml_document<> doc;
  xml_node<> * root_node;
  // Read the xml file into a vector
  ifstream theFile ("firstWorld.xml");

  vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
  buffer.push_back('\0');
  // Parse the buffer using the xml file parsing library into doc
  doc.parse<0>(&buffer[0]);
  // Find our root node
  root_node = doc.first_node("WORLD");
  // Iterate over the brewerys
  for (xml_node<> * object_node = root_node->first_node("OBJECTS"); object_node; object_node = object_node->next_sibling())
  {
    // Interate over the beers
    for(xml_node<> * rectangle_node = object_node->first_node("RECTANGLE"); rectangle_node; rectangle_node = rectangle_node->next_sibling())
    {
      printf("Rectangle title: %s. ",
          (rectangle_node->first_node("TITLE"))->value());
      xml_node<> * location_node = rectangle_node->first_node("LOCATION");
      xml_node<> * middlepoint_node = location_node->first_node("MIDDLEPOINT");
      printf("Middlepoint coordinates: %s, %s, %s. ",
          middlepoint_node->first_node("X")->value(),
          middlepoint_node->first_node("Y")->value(),
          middlepoint_node->first_node("Z")->value());
    }
    cout << endl;
  }
}


