#pragma once

#include "Calc.hpp"

#include <string_view>
#include <cstring>

namespace calc {

    struct ParseErrorInfo {
        char Message[40];
        const char* InputBegin;
        const char* InputEnd;
        int Position;
        bool Error = false;

        inline operator bool() const { return Error; }

        inline void SetError(const char* message, const char* inputBegin, const char* inputEnd, int pos)
        {
            Error = true;
            std::strncpy(Message, message, sizeof(Message));
            InputBegin = inputBegin;
            InputEnd = inputEnd;
            Position = pos;
        }

        inline void SetError(const char* inputBegin, const char* inputEnd, int pos)
        {
            Error = true;
            //We assume message was already written to. Use the other function when using error messages that are string literals
            InputBegin = inputBegin;
            InputEnd = inputEnd;
            Position = pos;
        }


    };

    template<typename T>
    [[nodiscard]] Atom<T>* Parse(std::string_view expression, ParseErrorInfo& errorInfo);
}

#include "Parser.inl"

