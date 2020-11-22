
#include "Calc.hpp"

namespace calc {

    namespace internal {

        template<typename T>
        struct BasicWorkingString
        {
            const T* const Begin;
            const T* const End;
            const T* Current;

            BasicWorkingString(const T* begin, const T* end)
                : Begin(begin), Current(begin), End(end)
            {
            }


            T Get () { return *Current; }
            inline std::size_t Pos() const { return Current - Begin; }

            bool IsValid() { return Current != End; }
            void Advance() { Current++; }

            bool StartsWith(const T* other)
            {
                const T* c = Current;

                while (*other)
                {
                    //We found a difference
                    if (*c != *other) return false;
                    //We are at the end of this string IE this length < other other length
                    if (c == End) return false;
                    
                    c++;
                    other++;
                }
                Current = c;
                return true;
            }
        };

        using WorkingString = BasicWorkingString<char>;

        inline bool IsDigit(char c)
        {
            return c >= '0' && c <= '9';
        }

        template<typename T>
        Atom<T>* ParseLiteral(WorkingString& s, ParseErrorInfo& errorInfo)
        {
            T value = 0;
            T power = 0;
#if 1//Regular approach
            while (s.IsValid())
            {
                if (IsDigit(s.Get()))
                {
                    if (power)
                    {
                        value = value + (s.Get() - '0') / power;
                    }
                    else
                    {
                        value = value * 10 + (s.Get() - '0');
                    }
                    
                    //If we have already encountered the decimal point then increase the value we divide by when finishing
                    if (power)
                    {
                        power *= 10;
                    }
                }
                else if (s.Get() == '.')
                {
                    power = 1;
                }
                else
                {
                    break;
                }
                s.Advance();
            }

#else
            //possibly faster approach for decimals. Store what to divide by to scale down to where the decimal point
            //instead of dividing by 10 and adding every time

            while (s.IsValid())
            {
                if (IsDigit(s.Get()))
                {
                    value = value * 10 + (s.Get() - '0');

                    //If we have already encountered the decimal point then increase the value we divide by when finishing
                    if (power)
                    {
                        power *= 10;
                    }
                }
                else if (s.Get() == '.')
                {
                    power = 1;
                }
                else
                {
                    break;
                }
                s.Advance();
            }
            if (power)
            {
                value /= power;
            }

#endif
            return new ConstantAtom<T>(value);

        }

        template<typename T>
        Atom<T>* ParseAtom(WorkingString& s, ParseErrorInfo& errorInfo);


        template<typename T>
        Atom<T>* ParseFactors(WorkingString& s, ParseErrorInfo& errorInfo)
        {
            Atom<T>* left = ParseAtom<T>(s, errorInfo);
            if (!left) return nullptr;
            while (s.IsValid())
            {
                if (s.Get() == '*')
                {
                    s.Advance();
                    Atom<T>* right = ParseAtom<T>(s, errorInfo);
                    if (!right) return nullptr;
                    left = new OperationAtom(operations::Multiply<T>, { left, right });
                    continue;
                }
                else if (s.Get() == '/')
                {
                    s.Advance();
                    Atom<T>* right = ParseAtom<T>(s, errorInfo);
                    if (!right) return nullptr;
                    left = new OperationAtom(operations::Divide<T>, { left, right });
                    continue;
                }
                return left;
            }
            return left;
        }

        template<typename T>
        Atom<T>* ParseSummands(WorkingString& s, ParseErrorInfo& errorInfo)
        {
            Atom<T>* left = ParseFactors<T>(s, errorInfo);
            if (!left) return nullptr;
            while (s.IsValid())
            {
                if (s.Get() == '+')
                {
                    s.Advance();
                    Atom<T>* right = ParseFactors<T>(s, errorInfo);
                    if (!right) return nullptr;
                    left = new OperationAtom(operations::Add<T>, { left, right });
                    continue;
                }
                else if (s.Get() == '-')
                {
                    s.Advance();
                    Atom<T>* right = ParseFactors<T>(s, errorInfo);
                    if (!right) return nullptr;
                    left = new OperationAtom(operations::Subtract<T>, { left, right });
                    continue;
                }
                return left;
            }
            return left;
        }


        template<typename T>
        Atom<T>* ParseUnaryOperation(WorkingString& s, ParseErrorInfo& errorInfo, GeneralOperation<T> operation)
        {
            Atom<T>* arg = ParseAtom<T>(s, errorInfo);
            if (!arg) return nullptr;
            return new OperationAtom(operation, { arg });
        }


        template<typename T>
        Atom<T>* CheckClosingBracket(WorkingString& s, ParseErrorInfo& errorInfo, Atom<T>* retult)
        {
            if (s.Get() == ')')
            {
                s.Advance();
                return retult;
            }
            errorInfo.SetError("Unbalanced brackets", s.Begin, s.End, s.Pos());
            return nullptr;
        }


        template<typename T>
        Atom<T>* ParseAtom(WorkingString& s, ParseErrorInfo& errorInfo)
        {
            if (!s.IsValid()) return nullptr;


            if (s.Get() == '(')
            {
                s.Advance();
                Atom<T>* atom = ParseSummands<T>(s, errorInfo);
                return CheckClosingBracket(s, errorInfo, atom);
            }
            else if (IsDigit(s.Get()))
            {
                Atom<T>* atom = ParseLiteral<T>(s, errorInfo);
                return atom;
            }
            else if (s.StartsWith("sin("))
            {
                Atom<T>* atom = ParseUnaryOperation<T>(s, errorInfo, operations::Sin<T>);
                return CheckClosingBracket(s, errorInfo, atom);
            }
            else if (s.StartsWith("cos("))
            {
                Atom<T>* atom = ParseUnaryOperation<T>(s, errorInfo, operations::Cos<T>);
                return CheckClosingBracket(s, errorInfo, atom);
            }
            else if (s.StartsWith("tan("))
            {
                Atom<T>* atom = ParseUnaryOperation<T>(s, errorInfo, operations::Tan<T>);
                return CheckClosingBracket(s, errorInfo, atom);
            }
            else
            {
                errorInfo.SetError("Unexpected char", s.Begin, s.End, s.Pos());
                return nullptr;
            }


        }

    }

    template<typename T>
    Atom<T>* Parse(std::string_view expression, ParseErrorInfo& errorInfo)
    {
        internal::WorkingString str(expression.begin(), expression.end());

        return internal::ParseSummands<T>(str, errorInfo);
    }
}


