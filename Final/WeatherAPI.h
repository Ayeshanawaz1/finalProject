#pragma once
#include <iostream>
#include <string>
using namespace std;

class WeatherAPI {
public:
    static std::string fetchWeatherData(std::string& cityName, std::string& countryName);
};
