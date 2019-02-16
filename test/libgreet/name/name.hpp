#ifndef NAME_HPP_INCLUDED
#define NAME_HPP_INCLUDED
#include <iostream>
#include "first.hpp"
#include "last.hpp"

class Name
{

public:
  std::string name;
  Name(First &first, Last &last);
};

#endif