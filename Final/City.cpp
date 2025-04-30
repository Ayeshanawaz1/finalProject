#include "City.h"

City::City(string city, string country, int code)
    : cityName(city), countryName(country), postalCode(code) {
}

string City::getcityName() { return cityName; }
string City::getcountryName() { return countryName; }
int City::getpostalCode() { return postalCode; }

void City::displayCity() {
    cout << "City: " << cityName << ", Country: " << countryName << " Code: " << postalCode << endl;
}
