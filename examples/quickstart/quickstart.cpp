#include "Calc.hpp"

#include <iostream>


using namespace calc;

int main(int argc, const char** argv)
{
	OperationAtom<double> total(operations::Add<double>, { new ConstantAtom<double>(11), 
		new OperationAtom<double>(operations::Multiply<double>, { new ConstantAtom<double>(2), new ConstantAtom<double>(5) })
	});

	std::cout << total.Get() << std::endl;
}

