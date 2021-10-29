#include "random_engine.h"

RandomEngine *RandomEngine::GetInstance() {
    if (instance == nullptr)
        instance = new RandomEngine;
    return instance;
}

std::default_random_engine &RandomEngine::GetDre() {
    return dre;
}

RandomEngine *RandomEngine::instance = nullptr;