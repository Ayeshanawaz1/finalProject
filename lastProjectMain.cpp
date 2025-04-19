#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm> // For removing spaces
using namespace std;

class City {
private:
    string cityName, countryName;
    int postalCode;

public:
    string getcityName() { return cityName; }
    string getcountryName() { return countryName; }
    int getpostalCode() { return postalCode; }

    City(string city = "", string country = "", int code = 0) {
        cityName = city;
        countryName = country;
        postalCode = code;
    }

    void displayCity() {
        cout << "City: " << cityName << ", " << "Country: " << countryName << " Code: " << postalCode << endl;
    }
};

class Weather {
private:
    string weatherCondition, dateOfForecast;
    float currentTemperature, windSpeed;
    int humidityPercentage;

public:
    Weather(string weather = "", float temperature = 0.0, int humidity = 0, float wind = 0.0, string date = "") {
        weatherCondition = weather;
        currentTemperature = temperature;
        humidityPercentage = humidity;
        windSpeed = wind;
        dateOfForecast = date;
    }

    string getdateOfForecast() { return dateOfForecast; }
    void displayWeather() {
        cout << "Date: " << dateOfForecast << endl;
        cout << "Condition: " << weatherCondition << endl;
        cout << "Temperature: " << currentTemperature << "°C" << endl;
        cout << "Humidity: " << humidityPercentage << "%" << endl;
        cout << "Wind Speed: " << windSpeed << " km/h" << endl;
        cout << "-----------------------------" << endl;
    }
};

class Forecast {
private:
    City city;
    vector<Weather> weather;

public:
    Forecast(string cityName = "", string countryName = "") {
        city = City(cityName, countryName);
    }

    void loadDatafromFile(string cityName, string countryName, ifstream& file) {
        int days = 7;
        string date, temperature, humidity, wind, condition;
        string line;
        bool cityFound = false;
        bool countryFound = false;

        if (!file) {
            cout << "File failed to open" << endl;
            return;
        }

        while (getline(file, line)) {
            if (line == "#" + countryName) {
                countryFound = true;

                while (getline(file, line)) {
                    if (line == "#" + cityName) {
                        cityFound = true;

                        for (int i = 0; i < days; i++) {
                            getline(file, date, ',');
                            getline(file, temperature, ',');
                            getline(file, humidity, ',');
                            getline(file, wind, ',');
                            getline(file, condition);

                            float temp = stof(temperature);
                            int hum = stoi(humidity);
                            float windSpeed = stof(wind);

                            weather.push_back(Weather(condition, temp, hum, windSpeed, date));
                        }
                        break;
                    } else if (line[0] == '#') {
                        break;
                    }
                }
                break;
            }
        }

        if (!countryFound) {
            cout << "Country not found: " << countryName << endl;
        } else if (!cityFound) {
            cout << "City not found in " << countryName << ": " << cityName << endl;
        }
    }

    void displayForecast() {
        cout << "\nForecast for " << city.getcityName() << ", " << city.getcountryName() << ":\n";
        cout << "=============================\n";
        for (int i = 0; i < weather.size(); i++) {
            cout << "Day " << (i + 1) << ":\n";
            weather[i].displayWeather();
        }
    }

    void displayForecastByDate(string date) {
        bool found = false;
        for ( Weather& w : weather) {
            // Trim any extra spaces in both date values
            string forecastDate = w.getdateOfForecast();
            forecastDate.erase(remove(forecastDate.begin(), forecastDate.end(), ' '), forecastDate.end());
            date.erase(remove(date.begin(), date.end(), ' '), date.end());

            //cout << "Comparing input date: " << date << " with forecast date: " << forecastDate << endl;  // Debugging line
            if (forecastDate == date) {
                cout << "\nForecast for " << city.getcityName() << ", " << city.getcountryName() << " on " << date << ":\n";
                w.displayWeather();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "No forecast available for " << date << " in " << city.getcityName() << "." << endl;
        }
    }
};

class WeatherSystem {
public:
    Forecast loadData(string cityName, string countryName) {
        ifstream file("Weather Data.txt");
        Forecast forecast(cityName, countryName);

        if (!file.is_open()) {
            cout << "Failed to open file." << endl;
        } else {
            forecast.loadDatafromFile(cityName, countryName, file);
        }

        file.close();
        return forecast;
    }
};

int main() {
    cout << "==============================================" << endl;
    cout << "        Welcome to Weather Forecast       " << endl;
    cout << "  Plan your week with confidence and clarity!  " << endl;
    cout << "==============================================" << endl;

    string countryName, cityName;
    cout << "\nEnter Country Name: ";
    getline(cin, countryName);
    cout << "Enter City Name: ";
    getline(cin, cityName);

    WeatherSystem system1;
    Forecast f1 = system1.loadData(cityName, countryName);

    cout << "\nDo you want the forecast for:\n";
    cout << "1. Whole Week\n";
    cout << "2. Specific Day\n";
    cout << "Enter your choice (1 or 2): ";
    int choice;
    cin >> choice;
    cin.ignore();  // flush newline

    if (choice == 1) {
        f1.displayForecast();
    } else if (choice == 2) {
        string date;
        cout << "Enter date (YYYY-MM-DD): ";
        getline(cin, date);
        f1.displayForecastByDate(date);
    } else {
        cout << "Invalid choice. Please restart and choose 1 or 2." << endl;
    }

    return 0;
}




