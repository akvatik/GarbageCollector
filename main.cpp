#include <iostream>
#include <cassert>
#include "memory/Graph.h"  // Подключите файл с вашим графом и сборщиком мусора
#include "memory/GarbageCollector_t.h"



#include "test/Functional_testsGC.h"
#include "test/Load_testsGC.h"


int main() {
    runFunctionalTests();
    runLoadTests();
    return 0;
}


