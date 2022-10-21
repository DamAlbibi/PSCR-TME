#include "Pool.h"

namespace pr {
    /*
    Pool::Pool(int qsize): queue(Queue(qsize));
    */

    void Pool::start(int nbthread) {
        for (int i = 0; i < nbthread; i++) {
            threads.emplace_back(poolWorker, std::ref(queue));
        }
    }

    void Pool::stop() {
        queue.setBlocking(false);
        for (auto& t: threads) {
            t.join();
        }
    }

    void Pool::submit (Job * job) {
        queue.push(job);
    }

    /*
    Pool::~Pool() {
        // I don't think I have need to delete something, I doesn't have any data on the heap
    }
    */
}