#include "WeatherAPI.h"
#include <curl/curl.h>
#include <iostream>
using namespace std;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    (*((string*)userp)).append((char*)contents, size * nmemb);
    return size * nmemb;
}

string WeatherAPI::fetchWeatherData(string& cityName, string& countryName) {
    string apiKey = "a8ad7a0710ba4c18add144233251304"; // your API key
    string url = "http://api.weatherapi.com/v1/forecast.json?key=" + apiKey + "&q=" + cityName + "," + countryName + "&days=7";

    CURL* curl = curl_easy_init();
    string response;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            cout << "Error: " << curl_easy_strerror(res) << endl;
            return "";
        }
        return response;
    }
    return "";
}
