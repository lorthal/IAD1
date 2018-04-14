#include "stdafx.h"
#include "SigmoidFunction.h"
#include "math.h"

double SigmoidFunction::GetResult(double input)
{
	return 1 / (1 + exp(-input));
}

double SigmoidFunction::GetDerivativeFromInput(double input)
{
	return GetResult(input) * (1 - GetResult(input));
}

double SigmoidFunction::GetDerivativeFromOutput(double output)
{
	return (1 - output) * output;
}
