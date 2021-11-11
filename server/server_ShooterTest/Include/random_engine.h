#pragma once
#include <random>
#include"singleton.h"


class RandomEngine : public Singleton<RandomEngine> {
  private:
    std::default_random_engine dre;

  public:
    std::default_random_engine &GetDre();
};
