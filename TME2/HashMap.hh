#pragma once 

#include <vector>
#include <forward_list>
#include <cstddef>
#include <functional>

namespace pr  {
    template<typename K, typename v> class HashMap {
        class Entry {
            const k entry;
            v value;
        }

        typedef std::vector<std::forward_list<Entry>> buckets_t;

        buckets_t buckets;

        public:
            HashMap(size_t init = 100) {
                buckets.reserve(init);
                for (size_t i = 0; i < init; i ++) {
                    buckets[i].push_back();
                }
            }

            V* get(const K& key) {
                size_t h = std::hash<K>()(key);
                
                
            }
    }
}