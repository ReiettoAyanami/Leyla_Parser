#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <functional>
#include <map>
#include <any>
#include "Types.hpp"
#include "Parsout.hpp"

#define _LEYLA_ARRAY_START '['
#define _LEYLA_ARRAY_END ']'
#define _LEYLA_ARRAY_SEPARATOR ','

#define _LEYLA_STR_DEF_OPTION_1 '\''
#define _LEYLA_STR_DEF_OPTION_2 '\"'
#define _LEYLA_STR_SPACE_REPLACER '\u001A'
#define _LEYLA_STR_ARR_REPLACER '\u0091'

namespace Leyla
{

    class Parser
    {

    private:
        char prefix;
        char arg_prefix;

        Parse_Result get_converted_arg(std::string);
        std::vector<std::string> pre_parse(std::string);

    public:
        Parser(char, char);
        ~Parser();

        Parsed_Results parse(std::string);
    };

    Parser::Parser(char prefix, char arg_prefix)
    {

        this->prefix = prefix;
        this->arg_prefix = arg_prefix;
    };

    Parser::~Parser() {}

    Parse_Result Parser::get_converted_arg(std::string arg)
    {

        if (arg[0] == this->prefix)
            return Parse_Result(Type::l_invalid_result, arg);

        if ((std::isdigit(arg[0]) || std::isdigit(arg[std::min<long>(1l, arg.size() - 1)])) && arg[0] != _LEYLA_ARRAY_START)
        {

            // Floating point
            if (arg.find_first_of('.') != std::string::npos)
            {

                return Parse_Result(Type::l_double, std::any(std::stod(arg)));
            }
            else
            { // Integer

                return Parse_Result(Type::l_long, std::any(std::stol(arg)));
            }
        }
        // arg
        else if (!std::isdigit(arg[std::min<long>(1l, arg.size() - 1)]) && arg[0] == this->arg_prefix)
        {

            arg.erase(std::remove(arg.begin(), arg.end(), this->arg_prefix), arg.end());

            // for(int i = 0; i < this -> arg_actions.size(); ++i){

            //     //std::cout << "Args" << std::endl;
            //     if(this -> arg_actions[i].name == arg) return std::any(this-> arg_actions[i].executor);

            // }

            // return std::any(std::function<T>( [](){} ));

            return Parse_Result(Type::l_optional_arg_name, std::any(arg));
        }
        else if (arg[0] == _LEYLA_ARRAY_START && arg[arg.size() - 1] == _LEYLA_ARRAY_END)
        {
            

            arg.erase(std::remove(arg.begin(), arg.end(), _LEYLA_ARRAY_START), arg.end());
            arg.erase(std::remove(arg.begin(), arg.end(), _LEYLA_ARRAY_END), arg.end());

            if(!arg.size()) return Parse_Result(Type::l_empty_vector, arg);

            std::stringstream argstream(arg);
            std::string segment;
            std::vector<std::string> args;
            while (std::getline(argstream, segment, _LEYLA_ARRAY_SEPARATOR))
            {

                args.push_back(segment);
            }

            std::cout << arg << std::endl;

            if (std::isdigit(args[0][0]) || std::isdigit(args[0][std::min<long>(1l, arg.size() - 1)]))
            {

                if (args[0].find_first_of('.') != std::string::npos)
                {
                    std::vector<double> parsed_d;
                    for (auto &p : args)
                        parsed_d.push_back(std::stod(p));

                    return Parse_Result(Type::l_double_vector, std ::any(parsed_d));
                }
                else
                {

                    std::vector<long> parsed_l;
                    for (auto &p : args)
                        parsed_l.push_back(std::stol(p));
                    return Parse_Result(Type::l_long_vector, std::any(parsed_l));
                }
            }
            else
            {

                return Parse_Result(Type::l_string_vector, std::any(args));
            }
        }
        else
        {

            return Parse_Result(Type::l_string, std::any(arg));
        }
    }

    // One thing i found out while writing a parser is that is really annoying
    // :)

    Parsed_Results Parser::parse(std::string input)
    {

        std::stringstream s_input;
        std::vector<std::string> splitted;
        std::vector<Parse_Result> typed_args;
        std::string temp;

        // remove spaces in arrays

        bool in_string = false;
        char current_string_opener;

        for (int i = 0; i < input.size(); ++i)
        {

            if ((input[i] == _LEYLA_STR_DEF_OPTION_1 || input[i] == _LEYLA_STR_DEF_OPTION_2) && !in_string)
            {
            
                in_string = true;
                current_string_opener = input[i];
                continue;
            }

            if (in_string && input[i] == current_string_opener)
            {

                in_string = false;
                current_string_opener = 0;
                continue;

            }

            if (in_string && input[i] != current_string_opener)
            {
                if (input[i] == ' ')
                    std::replace(input.begin() + i, input.begin() + i + 1, ' ', _LEYLA_STR_SPACE_REPLACER);
            }

            
        }

        

        if (in_string)
        {
            
            typed_args.push_back(Parse_Result(Type::l_invalid_result, std::any(input)));
            return typed_args;
        }
        
        in_string = false;
        current_string_opener = 0;
        bool in_array = false;
        for (int i = 0; i < input.size(); ++i)
        {
            if ((input[i] == _LEYLA_STR_DEF_OPTION_1 || input[i] == _LEYLA_STR_DEF_OPTION_2) && !in_string)
            {
            
                in_string = true;
                current_string_opener = input[i];
                continue;
            }

            if (in_string && input[i] == current_string_opener)
            {

                in_string = false;
                current_string_opener = 0;
                continue;

            }

            if(!in_string){

                if ((input[i] == _LEYLA_ARRAY_START || in_array) && input[i] != _LEYLA_ARRAY_END)
                {

                    in_array = true;
                    if (input[i] == ' ')
                        input.erase(input.begin() + i);
                }
                else if (input[i] == _LEYLA_ARRAY_END)
                    in_array = false;
            }
        }

        if (in_array)
        {

            typed_args.push_back(Parse_Result(Type::l_invalid_result, std::any(input)));
            return typed_args;
        }

        s_input = std::stringstream(input);

        while (s_input >> temp)
        {
            splitted.push_back(temp);
        }

        if (this->prefix != splitted[0][0])
        {

            typed_args.push_back(Parse_Result(Type::l_invalid_result, std::any(input)));
        }
        else
        {

            splitted[0].replace(0, 1, "");

            typed_args.push_back(Parse_Result(Type::l_command_name, splitted[0]));

            for (int i = 1; i < splitted.size(); ++i)
            {
                
                std::replace(splitted[i].begin(), splitted[i].end(), _LEYLA_STR_SPACE_REPLACER, ' ');
                std::cout << splitted[i] << std::endl;
                typed_args.push_back(this->get_converted_arg(splitted[i]));
            }
        }

        return Parsed_Results(typed_args);
    }
}