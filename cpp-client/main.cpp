#include <iostream>
#include <ta_analytics_sdk.h>
#include "ta_json_object.h"
#include <thread>
#if defined(_WIN32)
#include <windows.h>
#endif
using namespace wildfiredata;
using namespace std;

int main(){
    WildfireAnalyticsAPI::EnableLogType(LOGCONSOLE);
    const string server_url = "server_url";
    const string appid = "app_id";
    TDConfig config;
    config.appid = appid;
    config.server_url = server_url;
    config.enableAutoCalibrated = true;
    config.mode = TDMode::TD_NORMAL;
    config.databaseLimit = 3000;
    config.dataExpiration = 15;
    config.databasePath = "./";
    bool isInitSuccess = WildfireAnalyticsAPI::Init(config);
    if (!isInitSuccess){
        cout << "fail to init" << endl;
    }

    // 设置公共属性
    TDJSONObject superProperties;
    superProperties.SetString("gender", "male");
    superProperties.SetBool("win", true);
    superProperties.SetNumber("age", 100);
    superProperties.SetString("birthday", "2021-09-16 14:54:50");
    WildfireAnalyticsAPI::SetSuperProperty(superProperties);

    // 发送事件
    TDJSONObject properties;
    properties.SetString("name", "alice");
    properties.SetNumber("age", 18);
    vector<TDJSONObject> list1;

    TDJSONObject json1;
    json1.SetNumber("level", 132);
    properties.SetObject("object", json1);

    vector<string> list_str;
    list_str.push_back("item_name1");
    list_str.push_back("item_name2");
    properties.SetList("list_str", list_str);

    // 设置账号ID
    WildfireAnalyticsAPI::Login("my_account_id_alice");
    // 修改访客ID
    WildfireAnalyticsAPI::Identify("my_distinct_id_xxxx");
    
    WildfireAnalyticsAPI::Track("test_event_name",properties);
    WildfireAnalyticsAPI::Flush();
    std::this_thread::sleep_for(std::chrono::milliseconds(100000));
    return 0;
}