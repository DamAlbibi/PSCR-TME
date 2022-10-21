#pragma once

#include <mutex>
#include <condition_variable>

namespace pr {
    mutex mut;
    int cpt;
    int n;
    condition_variable cv;
    public:
        Barrier(int n): cpt(0), n(n);
        void waitFor();
        void done();
}