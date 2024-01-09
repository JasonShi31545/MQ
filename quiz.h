#include <iostream>
#include <map>
#include <unordered_map>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <chrono>
#include <queue>
#include <ctime>
#include <optional>
#include <string>
#include <utility>
#include <any>
#include "nlohmann/json.hpp"
#include <fstream>
#include <typeinfo>
#include <SDL2/SDL.h>
using json = nlohmann::json;

#ifndef QUIZ_H
#define QUIZ_H

class TimeFormatException: public std::exception {
    public:
    using std::exception::what;
    virtual char *what() {
        return (char *)"Time is incorrect for Set/Item, something has gone wrong in JSON?";
    }
};

class DataNotFoundException: public std::exception {
public:
    using std::exception::what;
    virtual char *what() {
        return message;
    }
    DataNotFoundException() {
        message = (char *)"";
    }
    DataNotFoundException(std::string &&str) {
        message = (char *)str.c_str();
    }

private:
    char *message;

};

typedef enum: int {
    TD = 0,
    DT = 1,
} Direction;

typedef struct {
    std::string term;
    std::string def;
    unsigned int mastery;
    unsigned int corrects;
    unsigned int mistakes;
    std::optional<std::time_t> elapsed_correct;
} Item;

struct Set {
    Item *items;
    size_t size;
    std::optional<std::time_t> elapsed_open;
    Set() {
        items = nullptr;
        size = 0;
        elapsed_open = std::nullopt;
    }
};

class MCQ{
public:
        Item choices[4];
        int correctID;
        Direction direction;
        MCQ() : choices(), correctID(0), direction(TD) {}
};
class ERQ {
public:
        std::string response;
        Item correctItem;
        ERQ() : response(""), correctItem({0}) {}
};


std::optional<json> GetJSONFromFile(std::string filename) {
    std::ifstream f(filename);
    json data;
    try {
        data = json::parse(f);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return std::nullopt;
    }
    return data;
}

std::optional<std::time_t> ParseTimeFromString(std::string st) {
    // format: "YYYY/MM/DD HH:MM:SS"
    time_t time;
    int yy, month, dd, hh, mm, ss;
    struct tm timestruct;
    const char *zStart = st.c_str();
    int ret = sscanf(zStart, "%d/%d/%d %d:%d:%d", &yy, &month, &dd, &hh, &mm, &ss);
    if (ret == EOF) {
        return std::nullopt;
    }
    timestruct.tm_year = yy;
    timestruct.tm_mon = month;
    timestruct.tm_mday = dd;
    timestruct.tm_hour = hh;
    timestruct.tm_min = mm;
    timestruct.tm_sec = ss;
    timestruct.tm_isdst = -1;
    time = mktime(&timestruct);
    std::cout << time << std::endl;
    return time;
}

typedef std::pair<std::time_t, std::vector<std::unordered_map<std::string, std::any>>> SetUnwrapped;

SetUnwrapped ParseJSON(json jsdata) {
    SetUnwrapped res;

    auto time = ParseTimeFromString(jsdata["elapsed-since"]);
    if (!time.has_value()) throw TimeFormatException();

    if (jsdata.find("items") == jsdata.end()) {
        throw DataNotFoundException(std::string("Item Not Found"));
    }
    for (int i = 0; i < jsdata["items"].size(); i++) {
        res.second.push_back({
            {"term", jsdata["items"][i]["term"]},
            {"def", jsdata["items"][i]["def"]},
            {"mastery", jsdata["items"][i]["mastery"]},
            {"corrects", jsdata["items"][i]["corrects"]},
            {"mistakes", jsdata["items"][i]["corrects"]},
            {"ces", jsdata["items"][i]["ces"]},
        });
    }
    return res;
}

Item ParseItem(std::unordered_map<std::string, std::any> itemdata) {
    Item item;
    item.term = std::any_cast<std::string>(itemdata["term"]);
    item.def = std::any_cast<std::string>(itemdata["def"]);
    item.mastery = std::any_cast<unsigned int>(itemdata["mastery"]);
    item.corrects = std::any_cast<unsigned int>(itemdata["corrects"]);
    item.mistakes = std::any_cast<unsigned int>(itemdata["mistakes"]);
    //item.elapsed_correct = std::any_cast<>(itemdata["term"]);
    std::optional<std::time_t> t = ParseTimeFromString(std::any_cast<std::string>(itemdata["ces"]));
    if (!t.has_value()) throw TimeFormatException();
    item.elapsed_correct = t;
    return item;
}

// Set ParseSet(SetUnwrapped setdata) {

// }

#endif // QUIZ_H
