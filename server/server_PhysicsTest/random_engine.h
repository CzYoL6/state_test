#pragma once
#include <random>

class RandomEngine {
  private:
    static RandomEngine *instance;
    std::default_random_engine dre;

  public:
    static RandomEngine *GetInstance();
    std::default_random_engine &GetDre();
};
