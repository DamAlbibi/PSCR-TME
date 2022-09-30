#pragma once 

#include <vector>
#include <forward_list>
#include <cstddef>
#include <functional>
#include <iterator>

namespace pr  {
    template<typename K, typename v> 
    class HashMap {
        class Entry {
            const k entry;
            v value;
        }

        typedef std::vector<std::forward_list<Entry>> buckets_t;

        buckets_t buckets;
        size_t size;

        public:
            HashMap(size_t init = 100) {
                buckets.reserve(init);
                for (size_t i = 0; i < init; i ++) {
                    buckets[i].push_back();
                }
            }

            // Je ne sais pas exactement ce que peux faire l'iterator de la forward_list, en theorie il me retourne un curseur sur une Entry
            V* get(const K& key) {
                size_t h = std::hash<K>()(key);
                
                h = h % buckets.size();
                for (auto iterator_l = buckets[h].begin(); iterator_l != mylist.end(); ++it) {
                    if (*iterator_l.k == key) {
                        return *iterator_l.v;
                    }
                }

                return nullptr;
            }

            // Pas oublier d'incrementer la size a chaque element ajoute
            bool put (const K& key, const V& value) {
                size_t h = std::hash<K>()(key);
                
                h = h % buckets.size();
                for (auto iterator_l = buckets[h].begin(); iterator_l != mylist.end(); ++it) {
                    if (*iterator_l.k == key) {
                        return *iterator_l.v;
                    }
                }
            }

            size_t size() {
                return size;
            }
    }
}