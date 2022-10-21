#pragma once

#include <mutex>
#include <condition_variable>

namespace pr {
    class Barrier {
        std::mutex mut;
        int cpt;
        int n;
        std::condition_variable cv;
        public:
            Barrier(int n);
            void waitFor();
            void done();
    };
}