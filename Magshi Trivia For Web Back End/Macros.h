#pragma once
#define SINGLETON_GENERATOR(ClassName)         \
public:                                      \
    static ClassName& getInstance() {        \
        static ClassName instance;           \
        return instance;                     \
    }                                        \
private:                                     \
    ClassName() = default;                   \
    ~ClassName() = default;                  \
    ClassName(const ClassName&) = delete;    \
    ClassName& operator=(const ClassName&) = delete; \
    ClassName(ClassName&&) = delete;         \
    ClassName& operator=(ClassName&&) = delete;