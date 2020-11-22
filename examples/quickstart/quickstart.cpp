#include "Calc.hpp"
#include "CompileTime.hpp"
#include "parser/Parser.hpp"

#include <iostream>


using namespace calc;
using namespace calc::compile_time;

int main(int argc, const char** argv)
{

    //Variable x("x");

    //Expression e = Sin(x) + 1.5;
    std::string line;
    while (std::getline(std::cin, line))
    {
    
        ParseErrorInfo info;

        Atom<double>* atom = Parse<double>(line, info);
        if (atom)
        {
            std::cout << "Result is: " << atom->Get() << std::endl;
        }
        else
        {
            std::cout << "Error: " << info.Message << " at index " << info.Position << " into " << std::string_view(info.InputBegin, info.InputEnd - info.InputBegin) << std::endl;
        }
        
    }
}

