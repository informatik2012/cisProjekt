#include <sstream>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "settings.hpp"
#include "gridPoint.hpp"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"


using namespace rapidxml;
using namespace std;

double Settings::strToDouble( const std::string& s )
{
  std::istringstream i(s);
  double x;
  if (!(i >> x))
    return 0;
  return x;
} 


Settings Settings::getSettingsFromFile(std::string filePath)
{
  cout << "Parsing firstworld.xml..." << endl;
  
  xml_document<> doc;
  xml_node<> * root_node;
  // Read the xml file into a vector
  ifstream theFile (filePath.c_str());

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
      xml_node<> * lengths_node = location_node->first_node("LENGTHS");

      string xStr = middlepoint_node->first_node("X")->value();
      string yStr = middlepoint_node->first_node("Y")->value();
      string zStr = middlepoint_node->first_node("Z")->value();
      GridPoint middle(strToDouble(xStr), strToDouble(yStr), strToDouble(zStr));


      xStr = lengths_node->first_node("X")->value();
      yStr = lengths_node->first_node("Y")->value();
      zStr = lengths_node->first_node("Z")->value();
      GridPoint halfLength(strToDouble(xStr), strToDouble(yStr), strToDouble(zStr));
      cout << halfLength;
      GridPoint bottomLeft = middle - 0.5 * halfLength;
      cout << bottomLeft;

      GridPoint topRight = middle + 0.5 * halfLength;
      cout << topRight;

      printf("Middlepoint coordinates: %s, %s, %s. ",
          middlepoint_node->first_node("X")->value(),
          middlepoint_node->first_node("Y")->value(),
          middlepoint_node->first_node("Z")->value());
      //StringToDouble(middlepoint_node->first_node("X")->value());

      printf("Lengths: %s, %s, %s. ",
          lengths_node->first_node("X")->value(),
          lengths_node->first_node("Y")->value(),
          lengths_node->first_node("Z")->value());

    }
    cout << endl;
  }

}
