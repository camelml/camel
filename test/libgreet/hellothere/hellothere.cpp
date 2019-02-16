#include "hellothere.hpp"

Hellothere::Hellothere(Hello &hello, There &there)
{
    hellothere = hello.hello + " " + there.there;
}