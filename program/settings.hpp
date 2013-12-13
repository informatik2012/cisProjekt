#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>

class Settings
{
  public:
    static double strToDouble( const std::string& s );
    static Settings getSettingsFromFile(std::string filePath);
};


#endif
