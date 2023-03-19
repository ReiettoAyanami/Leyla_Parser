#pragma once
#include <vector>
#include <string>
#include <any>
#include "Types.hpp"

namespace Leyla
{

    class Parse_Result
    {

    private:
        std::any value;

    public:
        Type type;
        bool is_valid;


        template<typename T>T get_value();
        
        Parse_Result(){};
        Parse_Result(Type type, std::any value, bool is_valid = true) : type(type), value(value), is_valid(is_valid){};
        ~Parse_Result(){};
    };


template <typename T>
T Parse_Result::get_value(){

    return std::any_cast<T>(this -> value);

}


class Parsed_Results{

    public:
        Parse_Result command_name;
        std::vector<Parse_Result> results;

        Parsed_Results(std::vector<Parse_Result> results){

            for(int i = 0; i < results.size(); ++i){

                if(results[i].type == Type::l_command_name){
                    this -> command_name = results[i];
                    results.erase(results.begin() + i);

                }

            }

            this -> results = results;

        }

};


}


