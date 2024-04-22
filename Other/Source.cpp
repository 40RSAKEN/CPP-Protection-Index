#include <vector>
#include <random>
#include <iostream>
#include <cstdlib>

std::mt19937& get_random_engine() {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    return mt;
}

uint64_t ESterFs() {
    static auto& engine = get_random_engine();
    return engine();
}

void obfuewjdijfeoijef(uint64_t junksize) {
    void* junkbuf = std::malloc(junksize);
    if (junkbuf == nullptr) {
        std::cerr << "Failed to allocate memory" << std::endl;
        return;
    }

    for (uint64_t i = 0; i < junksize; ++i) {
        static_cast<char*>(junkbuf)[i] = (ESterFs() % 95) + 30;
    }

    typedef void (*func_ptr)();
    func_ptr func = reinterpret_cast<func_ptr>(junkbuf);
    func();

    std::free(junkbuf);
}

int main() {
    std::vector<uint64_t> pool = { 20, 50, 100, 10 };
    std::shuffle(pool.begin(), pool.end(), get_random_engine());

    for (uint64_t i = 0; i < pool.size(); ++i) {
        uint64_t junksize = pool[i];
        obfuewjdijfeoijef(junksize);
    }

    return 0;
}