#pragma once
#include <string>
#include <vector>

namespace Leyla{

    typedef std::string invalid_result;
    typedef std::string optional_arg_name;
    typedef std::string command_name;
    typedef std::vector<double> double_vector;
    typedef std::vector<std::string> string_vector;
    typedef std::vector<long> long_vector;

    

    enum class Type{
        l_long,
        l_double,
        l_string,
        l_long_vector,
        l_double_vector,
        l_string_vector,
        l_empty_vector,
        l_invalid_result,
        l_optional_arg_name,
        l_command_name,
    };

}