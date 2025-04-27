#include <iostream>
#include <string>
#include "WeatherSystem.h"
#include "WeatherForecastSystem.h"

using namespace std;

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

    string userInput = "City: " + cityName + ", Country: " + countryName;
    WeatherSystem system1;
    Forecast f1 = system1.loadData(cityName, countryName);

    cout << "\nDo you want the forecast for:\n";
    cout << "1. Whole Week\n";
    cout << "2. Specific Day\n";
    cout << "3. Hourly Forecast\n";
    cout << "Enter your choice (1, 2 or 3): ";
    int choice;
    cin >> choice;
    cin.ignore();

    string forecastResult;
    if (choice == 1) {
        forecastResult = captureOutput(&Forecast::displayForecastByWeek, f1);
        f1.displayForecastByWeek();
    }
    else if (choice == 2) {
        string year, month, day;
        cout << "Enter Year (YYYY): ";
        getline(cin, year);
        cout << "Enter Month (MM): ";
        getline(cin, month);
        cout << "Enter Day (DD): ";
        getline(cin, day);
        forecastResult = captureOutput(&Forecast::displayForecastByDate, f1, year, month, day);
        f1.displayForecastByDate(year, month, day);
    }
    else if (choice == 3) {
        string year, month, day;
        cout << "Enter Year (YYYY): ";
        getline(cin, year);
        cout << "Enter Month (MM): ";
        getline(cin, month);
        cout << "Enter Day (DD): ";
        getline(cin, day);
        forecastResult = captureOutput(&Forecast::displayHourlyForecast, f1, year, month, day);
        f1.displayHourlyForecast(year, month, day);
    }
    else {
        cout << "Invalid choice. Please restart and choose 1, 2 or 3." << endl;
        return 1;
    }

    system1.logHistory(userInput, forecastResult);
    cout << "\nYour forecast has been saved to weather_history.txt\n";

    return 0;
}
