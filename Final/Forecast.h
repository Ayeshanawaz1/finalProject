#pragma once
#include "City.h"
#include "Weather.h"
#include <vector>
#include <string>

using namespace std;

class Forecast {
private:
    City city;
    vector<Weather> weather;

public:
    Forecast(string cityName = "", string countryName = "");

    void addWeather(const Weather& w);
    void displayForecastByWeek();
    void displayForecastByDate(string day, string month, string year);
    void displayHourlyForecast(string day, string month, string year);
};
