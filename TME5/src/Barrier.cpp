#include "Barrier.h"
#include <iostream>

namespace pr {

    Barrier::Barrier(int n): cpt(0), n(n) {}

    void Barrier::waitFor() {
        std::unique_lock<std::mutex> l(mut);
        while (cpt < n) {
            cv.wait(l);
        }
    }

    void Barrier::done() {
        std::unique_lock<std::mutex> l(mut); 
        cpt++;
        cv.notify_all();
    }
}