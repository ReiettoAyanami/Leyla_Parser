#pragma once
#include <string>
#include <functional>
#include "Parsout.hpp"
#include "Types.hpp"
namespace Leyla{

class Argument{

    public:
        std::string name;
        std::function<void(Parse_Result)> executor;
        std::function<void()> invalid_result_executor;

        bool valid;
        bool mandatory;
        Type type;
        
        Argument is_mandatory(bool);
        Argument executes(std::function<void(Parse_Result)>);
        Argument executes_on_invalid_result(std::function<void()>);

        Argument(std::string name, Type type) : executor(executor), type(type){}
        ~Argument();
};

Argument Argument::is_mandatory(bool mandatory){

    this -> mandatory = mandatory;

    return *this;
} 

Argument Argument::executes(std::function<void(Parse_Result)> executor){

    this -> executor = executor;

    return *this;


}

Argument Argument::executes_on_invalid_result(std::function<void()> invalid_result_executor){

    this -> invalid_result_executor = invalid_result_executor;

    return *this;

}

}

