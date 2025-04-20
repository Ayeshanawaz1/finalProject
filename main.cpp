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
	    string weatherCondition, year, month, day;
	    float currentTemperature, windSpeed;
	    int humidityPercentage;
	    vector<string> hours;
		vector<string> hourConditions;
		vector<float> hourTemperatures;
		vector<int> hourHumidities;
		vector<float> hourWinds;
	
	public:
	    Weather(string weather = "", float temperature = 0.0, int humidity = 0, float wind = 0.0, string _year = "",
		string _month = "", string _day = "") {
	        weatherCondition = weather;
	        currentTemperature = temperature;
	        humidityPercentage = humidity;
	        windSpeed = wind;
	        year = _year;
	        month = _month;
	        day = _day;
//	        dateOfForecast = date;
	    }
	
	    string getdateOfForecast() 
		{ 
			return year + "-" + month + "-" + day; 
		}
		
	    void displayWeather() {
	        cout << "Date: " << year << "/" << month << "/" << day << endl;
	        cout << "Condition: " << weatherCondition << endl;
	        cout << "Temperature: " << currentTemperature << "°C" << endl;
	        cout << "Humidity: " << humidityPercentage << "%" << endl;
	        cout << "Wind Speed: " << windSpeed << " km/h" << endl;
	        cout << "-----------------------------" << endl;
	    }
	    
	    void addHourlyData(string time, string condition, float temp, int humidity, float wind) 
		{
		    hours.push_back(time);
		    hourConditions.push_back(condition);
		    hourTemperatures.push_back(temp);
		    hourHumidities.push_back(humidity);
		    hourWinds.push_back(wind);
		}
		
		void displayHourlyForecast() 
		{
		    cout << "\nHOURLY FORECAST:\n------------------------\n";
		    for (size_t i = 0; i < hours.size(); i++) 
			{
		        cout << "Time: " << hours[i] << endl;
		        cout << "Condition: " << hourConditions[i] << endl;
		        cout << "Temperature: " << hourTemperatures[i] << "°C" << endl;
		        cout << "Humidity: " << hourHumidities[i] << "%" << endl;
		        cout << "Wind Speed: " << hourWinds[i] << " km/h" << endl;
		        cout << "-----------------------------\n";
		    }
		}

};

string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

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
		
	    void displayForecastByWeek() {
	        cout << "\nForecast for " << city.getcityName() << ", " << city.getcountryName() << ":\n";
	        cout << "=============================\n";
	        for (int i = 0; i < weather.size(); i++) {
	            cout << "Day " << (i + 1) << ":\n";
	            weather[i].displayWeather();
	        }
	    }

		void displayForecastByDate(string year, string month, string day) 
		{
			bool found = false;
			string inputDate = year + "-" + month + "-" + day;
			
			for ( Weather& w : weather) 
			{
				// Trim any extra spaces in both date values
				string forecastDate = w.getdateOfForecast();
//				forecastDate.erase(remove(forecastDate.begin(), forecastDate.end(), ' '), forecastDate.end());
//			    date.erase(remove(date.begin(), date.end(), ' '), date.end());
			
			    cout << "Comparing input date: " << inputDate
				<< " with forecast date: " << forecastDate << endl;  // Debugging line
			    
				if (forecastDate == inputDate)
				{
			    cout << "\nForecast for " << city.getcityName() << ", " << city.getcountryName() << ":\n";
			    w.displayWeather();
			    found = true;
			    break;
			    }
			}
			    if (!found) 
				{
			        cout << "No forecast available for " << year << "/" << month << "/" <<day << " in " 
					<< city.getcityName() << ", " << city.getcountryName() << "." << endl;
			    }
		}
		
		void displayHourlyForecast(string year, string month, string day) 
		{
		    string inputDate = year + "-" + month + "-" + day;
		    bool found = false;
	
			for (Weather& w : weather) 
			{
			    if (w.getdateOfForecast() == inputDate) 
				{
			        cout << "\nHourly Forecast for " << city.getcityName() << ", " << city.getcountryName() << ":\n";
			        w.displayHourlyForecast();
			        found = true;
			        break;
			    }
			}
			
			if (!found) 
			{
			    cout << "No hourly forecast available for " << year << "/" << month << "/" << day << " in " 
			    << city.getcityName() << ", " << city.getcountryName() << "." << endl;
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
	            
	            string inputCityLower = toLower(cityName);
				string inputCountryLower = toLower(countryName);
				
				string actualCity = data["location"]["name"];
				string actualCountry = data["location"]["country"];
				
				string actualCityLower = toLower(actualCity);
				string actualCountryLower = toLower(actualCountry);
				
				if (actualCityLower != inputCityLower || actualCountryLower != inputCountryLower) {
				    cout << actualCity << " was not found in " << countryName << "." << endl;
				    exit(1);  // Exit if mismatch
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
	                
	                for (auto& hour : day["hour"]) 
					{
				        string time = hour["time"];
				        string h_condition = hour["condition"]["text"];
				        float h_temp = hour["temp_c"];
				        int h_humidity = hour["humidity"];
				        float h_wind = hour["wind_kph"];
				
				        w.addHourlyData(time, h_condition, h_temp, h_humidity, h_wind);
				    }
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
    cout << "3. Hourly Forecast\n";
    cout << "Enter your choice (1 or 2): ";
    int choice;
    cin >> choice;
    cin.ignore();  // flush newline

    if (choice == 1) {
        f1.displayForecastByWeek();
    } 
	else if (choice == 2) 
	{
        string year, month, day;
		cout << "Enter Year (YYYY): ";
		getline(cin, year);
		cout << "Enter Month (MM): ";
		getline(cin, month);
		cout << "Enter Day (DD): ";
		getline(cin, day);
        f1.displayForecastByDate(year, month, day);
    } 
    else if (choice == 3)
    {
    	string year, month, day;
		cout << "Enter Year (YYYY): ";
		getline(cin, year);
		cout << "Enter Month (MM): ";
		getline(cin, month);
		cout << "Enter Day (DD): ";
		getline(cin, day);
        f1.displayHourlyForecast(year, month, day);
	}
	else 
	{
        cout << "Invalid choice. Please restart and choose 1 or 2." << endl;
    }

    return 0;
}
