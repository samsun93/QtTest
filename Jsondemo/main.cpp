#include <iostream>
#include <fstream>
#include "json.h"
#include<QDebug>
using namespace std;

int main()
{
    Json::Value people1;
        people1["name"] = "Dione";
        people1["sex"] = "男";
        people1["age"] = 24;
        people1["note"] = "jsoncpp write test!";

        Json::Value people2;
        people2["name"] = "Hulis";
        people2["sex"] = "女";
        people2["age"] = 22;
        people2["note"] = "jsoncpp write test!";

        Json::Value peoples;
        peoples.append(people1);
        peoples.append(people2);

        Json::Value writeValue;
        writeValue["classname"] = "三年一班";
        writeValue["peoples"] = peoples;


        Json::FastWriter fwriter;
        std::string strf = fwriter.write(writeValue);
        std::ofstream ofsf("example_fast_writer.json");
        ofsf << strf;
        ofsf.close();

        Json::StyledWriter swriter;
        std::string strs = swriter.write(writeValue);
        std::ofstream ofss("example_styled_writer.json");
        ofss << strs;
        ofss.close();

        // read
        string strValue = "{\"key1\":\"111\",\"array\":[{\"key2\":\"222\"},{\"key2\":\"333\"},{\"key2\":\"444\"}]}";
        Json::Reader reader;
        Json::Value root;
        if (reader.parse(strValue, root))
        {
            std::string out = root["key1"].asString();
            qDebug()<<QString::fromStdString(out);
            Json::Value arrayObj = root["array"];
            for (unsigned int i=0; i<arrayObj.size(); i++)
            {
                out = arrayObj[i]["key2"].asString();
                qDebug()<<QString::fromStdString(out);
            }
        }

        std::ifstream ifs("example_fast_writer.json");
        if (reader.parse(ifs, root))
        {
            std::string out = root["classname"].asString();
            qDebug()<<QString::fromStdString(out);
            Json::Value peoples = root["peoples"];
            for (unsigned int i=0; i<peoples.size(); i++)
            {
                qDebug()<<QString::fromStdString(peoples[i]["name"].asString());
                qDebug()<<QString::fromStdString(peoples[i]["sex"].asString());
                qDebug()<<QString::fromStdString(peoples[i]["age"].asString());
                qDebug()<<QString::fromStdString(peoples[i]["note"].asString());
            }
        }

        return 0;


}

