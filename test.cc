#include "quiz.h"

// typedef struct {
//     int a, b, c;
// } estructura;

// typedef struct {
//     estructura *structuras;
// } multos;


// estructura funca() {
//     estructura a{};
//     a.a = 0;
//     a.b = 1;
//     a.c = 3;
//     return a;
// }
int main(int argc, const char *argv[]) {

    std::optional<json> a = GetJSONFromFile("example.json");
    assert(a.has_value());

    SetUnwrapped b = ParseJSON(a.value());

    std::cerr << "B" << std::endl;
    Set *s = ParseSet(b);
    std::cerr << "done" << std::endl;
    delete s;



    // multos m;
    // m.structuras = (estructura *)malloc(sizeof(estructura) * 20);
    // for (int i = 0; i < 20; i++) {
    //     m.structuras[i] = funca();
    // }

    // for (int i = 0; i < 20; i++) {
    //     printf("%d %d %d\n", m.structuras[i].a, m.structuras[i].b, m.structuras[i].c);
    // }

    // free(m.structuras);
    return 0;
}
