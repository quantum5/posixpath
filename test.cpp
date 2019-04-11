#include <iostream>
#include <initializer_list>
#include <tuple>
#include "posixpath.h"

int main() {
    int count = 0;
    int passed = 0;
    int failed = 0;
    bool failure = false;

    std::cout << "Testing posixpath::join..." << std::endl;
    for (auto p : std::initializer_list<std::tuple<std::string, std::string, std::string>>{
            {"", ".", "."},
            {"/foo", "/bar", "/bar"},
            {"foo", "/bar", "/bar"},
            {"/foo", "bar", "/foo/bar"},
            {"/foo/", "bar", "/foo/bar"},
    }) {
        ++count;
        auto result = posixpath::join(std::get<0>(p), std::get<1>(p));
        if (result != std::get<2>(p)) {
            std::cout << "Error on case " << count << ": " << std::get<0>(p)
                << " + " << std::get<1>(p) << '\n'
                << "Expected: " << std::get<2>(p) << '\n'
                << "Actual:   " << result << std::endl;
            ++failed;
        } else {
            ++passed;
        }
    }
    std::cout << "Ran " << count << " tests.\n"
        << "  - " << passed << " passed.\n"
        << "  - " << failed << " failed." << std::endl;
    failure |= failed > 0;

    count = passed = failed = 0;
    std::cout << "Testing posixpath::normpath..." << std::endl;
    for (auto p : std::initializer_list<std::pair<std::string, std::string>>{
            {"", "."},
            {"/", "/"},
            {"//", "/"},
            {"///", "/"},
            {"///foo/.//bar//", "/foo/bar"},
            {"///foo/.//bar//.//..//.//baz", "/foo/baz"},
            {"///..//./foo/.//bar", "/foo/bar"},
    }) {
        ++count;
        auto result = posixpath::normpath(p.first);
        if (result != p.second) {
            std::cout << "Error on case " << count << ": " << p.first << '\n'
                << "Expected: " << p.second << '\n'
                << "Actual:   " << result << std::endl;
            ++failed;
        } else {
            ++passed;
        }
    }
    std::cout << "Ran " << count << " tests.\n"
        << "  - " << passed << " passed.\n"
        << "  - " << failed << " failed." << std::endl;
    failure |= failed > 0;

    return failure;
}

