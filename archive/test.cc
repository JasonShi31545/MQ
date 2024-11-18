#include "quiz.h"

int main(int argc, const char *argv[]) {

    std::optional<json> a = GetJSONFromFile("example.json");
    assert(a.has_value());

    SetUnwrapped b = ParseJSON(a.value());

    std::cerr << "B" << std::endl;
    std::unique_ptr<Set> s = ParseSet(b);
    std::cerr << "done" << std::endl;

    return 0;
}
