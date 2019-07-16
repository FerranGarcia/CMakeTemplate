#include <string>
#include <boost/any.hpp>

#pragma once

namespace foo
{
    void help(std::string argv);
    double mysqrt(const int& inputValue);
    bool is_int(const boost::any & operand);
}