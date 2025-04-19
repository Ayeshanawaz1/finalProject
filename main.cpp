#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <curl/curl.h>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

class City {
private:
    string cityName, countryName;
    int postalCode;

public:
    string getcityName() 
	{ 
		return cityName; 
	}
    string getcountryName() 
	{ 
		return countryName; 
		}
    int getpostalCode() 
	{ 
		return postalCode; 
	}

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
	
	    string getdateOfForecast() 
		{ 
			return dateOfForecast; 
		}
		
	    void displayWeather() {
	        cout << "Date: " << dateOfForecast << endl;
	        cout << "Condition: " << weatherCondition << endl;
	        cout << "Temperature: " << currentTemperature << "°C" << endl;
	        cout << "Humidity: " << humidityPercentage << "%" << endl;
	        cout << "Wind Speed: " << windSpeed << " km/h" << endl;
	        cout << "-----------------------------" << endl;
	    }
};

//class HourlyWeather : public  Weather
//{
//	void displayHourlyWeather()
//	{
//		cout << "Hourly Weather: ";
//	}
//};
//
//class WeeklyWeather : public Weather
//{
//	cout << "Weekly weather: ";

class Forecast {
	private:
	    City city;
	    vector<Weather> weather;
	
	public:
	    Forecast(string cityName = "", string countryName = "") {
	        city = City(cityName, countryName);
	    }
	
		void addWeather(const Weather& w) 
		{
    		weather.push_back(w);
		}
		
	    void displayForecast() {
	        cout << "\nForecast for " << city.getcityName() << ", " << city.getcountryName() << ":\n";
	        cout << "=============================\n";
	        for (int i = 0; i < weather.size(); i++) {
	            cout << "Day " << (i + 1) << ":\n";
	            weather[i].displayWeather();
	        }
	    }

		void displayForecastByDate(string date) 
		{
			bool found = false;
			for ( Weather& w : weather) 
			{
				// Trim any extra spaces in both date values
				string forecastDate = w.getdateOfForecast();
//				forecastDate.erase(remove(forecastDate.begin(), forecastDate.end(), ' '), forecastDate.end());
//			    date.erase(remove(date.begin(), date.end(), ' '), date.end());
			
			    cout << "Comparing input date: " << date << " with forecast date: " << forecastDate << endl;  // Debugging line
			    if (forecastDate == date) 
				{
			    cout << "\nForecast for " << city.getcityName() << ", " << city.getcountryName() 
				<< ":\n";
			    w.displayWeather();
			    found = true;
			    break;
			    }
			}
			    if (!found) 
				{
			        cout << "No forecast available for " << date << " in " << city.getcityName() <<
					", " << city.getcountryName() << "." << endl;
			    }
		}
};

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

class WeatherAPI {
	public:
	    static string fetchWeatherData(string& cityName, string& countryName) {
	        string apiKey = "a8ad7a0710ba4c18add144233251304";  // Replace with your API key
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
	
	        return "";  // Return empty if curl initialization failed
	    }
};

class WeatherSystem {
	public:
	    Forecast loadData(string cityName, string countryName) //---------------- 
		{
	        Forecast forecast(cityName, countryName);
	        
	        // Fetch weather data from API using WeatherAPI class
	        string response = WeatherAPI::fetchWeatherData(cityName, countryName);
	        
	        if (response.empty()) {
	            return forecast;  // Return empty forecast if API call fails
	        }
	
	        try {
	            json data = json::parse(response);
	            
	            string actualCity = data["location"]["name"];
        		string actualCountry = data["location"]["country"];

        		if (actualCity != cityName || actualCountry != countryName) {
            		cout <<  actualCity << " was not found in " << countryName << "." << endl;
            		
					exit(1);  
        		}
        
	            auto days = data["forecast"]["forecastday"];
	
	            for (auto& day : days) {
	                string date = day["date"];
	                string condition = day["day"]["condition"]["text"];
	                float temp = day["day"]["avgtemp_c"];
	                int humidity = day["day"]["avghumidity"];
	                float wind = day["day"]["maxwind_kph"];
	
	                Weather w(condition, temp, humidity, wind, date);
	                forecast.addWeather(w);
	            }
	
	        } catch (...) {
	            cout << "Error parsing JSON data!" << endl;
	        }
	
	        return forecast;
	    }
};


int main() 
{
    cout << "==============================================" << endl;
    cout << "        Welcome to Weather Forecast       " << endl;
    cout << "  Plan your week with confidence and clarity!  " << endl;
    cout << "==============================================" << endl;
    string countryName;
	string cityName;
    cout << "\nEnter Country Name: ";
    getline(cin, countryName);

    cout << "Enter City Name: ";
    getline(cin, cityName);
//
    WeatherSystem system1;
    Forecast f1 = system1.loadData(cityName, countryName);
//    f1.displayForecast();

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