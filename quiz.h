#include <iostream>
#include <map>
#include <unordered_map>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <chrono>
#include <cstring>
#include <queue>
#include <ctime>
#include <optional>
#include <string>
#include <utility>
#include <any>
#include <random>
#include "nlohmann/json.hpp"
#include "levenshtein.h"
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
    bool mastery;
    float priority;
    unsigned int corrects;
    unsigned int mistakes;
    std::optional<std::time_t> elapsed_correct;
    std::optional<std::time_t> elapsed;
} Item;

struct Set {
    Item *items;
    std::optional<std::time_t> elapsed_open;
    Set() {
        items = nullptr;
        _size = 0;
        elapsed_open = std::nullopt;
    }
    ~Set() {
        free(items);
    }
    size_t size() const {
        return _size;
    }
    void setSize(size_t s) {
        _size = s;
    }
private:
    size_t _size;
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
            {"nes", jsdata["items"][i]["nes"]},
        });
    }
    return res;
}

Item ParseItem(std::unordered_map<std::string, std::any> itemdata) {
    Item item;
    item.term = std::any_cast<std::string>(itemdata["term"]);
    item.def = std::any_cast<std::string>(itemdata["def"]);
    item.mastery = std::any_cast<bool>(itemdata["mastery"]);
    item.priority = std::any_cast<float>(itemdata["priority"]);
    item.corrects = std::any_cast<unsigned int>(itemdata["corrects"]);
    item.mistakes = std::any_cast<unsigned int>(itemdata["mistakes"]);
    //item.elapsed_correct = std::any_cast<>(itemdata["term"]);
    std::optional<std::time_t> ces = ParseTimeFromString(std::any_cast<std::string>(itemdata["ces"]));
    std::optional<std::time_t> nes = ParseTimeFromString(std::any_cast<std::string>(itemdata["nes"]));
    if (!ces.has_value() || !nes.has_value()) throw TimeFormatException();
    item.elapsed_correct = ces;
    item.elapsed = nes;
    return item;
}

Set *ParseSet(SetUnwrapped setdata) { // remember to wrap the return value in a std::unique_ptr or remember to delete
    Set *_set = new Set{};
    _set->items = (Item *)malloc(sizeof(Item) * setdata.second.size());
    _set->setSize(setdata.second.size());
    _set->elapsed_open = setdata.first;

    for (int i = 0; i < setdata.second.size(); i++) {
        auto mapping = setdata.second[i];
        _set->items[i] = ParseItem(mapping);
    }

    return _set;
}

int *random_int(int upperbound, int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, upperbound);
    assert(n > 0);
    int *nums = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        nums[i] = distrib(gen);
    }
    return nums;
}

std::tuple<int, int, int> getThree(int upperbound, int except = -1) {
    int *rands;
    auto check = [&rands, &except]() -> bool {
        if (!rands) return true;
        for (int i = 0; i < 3; i++) {
            if (rands[i] == except) return true;
        }
        return false;
    };
    do {
        rands = random_int(upperbound, 3);
    } while (check());
    std::tuple<int, int, int> res = {rands[0], rands[1], rands[2]};
    free(rands);
    return res;
}

std::time_t GetTimeNow() {
    return std::time(0);
}

float MySigmoid(float n) {
    const float a = 0.1;
    return 1.0f/(1.0f + expf(-a * n));
}

void SetDefaultTiming(Set *set) {
    set->elapsed_open = GetTimeNow();
}

float CalculatePriority(const Set &set, const Item item) {
    std::optional<std::time_t> e, ec;
    e = item.elapsed;
    ec = item.elapsed_correct;


    if (set.elapsed_open.has_value()) {
        if (e.has_value()) {
            e = e.value() - set.elapsed_open.value();
            e = e.value()/1000;
        }
        if (ec.has_value()) {
            ec = ec.value() - set.elapsed_open.value();
            ec = e.value()/1000;
        }
    } else {
        throw DataNotFoundException("elapsed date not found");
    }

    if (e.has_value() && !ec.has_value()) {
        // no correct trials, it's really bad
        return MySigmoid(item.mistakes * item.mistakes + 2.0f*e.value());
    } else if (e.has_value() && ec.has_value()) {
        // has correct trials
        if (e.value() == ec.value()) {
            // the last time was correct
            return MySigmoid(item.mistakes / 2.0f + 0.5f*ec.value());
        } else {
            // was not
            return MySigmoid(item.mistakes + 1.5f*ec.value());
        }
    }
    // has never seen it
    return 0.5f;
}

struct CompareItem {
    bool operator()(Item const &i1, Item const &i2) {
        return i1.priority < i2.priority;
    }
};

std::unique_ptr<std::priority_queue<Item, std::vector<Item>, CompareItem>> InstantiateQueueForSet(const Set &set) {
    std::priority_queue<Item, std::vector<Item>, CompareItem> *pq;
    pq = new std::priority_queue<Item, std::vector<Item>, CompareItem>();
    return std::unique_ptr<std::priority_queue<Item, std::vector<Item>, CompareItem>>(pq);
}


typedef std::unique_ptr<std::priority_queue<Item, std::vector<Item>, CompareItem>> QuizPQ;

MCQ *QuestionMCQ(QuizPQ pq, const Set &set, Direction d) {
    Item citem = pq->top();
    MCQ *mcq = new MCQ();
    int *random_id = random_int(3, 1);
    mcq->correctID = *random_id;
    mcq->direction = d;
    assert(set.size() > 4);
    int *more = NULL;

BACK:
    more = random_int(set.size(), 3);
    for (int i = 0; i < 3; i++) {
        if (more[i] == mcq->correctID) {
            free(more);
            more = NULL;
            goto BACK;
        }
    }

    assert(more != NULL);
    mcq->choices[mcq->correctID] = citem;
    int j = 0;
    for (int i = 0; i < 4; i++) {
        if (i == mcq->correctID) continue;
        mcq->choices[i] = set.items[more[j++]];
    }
    free(more);
    free(random_id);
    pq->pop();
    return mcq;
}

ERQ *QuestionERQ(QuizPQ pq, const Set &set, Direction d) {
    Item citem = pq->top();
    pq->pop();
    ERQ *erq = new ERQ();
    erq->correctItem = citem;
    return erq;
}




#endif // QUIZ_H
