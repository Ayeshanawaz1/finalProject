#pragma once
#include <string>
#include <iostream>
#include "WeatherForecastSystem.h"
using namespace std;

class WeatherSystem {
private:
    HistoryLogger logger;

public:
    Forecast loadData(string cityName, string countryName);
    void logHistory(const string& userInput, const string& forecastResult);
};
