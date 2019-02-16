#ifndef HELLOTHERE_HPP_INCLUDED
#define HELLOTHERE_HPP_INCLUDED
#include "hello.hpp"
#include "there.hpp"
#include <iostream>

class Hellothere
{
  private:
    /* data */
  public:
    std::string hellothere;
    Hellothere(Hello &hello, There &there);
};

#endif