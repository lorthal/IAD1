#pragma once
#include "IActivationFunction.h"
class IdentityFunction :
	public IActivationFunction
{
public:
	IdentityFunction() {}
	~IdentityFunction() {}

	double GetResult(const double &input) override;
	double GetDerivativeFromOutput(const double &output) override;
	double GetDerivativeFromInput(const double &input) override;
};

