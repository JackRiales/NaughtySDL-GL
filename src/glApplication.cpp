#include "glApplication.hpp"
using namespace ngl;

glApplication::glApplication (Uint8 glMajorVersion, Uint8 glMinorVersion, std::string header, unsigned int width, unsigned int height):
_width  (width),
_height (height),
_header (header)
{
    ;
}

glApplication::~glApplication()
{
    ;
}
