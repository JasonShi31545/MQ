#include "quiz.h"
using namespace std;

int main(int argc, const char *argv[]) {

    printf("Start Program\n");
    // std::ifstream f("example.json");
    // json data = json::parse(f);
    // using namespace std;

    // cout << data["elapsed"] << endl;
    // cout << data["items"] << endl;
    // for (int i = 0; i < data["items"].size(); i++) {
    //     cout << data["items"][i] << endl;
    // }

    // cout << data["items"][0]["term"] << endl;
    // cout << data["items"][0]["def"] << endl;
    // cout << data["items"][0]["mastery"] << endl;
    // cout << data["items"][0]["corrects"] << endl;
    // cout << data["items"][0]["mistakes"] << endl;
    // cout << data["items"][0]["correct_elapse"] << endl;

    auto res = GetJSONFromFile("example.json");

    cout << res.value()["elapsed"] << endl;
    cout << res.has_value() << endl;

    return 0;
}
