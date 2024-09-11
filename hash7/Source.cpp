#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <functional>
#include <fstream>

template<typename K, typename V, typename Hash = std::hash<K>>
class HashTable {
private:
    using PairType = std::pair<K, V>;
    std::list<PairType> elements; // O singurã listã pentru toate elementele
    std::vector<typename std::list<PairType>::iterator> buckets;
    size_t num_elements;
    Hash hash_function;
    float load_factor_threshold;

    void rehash() {
        std::vector<PairType> old_elements(elements.begin(), elements.end());
        elements.clear();
        buckets.clear();
        buckets.resize(old_elements.size() * 2, elements.end());
        num_elements = 0;
        for (const auto& pair : old_elements) {
            insert(pair.first, pair.second);
        }
    }

    float load_factor() const {
        return static_cast<float>(num_elements) / buckets.size();
    }

    size_t get_bucket_index(const K& key) const {
        return hash_function(key) % buckets.size();
    }

public:
    HashTable(size_t initial_size = 16, float load_factor_threshold = 1.0)
        : buckets(initial_size, elements.end()), num_elements(0), load_factor_threshold(load_factor_threshold) {}

    void insert(const K& key, const V& value) {
        size_t index = get_bucket_index(key);
        auto it = buckets[index];
        while (it != elements.end() && get_bucket_index(it->first) == index) {
            if (it->first == key) {
                it->second = value;
                return;
            }
            ++it;
        }
        elements.emplace(it, key, value);
        buckets[index] = --it;
        ++num_elements;
        if (load_factor() > load_factor_threshold) {
            rehash();
        }
    }

    bool remove(const K& key) {
        size_t index = get_bucket_index(key);
        auto it = buckets[index];
        while (it != elements.end() && get_bucket_index(it->first) == index) {
            if (it->first == key) {
                elements.erase(it);
                --num_elements;
                if (buckets[index] == it) {
                    if (elements.empty() || get_bucket_index(elements.begin()->first) != index) {
                        buckets[index] = elements.end();
                    }
                    else {
                        buckets[index] = std::find_if(elements.begin(), elements.end(),
                            [index, this](const PairType& pair) {
                                return get_bucket_index(pair.first) == index;
                            });
                    }
                }
                return true;
            }
            ++it;
        }
        return false;
    }

    V* search(const K& key) {
        size_t index = get_bucket_index(key);
        auto it = buckets[index];
        while (it != elements.end() && get_bucket_index(it->first) == index) {
            if (it->first == key) {
                return &it->second;
            }
            ++it;
        }
        return nullptr;
    }

    V& operator[](const K& key) {
        size_t index = get_bucket_index(key);
        auto it = buckets[index];
        while (it != elements.end() && get_bucket_index(it->first) == index) {
            if (it->first == key) {
                return it->second;
            }
            ++it;
        }
        insert(key, V());
        return buckets[index]->second;
    }

    void print() const {
        for (const auto& pair : elements) {
            std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
        }
    }
};

int main() {
    HashTable<std::string, int> ht;
    ht.insert("one", 1);
    ht.insert("two", 2);
    ht.insert("three", 3);

    ht.print();

    ht.remove("two");
    ht.print();

    int* value = ht.search("three");
    if (value) {
        std::cout << "Found value: " << *value << std::endl;
    }
    else {
        std::cout << "Value not found" << std::endl;
    }

    ht["four"] = 4;
    ht.print();

    return 0;
}
