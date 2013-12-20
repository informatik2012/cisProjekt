#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "simulation.hpp"
#include <string>

class Settings
{
  public:
    ~Settings();
    static double strToDouble( const std::string& s );
    static long strToLong( const std::string& s );
    static Settings *getSettingsFromFile(std::string filePath);
    Simulation *simulation;
};

#endif
