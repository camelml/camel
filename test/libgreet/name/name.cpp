#include "name.hpp"

Name::Name(First &first, Last &last)
{
    name = first.name + " " + last.name;
}