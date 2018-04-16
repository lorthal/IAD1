#pragma once
#include "IActivationFunction.h"
class SigmoidFunction :
	public IActivationFunction
{
public:
	SigmoidFunction() {}
	~SigmoidFunction() {}

	double GetResult(const double &input) override;
	double GetDerivativeFromOutput(const double &output) override;
	double GetDerivativeFromInput(const double &input) override;
	
};

