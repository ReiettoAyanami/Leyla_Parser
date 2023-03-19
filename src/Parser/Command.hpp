
#pragma once

#include "Parsout.hpp"
#include "Argument.hpp"
#include "Types.hpp"
#include <string>
#include <vector>

namespace Leyla
{

    class Command{
        private:

            std::string name;
            std::vector<Argument> args;
            std::function<void(std::vector<Parse_Result>)> executor;
            std::function<void()> invalid_command_executor;

        public:

            bool is_valid;

            Command new_argument(Argument);
            Command executes(std::function<void(std::vector<Parse_Result>)>);
            Command executes_on_invalid(std::function<void()>);

            void execute(std::vector<Parse_Result>);

            Command(std::string name) : name(name){}
            ~Command(); 


};


Command Command::new_argument(Argument arg){

    this -> args.push_back(arg);
    return *this;

}


Command Command::executes(std::function<void(std::vector<Parse_Result>)> executor){

    this -> executor = executor;
    
    return *this;

}

Command Command::executes_on_invalid(std::function<void()> executor){

    this -> invalid_command_executor = executor;

    return *this;

}

void execute(){}


}