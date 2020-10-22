#include "Calc.hpp"

#include <iostream>


using namespace calc;

int main(int argc, const char** argv)
{
	DOperationAtom total(operations::Add<double>, { new DConstantAtom(1), new DOperationAtom(operations::Multiply<double>, { new DConstantAtom(2), new DConstantAtom(5) }) });

	std::cout << total.Get() << std::endl;
}

