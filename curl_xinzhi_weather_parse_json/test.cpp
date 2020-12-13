#include <iostream>
#include <memory> 
#include <fstream>
#include <sstream>
#include "curl/curl.h"
#include <unistd.h>
#include </usr/include/jsoncpp/json/json.h>


using namespace std;

std::stringstream returned_data;
size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream) 
{
    std::string data((const char*)ptr, (size_t)size * nmemb);
    *((std::stringstream*)stream) << data << std::endl;
    return size * nmemb;
}



int curl_post_from_server(CURL* hnd,std::string server_addr)
{   
    returned_data.str("");
    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(hnd, CURLOPT_URL, server_addr.c_str());
    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &returned_data);
    curl_easy_setopt(hnd, CURLOPT_LOW_SPEED_LIMIT , 100);
    curl_easy_setopt(hnd, CURLOPT_LOW_SPEED_TIME , 2);
    CURLcode ret = curl_easy_perform(hnd);
    //std::cout << "ret = " << ret << std::endl;
    return ret;
}


int curl_get_from_server(CURL* hnd,std::string server_addr)
{   
    returned_data.str("");
    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_URL, server_addr.c_str());
    curl_easy_setopt(hnd, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.1 (KHTML, like Gecko) Chrome/21.0.1180.89 Safari/537.1");   //用户访问代理 User-Agent
    curl_easy_setopt(hnd, CURLOPT_REFERER,"http://www.thinkpage.cn");
    curl_easy_setopt(hnd, CURLOPT_TIMEOUT, 2);//设置超时
    curl_easy_setopt(hnd, CURLOPT_COOKIE, "");  

    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &returned_data);
    curl_easy_setopt(hnd, CURLOPT_LOW_SPEED_LIMIT , 100);
    curl_easy_setopt(hnd, CURLOPT_LOW_SPEED_TIME , 2);  
    CURLcode result = curl_easy_perform(hnd);
    //std::cout << "ret = " << result << std::endl;
    return result;
}

bool parse_json_data(std::string json_data)
{
    //std::cout <<"json_data" << json_data << std::endl;
    Json::Reader reader;
    Json::Value root;
    if (reader.parse(json_data, root)) 
    {
        Json::Value results;
        results = root["results"];
        //std::cout << "root " << results << std::endl;

        Json::Value location;
        location = results[0]["location"];
        std::string country = location["country"].asString();
        std::string name = location["name"].asString();
        std::cout << "country: " << country << std::endl;
        std::cout << "name: " << name << std::endl;

        Json::Value now;
        now = results[0]["now"];
        std::string temperature = now["temperature"].asString();
        std::string text = now["text"].asString();
        std::cout << "temperature: " << temperature << "℃" << std::endl;
        std::cout << "text: " << text << std::endl;

        Json::Value air;
        air = results[0]["air"];
        std::string quality = air["city"]["quality"].asString();
        std::cout << "quality: " << quality << std::endl;

        Json::Value alarms;
        alarms = results[0]["alarms"];
        for (int i=0;i<alarms.size();i++)
        {
            std::string description = alarms[i]["description"].asString();
            std::string type = alarms[i]["type"].asString();
            std::cout << "description: " << description << std::endl;
            std::cout << "type: " << type << std::endl;

        }

        std::string last_update = results[0]["last_update"].asString();
        std::cout << "last_update: " << last_update << std::endl;

    }
    return true;
}


int main(void)
{
    CURL* curl_weather;
    std::string xinzhi_url = "http://www.thinkpage.cn/weather/api.svc/getWeather";
    std::string city = "qingdao";
    std::string language ="zh-CHS";
    std::string curl_weather_url = xinzhi_url +  "?" + "&city=" + city + "&language=" + language + "&provider=CMA&unit=C&aqi=city";

    curl_weather = curl_easy_init();
    //curl_get_from_server(curl_weather,curl_weather_url);
    //std::cout << "returned_data:" << returned_data.str()<< std::endl;
    while(1)
    {
        curl_get_from_server(curl_weather,curl_weather_url);
        //std::cout << "returned_data:" << returned_data.str()<< std::endl;
        //if(returned_data.str() != NULL)
        {
            std::cout << std::endl << std::endl ;
            parse_json_data(returned_data.str());
            sleep(5);
        }
    }
    return 0;
}

/***
****  readme.txt
****  sudo apt-get install libjsoncpp-dev
****  g++ test.cpp -std=c++11 -fno-rtti -lalibabacloud-oss-cpp-sdk -lcurl -lcrypto -lpthread -ljsoncpp -o test.bin
****  http://www.thinkpage.cn/weather/api.svc/getWeather?city=beijing&language=zh-CHS&provider=CMA&unit=C&aqi=city
****  使用curl解析心知天气的json数据
****
***/
