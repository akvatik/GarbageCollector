#include "test/TestGarbageCollector.h"


int main() {
    testBasic();
    testAllReachable();
    testNoRoot();
    testCycle();
    testMultipleGraphs();
    testMarkReset();

    return 0;
}


