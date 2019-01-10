/*
Weather Client

You are going to develop a program that gets the statistics about weather in the current city
using information from a certain server. The goal is to calculate statistics using the data from weather server.

To communicate with the weather server you have to implement interface IWeatherServer,
which provides the raw string from the real server for the requested day and time.

The real server (i.e. "weather.com") gets the requests in this format:
"<date>;<time>", for example:
"31.08.2018;03:00"

The server answers on requests with string like this:
"20;181;5.1"
This string contains the weather for the requested time and means next:
"<air_temperature_in_celsius>;<wind_direction_in_degrees>:<wind_speed>".
Wind direction value may be in range from 0 to 359 inclusively, temperature may be negative.

The task:
1. Implement fake server, because interacting with real network is inacceptable within the unit tests.
To do this, you need to use real server responses. Fortunately, you've collected some results for the several dates from the weather server.
Each line means "<request>" : "<response>":

"31.08.2018;03:00" : "20;181;5.1"
"31.08.2018;09:00" : "23;204;4.9"
"31.08.2018;15:00" : "33;193;4.3"
"31.08.2018;21:00" : "26;179;4.5"

"01.09.2018;03:00" : "19;176;4.2"
"01.09.2018;09:00" : "22;131;4.1"
"01.09.2018;15:00" : "31;109;4.0"
"01.09.2018;21:00" : "24;127;4.1"

"02.09.2018;03:00" : "21;158;3.8"
"02.09.2018;09:00" : "25;201;3.5"
"02.09.2018;15:00" : "34;258;3.7"
"02.09.2018;21:00" : "27;299;4.0"

IMPORTANT:
* Server returns empty string if request is invalid.
* Real server stores weather only for times 03:00, 09:00, 15:00 and 21:00 for every date. Do not use other hours in a day.

2. Implement IWeatherClient using fake server.
*/

/*
 * - Empty string parsing
 * - Valid data parsing
 * - Invalid data parsing  // TODO
 * - Parse data list
 *
 * - Weather server stub
 * - Test GetAverageTemperature for 31.08.2018
 * - Acceptance test for GetAverageTemperature
 * - Test GetMinimumTemperature for 31.08.2018
 * - Acceptance test for GetMinimumTemperature
 * - Test GetMaximumTemperature for 31.08.2018
 * - Acceptance test for GetMaximumTemperature
 * - Test GetAverageWindDirection for 31.08.2018
 * - Acceptance test for GetAverageWindDirection
 * - Test GetMaximumWindSpeed for 31.08.2018
 * - Acceptance test for GetMaximumWindSpeed
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

struct Weather
{
    short temperature = 0;
    unsigned short windDirection = 0;
    double windSpeed = 0;
    bool operator==(const Weather& right) const
    {
        return temperature == right.temperature &&
               windDirection == right.windDirection &&
               std::abs(windSpeed - right.windSpeed) < 0.01;
    }
};

class IWeatherServer
{
public:
    virtual ~IWeatherServer() { }
    // Returns raw response with weather for the given day and time in request
    virtual std::string GetWeather(const std::string& request) = 0;
};

// Implement this interface
class IWeatherClient
{
public:
    virtual ~IWeatherClient() { }
    virtual double GetAverageTemperature(IWeatherServer& server, const std::string& date) = 0;
    virtual double GetMinimumTemperature(IWeatherServer& server, const std::string& date) = 0;
//    virtual double GetMaximumTemperature(IWeatherServer& server, const std::string& date) = 0;
//    virtual double GetAverageWindDirection(IWeatherServer& server, const std::string& date) = 0;
//    virtual double GetMaximumWindSpeed(IWeatherServer& server, const std::string& date) = 0;
};

class WeatherServerStub : public IWeatherServer
{
public:
    std::string GetWeather(const std::string& request)
    {
        static std::map<std::string, std::string> weatherMap = {{"31.08.2018;03:00" , "20;181;5.1"},
                                                                {"31.08.2018;09:00" , "23;204;4.9"},
                                                                {"31.08.2018;15:00" , "33;193;4.3"},
                                                                {"31.08.2018;21:00" , "26;179;4.5"},

                                                                {"01.09.2018;03:00" , "19;176;4.2"},
                                                                {"01.09.2018;09:00" , "22;131;4.1"},
                                                                {"01.09.2018;15:00" , "31;109;4.0"},
                                                                {"01.09.2018;21:00" , "24;127;4.1"},

                                                                {"02.09.2018;03:00" , "21;158;3.8"},
                                                                {"02.09.2018;09:00" , "25;201;3.5"},
                                                                {"02.09.2018;15:00" , "34;258;3.7"},
                                                                {"02.09.2018;21:00" , "27;299;4.0"}};
        auto result = weatherMap.find(request);
        return result == weatherMap.end() ? "" : result->second;
    }
};

Weather ParseWeather(const std::string &data);
class WeatherClient : public IWeatherClient
{
public:
    double GetAverageTemperature(IWeatherServer& server, const std::string& date)
    {
        double result = 0;


        std::string response = server.GetWeather(date + ";03:00");
        result += ParseWeather(response).temperature;
        response = server.GetWeather(date + ";09:00");
        result += ParseWeather(response).temperature;
        response = server.GetWeather(date + ";15:00");
        result += ParseWeather(response).temperature;
        response = server.GetWeather(date + ";21:00");
        result += ParseWeather(response).temperature;


        return result/4;
    }

    double GetMinimumTemperature(IWeatherServer& server, const std::string& date)
    {
        std::set<double> results;

        results.insert(ParseWeather(server.GetWeather(date + ";03:00")).temperature);
        results.insert(ParseWeather(server.GetWeather(date + ";09:00")).temperature);
        results.insert(ParseWeather(server.GetWeather(date + ";15:00")).temperature);
        results.insert(ParseWeather(server.GetWeather(date + ";21:00")).temperature);

        return *results.begin();
    }
};

Weather ParseWeather(const std::string &data)
{
    if (data.empty())
    {
        throw std::runtime_error("");
    }
    Weather weather;
    std::istringstream stream(data);

    stream >> weather.temperature;
    stream.ignore();
    stream >> weather.windDirection;
    stream.ignore();
    stream >> weather.windSpeed;

    return weather;
}

std::vector<Weather> ParseWeather(const std::vector<std::string> &response)
{
    std::vector<Weather> result;
    for (auto data : response)
    {
        Weather weather = ParseWeather(data);
        result.push_back(weather);
    }

    return result;
}

TEST(WeatherClient, CheckParsingEmptyString)
{
    EXPECT_THROW(ParseWeather(""), std::runtime_error);
}

TEST(WeatherClient, CheckParsingValidString)
{
    Weather wether;
    wether.temperature = 27;
    wether.windDirection = 299;
    wether.windSpeed = 4.0;

    ASSERT_EQ(wether, ParseWeather("27;299;4.0"));
}

TEST(WeatherClient, CheckParsingMultipleStrings)
{
    std::vector<std::string> response = {"20;181;5.1", "23;204;4.9", "33;193;4.3"};

    Weather wether0;
    wether0.temperature = 20;
    wether0.windDirection = 181;
    wether0.windSpeed = 5.1;

    Weather wether1;
    wether1.temperature = 23;
    wether1.windDirection = 204;
    wether1.windSpeed = 4.9;

    Weather wether2;
    wether2.temperature = 33;
    wether2.windDirection = 193;
    wether2.windSpeed = 4.3;

    std::vector<Weather> result = {wether0, wether1, wether2};
    ASSERT_EQ(result , ParseWeather(response));
}

TEST(WeatherClient, GetAverageTemperatureFor31_08_2018)
{
    WeatherServerStub server;
    WeatherClient client;

    ASSERT_DOUBLE_EQ(25.5, client.GetAverageTemperature(server, "31.08.2018"));
}

TEST(WeatherClient, AverageTemperatureAcceptance)
{
    WeatherServerStub server;
    WeatherClient client;

    ASSERT_DOUBLE_EQ(25.5, client.GetAverageTemperature(server, "31.08.2018"));
    ASSERT_DOUBLE_EQ(24.0, client.GetAverageTemperature(server, "01.09.2018"));
    ASSERT_DOUBLE_EQ(26.75, client.GetAverageTemperature(server, "02.09.2018"));
    EXPECT_THROW(client.GetAverageTemperature(server, "03.09.2018"), std::runtime_error);
}

TEST(WeatherClient, GetMinimumTemperatureFor31_08_2018)
{
    WeatherServerStub server;
    WeatherClient client;

    ASSERT_DOUBLE_EQ(20, client.GetMinimumTemperature(server, "31.08.2018"));
}

TEST(WeatherClient, MinimumTempertureAcceptance)
{
    WeatherServerStub server;
    WeatherClient client;

    ASSERT_DOUBLE_EQ(19, client.GetMinimumTemperature(server, "01.09.2018"));
    ASSERT_DOUBLE_EQ(21, client.GetMinimumTemperature(server, "02.09.2018"));
    EXPECT_THROW(client.GetMinimumTemperature(server, "03.09.2018"), std::runtime_error);
}
