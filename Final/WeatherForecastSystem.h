#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <ctime>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// City class
class City {
private:
    string cityName, countryName;
    int postalCode;

public:
    City(string city = "", string country = "", int code = 0)
        : cityName(city), countryName(country), postalCode(code) {
    }

    string getcityName() { return cityName; }
    string getcountryName() { return countryName; }
    int getpostalCode() { return postalCode; }

    void displayCity() {
        cout << "City: " << cityName << ", Country: " << countryName << " Code: " << postalCode << endl;
    }
};

// Weather class
class Weather {
private:
    string weatherCondition, year, month, day;
    float currentTemperature, windSpeed;
    int humidityPercentage;

    vector<string> hours;
    vector<string> hourConditions;
    vector<float> hourTemperatures;
    vector<int> hourHumidities;
    vector<float> hourWinds;

public:
    Weather(string weather = "", float temp = 0.0, int humidity = 0, float wind = 0.0,
        string _year = "", string _month = "", string _day = "")
        : weatherCondition(weather), currentTemperature(temp), humidityPercentage(humidity),
        windSpeed(wind), year(_year), month(_month), day(_day) {
    }

    string getdateOfForecast() {
        return day + "-" + month + "-" + year;
    }

    void displayWeather() {
        cout << "Date: " << day << "/" << month << "/" << year << endl;
        cout << "Condition: " << weatherCondition << endl;
        cout << "Temperature: " << currentTemperature << "°C" << endl;
        cout << "Humidity: " << humidityPercentage << "%" << endl;
        cout << "Wind Speed: " << windSpeed << " km/h" << endl;
        cout << "-----------------------------" << endl;
    }

    void addHourlyData(string time, string condition, float temp, int humidity, float wind) {
        hours.push_back(time);
        hourConditions.push_back(condition);
        hourTemperatures.push_back(temp);
        hourHumidities.push_back(humidity);
        hourWinds.push_back(wind);
    }

    void displayHourlyForecast() {
        cout << "\nHOURLY FORECAST:\n------------------------\n";
        for (size_t i = 0; i < hours.size(); i++) {
            cout << "Time: " << hours[i] << endl;
            cout << "Condition: " << hourConditions[i] << endl;
            cout << "Temperature: " << hourTemperatures[i] << "°C" << endl;
            cout << "Humidity: " << hourHumidities[i] << "%" << endl;
            cout << "Wind Speed: " << hourWinds[i] << " km/h" << endl;
            cout << "-----------------------------\n";
        }
    }
};

// Forecast class
class Forecast {
private:
    City city;
    vector<Weather> weather;

public:
    Forecast(string cityName = "", string countryName = "")
        : city(cityName, countryName) {
    }

    void addWeather(const Weather& w) {
        weather.push_back(w);
    }

    void displayForecastByWeek() {
        cout << "\nForecast for " << city.getcityName() << ", " << city.getcountryName() << ":\n";
        cout << "=============================\n";
        for (size_t i = 0; i < weather.size(); i++) {
            cout << "Day " << (i + 1) << ":\n";
            weather[i].displayWeather();
        }
    }

    void displayForecastByDate(string day, string month, string year) {
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

    void displayHourlyForecast(string day, string month, string year) {
        string inputDate = day + "-" + month + "-" + year;
        bool found = false;

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
};

// HistoryLogger class
class HistoryLogger {
private:
    const string filename = "weather_history.txt";

public:
    void logEntry(const string& userInput, const string& forecastResult) {
        ofstream outFile(filename, ios::app);
        if (outFile.is_open()) {
            time_t now = time(0);
            tm localTime;
            localtime_s(&localTime, &now);
            char timeStr[80];
            strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &localTime);

            outFile << "[" << timeStr << "]\n";
            outFile << "User Input: " << userInput << "\n";
            outFile << "Forecast Result:\n" << forecastResult << "\n";
            outFile << "----------------------------------------\n";
            outFile.close();
        }
        else {
            cerr << "Error: Unable to open history file!" << endl;
        }
    }
};


inline string captureOutput(void (Forecast::* func)(), Forecast& forecast) {
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());
    (forecast.*func)();
    cout.rdbuf(old);
    return buffer.str();
}

inline string captureOutput(void (Forecast::* func)(string, string, string), Forecast& forecast, string y, string m, string d) {
    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());
    (forecast.*func)(y, m, d);
    cout.rdbuf(old);
    return buffer.str();
}