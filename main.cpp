#include <iostream>
#include <vector>
#include <tuple>

#include "dhatpp.h"

using namespace dhatpp;

#if 1
int main(void) {
#if 0
    HashTable<int> ht(2.0, 4, 10);
    array<tuple <string, int>, 3> insert = {make_tuple("123", 3), make_tuple("33883", 3030), make_tuple("asdf", 382729)};
#else
    HashTable<int> ht(2.0, 4);
    array<tuple <string, int>, 9> insert = {make_tuple("123", 3),
                                            make_tuple("33883", 3030),
                                            make_tuple("asdf", 382729),
                                            make_tuple("1010", 3173),
                                            make_tuple("29398f", 28),
                                            make_tuple("hello", 5),
                                            make_tuple("world", 183),
                                            make_tuple("fu", 2),
                                            make_tuple("ck", 3),
                                           };
#endif

    for (auto &[k, v] : insert) {
        cout << "ht[\"" << k << "\"] = " << v << endl;
        ht.put(k, v);
    }

    cout << endl;

    for (auto &[k, _] : insert) {
        cout << "ht.get(string(\"" << k << "\")): " << ht.get(k) << endl;
    }

    cout << endl;

    for (auto &[k, _] : insert) {
            cout << "ht[string(\"" << k << "\")]: " << ht[k] << endl;
    }

#if 1
    cout << "____________" << endl << ht << "____________" << endl;
    ht["123.."] = 1038;
    cout << "____________" << endl << ht << "____________" << endl;
#endif

    try {
        cout << endl;
        cout << "ht[\"123\"]: " <<  ht["123"] << endl;
        cout << "ht[\"123..\"]: " <<  ht["123.."] << endl;
    } catch(const exception &ex) {
        cout << "Exception: [\"" << ex.what() << "\"]" << endl;
    }

    return 0;
}
#else
int main(void) {
    HashTable<int> ht(2.0, 4, 10);

    ht["1001"] = 1234;
    ht["fjdsa"] = 1023;
    ht["hello"] = 12;

    cout << "1001: " << ht["1001"] << endl;
    cout << "fjdsa: " << ht["fjdsa"] << endl;
    cout << "hello: " << ht["hello"] << endl;

    cout << "____" << endl << ht << "____" << endl;

    return 0;
}
#endif
