#include "WeatherSystem.h"
#include "WeatherAPI.h"
#include "Forecast.h"
#include "json.hpp"
#include <algorithm>
#include <iostream>
#include <ctime>
using namespace std;
using json = nlohmann::json;

static string toLower(string& str) {
    for (char& ch : str) {
        ch = tolower(ch);
    }
    return str;
}

Forecast WeatherSystem::loadData(string cityName, string countryName) {
    Forecast forecast(cityName, countryName);

    string response = WeatherAPI::fetchWeatherData(cityName, countryName);

    if (response.empty()) {
        return forecast;
    }

    try {
        json data = json::parse(response);

        string inputCityLower = toLower(cityName);
        string inputCountryLower = toLower(countryName);

        string actualCity = data["location"]["name"];
        string actualCountry = data["location"]["country"];

        string actualCityLower = toLower(actualCity);
        string actualCountryLower = toLower(actualCountry);

        if (actualCityLower != inputCityLower || actualCountryLower != inputCountryLower) {
            cout << "\n \"" << cityName << "\" was not recognized as a city in \"" << countryName << "\".\n";
            cout << "Please check the spelling and try again.\n" << endl;
            exit(1);
        }

        auto days = data["forecast"]["forecastday"];
        for (auto& day : days) {
            string date = day["date"];
            string year = date.substr(0, 4);
            string month = date.substr(5, 2);
            string dayPart = date.substr(8, 2);

            string condition = day["day"]["condition"]["text"];
            float temp = day["day"]["avgtemp_c"];
            int humidity = day["day"]["avghumidity"];
            float wind = day["day"]["maxwind_kph"];

            Weather w(condition, temp, humidity, wind, year, month, dayPart);

            for (auto& hour : day["hour"]) {
                string time = hour["time"];
                string h_condition = hour["condition"]["text"];
                float h_temp = hour["temp_c"];
                int h_humidity = hour["humidity"];
                float h_wind = hour["wind_kph"];

                w.addHourlyData(time, h_condition, h_temp, h_humidity, h_wind);
            }

            forecast.addWeather(w);
        }

    }
    catch (...) {
        cout << "Error parsing JSON data!" << endl;
    }

    return forecast;
}

void WeatherSystem::logHistory(const string& userInput, const string& forecastResult) {
    logger.logEntry(userInput, forecastResult);
}
