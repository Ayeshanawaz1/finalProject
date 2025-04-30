#pragma once
#include <string>
#include <iostream>

using namespace std;

class City {
private:
    string cityName, countryName;
    int postalCode;

public:
    City(string city = "", string country = "", int code = 0);

    string getcityName();
    string getcountryName();
    int getpostalCode();
    void displayCity();
};
