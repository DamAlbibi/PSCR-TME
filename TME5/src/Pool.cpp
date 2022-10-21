#include "Pool.h"
#include <iostream>

namespace pr {
    
    Pool::Pool(int qsize): queue(qsize) {}

    void poolWorker(Queue<Job>& queue) {
        while(true) {
            Job* job = queue.pop();
            if(job==nullptr) break;
            job->run();
            delete job;
        }
    } 

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

    
    Pool::~Pool() {
        stop();
    }
}