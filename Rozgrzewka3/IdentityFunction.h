#pragma once
#include "IActivationFunction.h"
class IdentityFunction :
	public IActivationFunction
{
public:
	IdentityFunction() {}
	~IdentityFunction() {}

	double GetResult(double input) override;
	double GetDerivativeFromOutput(double output) override;
	double GetDerivativeFromInput(double input) override;
};

