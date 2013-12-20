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
#include "particlesState.hpp"

using namespace rapidxml;
using namespace std;

Settings::~Settings()
{
  if(simulation != NULL)
  {
    //delete simulation;
  }
}

double Settings::strToDouble( const std::string& s )
{
  std::istringstream i(s);
  double x;
  if (!(i >> x))
    return 0;
  return x;
} 


long Settings::strToLong( const std::string& s )
{
  std::istringstream i(s);
  long x;
  if (!(i >> x))
    return 0;
  return x;
} 

Settings *Settings::getSettingsFromFile(std::string filePath)
{
  Settings *settings = new Settings();
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

  xml_node<> * simulation_node = root_node->first_node("SIMULATION");
  xml_node<> * steps_node = simulation_node->first_node("STEPS");
  long steps = strToLong(steps_node->value());
  // Iterate over the objects
  for (xml_node<> * object_node = root_node->first_node("OBJECTS"); object_node; object_node = object_node->next_sibling())
  {
    // Interate over the rectangles 
    for(xml_node<> * rectangle_node = object_node->first_node("RECTANGLE"); rectangle_node; rectangle_node = rectangle_node->next_sibling())
    {
      
      printf("Rectangle title: %s. \n ",
          (rectangle_node->first_node("TITLE"))->value());
      xml_node<> * location_node = rectangle_node->first_node("LOCATION");
      xml_node<> * middlepoint_node = location_node->first_node("MIDDLEPOINT");
      xml_node<> * lengths_node = location_node->first_node("LENGTHS");

      string xStr = middlepoint_node->first_node("X")->value();
      string yStr = middlepoint_node->first_node("Y")->value();
      string zStr = middlepoint_node->first_node("Z")->value();
      GridPoint middle(strToLong(xStr), strToLong(yStr), strToLong(zStr));

      xStr = lengths_node->first_node("X")->value();
      yStr = lengths_node->first_node("Y")->value();
      zStr = lengths_node->first_node("Z")->value();
      GridPoint lengthes(strToLong(xStr), strToLong(yStr), strToLong(zStr));

      xml_node<> * particles_node = rectangle_node->first_node("PARTICLES");
      
      GridPoint bottomLeft = middle - (lengthes / 2);

      GridPoint topRight = middle + (lengthes / 2);

      assert(bottomLeft < topRight);

      if(particles_node)
      {
        long count = strToLong(particles_node->first_node("COUNT")->value());
        ParticlesState *first = new ParticlesState(count, bottomLeft, topRight); 
        ParticlesState *second;
        /*
        GridPoint * particles = new GridPoint[count];
        for(long i = 0; i < count; ++i)
        {
          bool alreadyInserted;
          do
          {
            alreadyInserted = false;
            particles[i] = GridPoint(bottomLeft, topRight);
            for(long j; j < i; ++j)
            {
              if(particles[j] == particles[i])
              {
                alreadyInserted = true;
                break;
              }
            }
          } while(alreadyInserted);
          
          //cout << particles[i];
        }
        */
        xml_node<> * velocity_node = particles_node->first_node("VELOCITY");
        long velocity = strToLong(velocity_node->value());

        for (xml_attribute<> *attr = velocity_node->first_attribute();
            attr; attr = attr->next_attribute())
        {
          if(strcmp(attr->name(),"TYPE") == 0)
          {
            if(strcmp(attr->value(),"constant") == 0)
            {
              second = new ParticlesState(first, velocity);
            }
            break;
          }
        }
        if(second != NULL)
        {
          settings->simulation = new Simulation(first, second, steps);
        }
        //delete first;
      }
      
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
  return settings;
}
