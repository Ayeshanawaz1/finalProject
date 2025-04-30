#include "Forecast.h"
#include <iostream>

Forecast::Forecast(string cityName, string countryName)
    : city(cityName, countryName) {
}

void Forecast::addWeather(const Weather& w) {
    weather.push_back(w);
}

void Forecast::displayForecastByWeek() {
    cout << "\nForecast for " << city.getcityName() << ", " << city.getcountryName() << ":\n";
    cout << "=============================\n";
    for (size_t i = 0; i < weather.size(); i++) {
        cout << "Day " << (i + 1) << ":\n";
        weather[i].displayWeather();
    }
}

void Forecast::displayForecastByDate(string day, string month, string year) {
    bool found = false;
    string inputDate = day + "-" + month + "-" + year;

    for (Weather& w : weather) {
        if (w.getdateOfForecast() == inputDate) {
            cout << "\nForecast for " << city.getcityName() << ", " << city.getcountryName() << ":\n";
            w.displayWeather();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No forecast available for " << day << "/" << month << "/" << year
            << " in " << city.getcityName() << ", " << city.getcountryName() << "." << endl;
    }
}

void Forecast::displayHourlyForecast(string day, string month, string year) {
    bool found = false;
    string inputDate = day + "-" + month + "-" + year;

    for (Weather& w : weather) {
        if (w.getdateOfForecast() == inputDate) {
            cout << "\nHourly Forecast for " << city.getcityName() << ", " << city.getcountryName() << ":\n";
            w.displayHourlyForecast();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No hourly forecast available for " << day << "/" << month << "/" << year
            << " in " << city.getcityName() << ", " << city.getcountryName() << "." << endl;
    }
}
