#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "simulation.hpp"
#include "gridPoint.hpp"
#include <vector>
#include <string>

class Settings
{
  public:
    ~Settings();
    static double strToDouble( const std::string& s );
    static long strToLong( const std::string& s );
    
    template <typename Type> // this is the template parameter declaration
    static void addNTimes(std::vector<Type> *vector, Type value, unsigned long times);


    static void addParticles(std::vector<GridPoint> *particlePositions, std::vector<unsigned long> *masses, std::vector<unsigned long> *velocities, GridPoint *middle, GridPoint *lengthes, unsigned long mass, unsigned long velocity, unsigned long N);

    static Settings *getSettingsFromFile(std::string filePath);
    Simulation *simulation;
};

#endif
