#include "quiz.h"

int main(int argc, const char *argv[]) {

    std::optional<json> a = GetJSONFromFile("example.json");
    assert(a.has_value());

    SetUnwrapped b = ParseJSON(a.value());

    Set *s = ParseSet(b);
    delete s;

    return 0;
}
