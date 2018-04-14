#pragma once
#include "IActivationFunction.h"
class SigmoidFunction :
	public IActivationFunction
{
public:
	SigmoidFunction() {}
	~SigmoidFunction() {}

	double GetResult(double input) override;
	double GetDerivativeFromOutput(double output) override;
	double GetDerivativeFromInput(double input) override;
	
};

