// #include <iostream>
// #include <list>
// #include <optional>
// #include <unordered_map>
// #include <utility>

// using namespace std;

// template<typename T> using entry = pair<string, T>;

// // LRU Cache with string keys and templated value
// template <typename T>
// class LRUCache {
//     public:
//     LRUCache(int sz): sz_(sz) {};
//     void add(string key, T value);
//     optional<T> get(string key);

//     private:
//     int sz_;
//     list<entry<T>> store_;
//     unordered_map<string, typename list<entry<T>>::iterator> lookup_;
// };

// template<typename T>
// void LRUCache<T>::add(string key, T value) {
//     auto itr = lookup_.find(key);
//     if (itr == lookup_.end()) {
//         // add to store and lookup
//         if (store_.size() == sz_) {
//             auto oldest_entry = store_.front();
//             store_.pop_front();
//             lookup_.erase(oldest_entry.first);
//             cout << "Evicted oldest entry: " << oldest_entry.first << endl;
//         }
//     } else {
//         // erase the key - since we will move it to back
//         store_.erase(itr->second);
//         lookup_.erase(itr);
//     }
//     store_.push_back(make_pair(key, value));
//     lookup_[key] = make_pair(key, store_.back());
//     cout << "Added key: " << key << endl;
// }

// template<typename T>
// optional<T> LRUCache<T>::get(string key) {
//     if (lookup_.find(key) == lookup_.end()) {
//         return optional<T>();
//     }

//     auto itr = lookup_.find(key);
//     store_.erase(itr);
//     store_.push_back(make_pair(key, itr->second));
//     return optional<T>(itr->second->second);
// }

// int main() {
//     LRUCache<int> cache(5);
//     cache.add("a", 1);
//     cache.add("b", 2);
//     cache.add("c", 1);
//     cache.add("d", 2);
//     cache.add("e", 1);
//     cache.add("f", 2);
// }
