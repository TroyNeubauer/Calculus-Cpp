#pragma once

#include <string_view>


namespace calc {

    namespace compile_time {


        struct Variable {

            Variable(const std::string_view& name) : Name(name) {}
            Variable(const char* name) : Name(name) {}

            const std::string_view Name;

        };



    }

}


