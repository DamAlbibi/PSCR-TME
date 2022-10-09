#pragma once 

#include <forward_list>
#include <cstddef>
#include <functional>
#include <iterator>
#include <vector>
#include <utility>

namespace pr  {
    template<typename K, typename V> 
    class HashMap {
        class Entry {
            // Je pourrais mettre un const pour entry mais mon boulot deviendrait bien plus chiant
            K entry;
            V value;
            
            public:
                
                Entry(const K entry, V value) {
                    this->entry = entry;
                    this->value = value;
                }
                
                K getEntry() const {
                    return entry;
                }

                V* getValue() {
                    return &value;
                }
        };

        typedef std::vector<std::forward_list<Entry>> buckets_t;

        buckets_t buckets;
        size_t size;

        public:
            HashMap(size_t init = 100) {
                size = 0;
                buckets.reserve(init);
                for (size_t i = 0; i < init; i ++) {
                    buckets.push_back(std::forward_list<Entry> ());
                }
            }

            V* get(const K& key) {
                size_t h = std::hash<K>()(key);
                
                h = h % buckets.size();

                for (Entry e: buckets[h]) {
                    if (e.getEntry() == key) {
                        return e.getValue();
                    }
                }

                return nullptr;
            }

            bool put (const K& key, const V& value) {
                size_t h = std::hash<K>()(key);
                
                h = h % buckets.size();
                
                for (auto iterator_l = buckets[h].begin(); iterator_l != buckets[h].end(); ++iterator_l) {
                    if (iterator_l->getEntry() == key) {
                        *iterator_l = Entry(key, value);
                        return false;
                    }
                }
                

                size++;
                buckets[h].push_front(Entry(key, value));

                return true;
            }

            size_t size_h() {
                return size;
            }

            std::vector<std::pair<K, V>> getCopy() {

                std::vector<std::pair<K, V>> vector;

                for (std::forward_list<Entry> f: buckets) {
                    for (Entry e: f) {
                        vector.push_back(std::make_pair(e.getEntry(), *(e.getValue())));
                    }
                }
                return vector;
            }
    };
}