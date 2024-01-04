#include <cassert>
#include <cstdio>
#include <cstring>
#include <stringzilla/stringzilla.hpp>

static char*
_default_alloc(sz_size_t sz, void* unused) {
    return (char*)malloc(sz);
}

static void
_default_free(sz_ptr_t p, sz_size_t usz, void* up) {
    return free(p);
}


constexpr sz_memory_allocator_t default_alloc = {
   _default_alloc, _default_free, nullptr
};

constexpr auto lev = 
  [](const char* left, size_t lz, const char* right, size_t rz, size_t max = 256) {
    return sz_levenshtein_serial(left, lz, right, rz, max, &default_alloc);
};

void test_lev() {
    auto check = [](const char* s1, const char* s2, size_t exp) {
        auto result = lev(s1, strlen(s1), s2, strlen(s2), 200);
        assert(result == exp);
        result = lev(s2, strlen(s2), s1, strlen(s1), 200);
        assert(result == exp);
    };

    check("abc", "+abc", 1);
}

int main(int argc, char** argv) {
    test_lev();
}
