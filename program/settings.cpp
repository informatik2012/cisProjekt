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
  xml_node<> * lennardJonesA_node = simulation_node->first_node("LENNARDJONESA");
  double lennardJonesA = -1.0;
  if(lennardJonesA_node != NULL)
  {
    lennardJonesA = strToDouble(lennardJonesA_node->value());
  }
  xml_node<> * lennardJonesB_node = simulation_node->first_node("LENNARDJONESB");
  double lennardJonesB = -1.0;
  if(lennardJonesB_node != NULL)
  {
    lennardJonesB = strToDouble(lennardJonesB_node->value());
  }

  xml_node<> * outputDir_node = simulation_node->first_node("OUTPUTDIR");
  std::string outputDir;
  if(outputDir_node != NULL)
  {
    outputDir = outputDir_node->value();
  }
  else
  {
    outputDir = "";
  }
  // Iterate over the objects
  for (xml_node<> * object_node = root_node->first_node("OBJECTS"); object_node != 0; object_node = object_node->next_sibling())
  {
    // Interate over the rectangles 
    for(xml_node<> * rectangle_node = object_node->first_node("RECTANGLE"); rectangle_node != 0; rectangle_node = rectangle_node->next_sibling())
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

      if(particles_node != NULL)
      {
        long count = strToLong(particles_node->first_node("COUNT")->value());
        ParticlesState *first = new ParticlesState(count, bottomLeft, topRight); 
        ParticlesState *second = NULL;
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
          if(lennardJonesA >= 0.0 && lennardJonesB >= 0.0)
          {
            settings->simulation = new Simulation(first, second, steps, outputDir, lennardJonesA, lennardJonesB);
          }
          else
          {
            settings->simulation = new Simulation(first, second, steps, outputDir);
          }
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
    ParticlesState *first = NULL;
    ParticlesState *second = NULL;
    for (xml_node<> * particles_node = object_node->first_node("PARTICLES"); particles_node != 0; particles_node = particles_node->next_sibling())
    {
      unsigned long pointsCount = 0;
      for (xml_node<> * positions_node = particles_node->first_node("POSITIONS"); positions_node != 0; positions_node = positions_node->next_sibling(positions_node->name()))
      {

        xml_node<> *x_node;
        xml_node<> *y_node;
        xml_node<> *z_node;
        for (x_node = positions_node->first_node("X"),
y_node = positions_node->first_node("Y"),
z_node = positions_node->first_node("Z");
             x_node != 0 && y_node != 0 && z_node != 0;
             x_node = x_node->next_sibling(x_node->name()),
             y_node = y_node->next_sibling(y_node->name()),
             z_node = z_node->next_sibling(z_node->name())
             )
        {
          ++pointsCount;
        }

        first = new ParticlesState(pointsCount, 0);
        unsigned long i = 0;
        for (x_node = positions_node->first_node("X"),
y_node = positions_node->first_node("Y"),
z_node = positions_node->first_node("Z");
             x_node != 0 && y_node != 0 && z_node != 0;
             x_node = x_node->next_sibling(x_node->name()),
             y_node = y_node->next_sibling(y_node->name()),
             z_node = z_node->next_sibling(z_node->name())
             )
        {
          string xStr = x_node->value();
          string yStr = y_node->value();
          string zStr = z_node->value();
          
          (*first)[i] = GridPoint(strToLong(xStr), strToLong(yStr), strToLong(zStr));
          ++i;
        }
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

      }

    }
    //cout << endl;
    if(second != NULL)
    {
      if(lennardJonesA >= 0.0 && lennardJonesB >= 0.0)
      {
        settings->simulation = new Simulation(first, second, steps, outputDir, lennardJonesA, lennardJonesB);
      }
      else
      {
        settings->simulation = new Simulation(first, second, steps, outputDir);
      }
    }
  }
  return settings;
}
