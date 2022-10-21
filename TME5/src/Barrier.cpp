#include "Barrier.h"

namespace pr {
    void Barrier::waitFor() {
        std::unique_lock<mutex> l(mut);
        while (cpt < n) {
            cv.wait(l);
        }
    }

    void Barrier::done() {
        std::unique_lock<mutex> l(mut); 
        compteur++;
        if (compteur == n) cv.notify_all();
    }
}