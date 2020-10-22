#include "Calc.hpp"

#include <iostream>


using namespace calc;

int main(int argc, const char** argv)
{
	DBinaryOperationAtom total(operations::Add<double>, new DConstantAtom(1), new DConstantAtom(1));

	std::cout << total.Get() << std::endl;
}

