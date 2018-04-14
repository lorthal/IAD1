#pragma once
class IActivationFunction
{
public:
	IActivationFunction() {}
	virtual ~IActivationFunction() {}

	virtual double GetResult(double input) { return 99; }
	virtual double GetDerivativeFromInput(double input) { return 99; }
	virtual double GetDerivativeFromOutput(double output) { return 99; }
};