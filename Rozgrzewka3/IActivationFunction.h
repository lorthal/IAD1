#pragma once
class IActivationFunction
{
public:
	IActivationFunction() {}
	virtual ~IActivationFunction() {}

	virtual double GetResult(const double &input) { return 99; }
	virtual double GetDerivativeFromInput(const double &input) { return 99; }
	virtual double GetDerivativeFromOutput(const double &output) { return 99; }
};