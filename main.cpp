#include "core/Application.h"

int main() {
    Application app(600, 800);
    app.init();

    app.run();

    app.shutdown();

    return 0;
}