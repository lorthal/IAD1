#include "stdafx.h"
#include "SigmoidFunction.h"
#include "math.h"

double SigmoidFunction::GetResult(const double &input)
{
	return 1 / (1 + exp(-input));
}

double SigmoidFunction::GetDerivativeFromInput(const double &input)
{
	return GetResult(input) * (1 - GetResult(input));
}

double SigmoidFunction::GetDerivativeFromOutput(const double &output)
{
	return (1 - output) * output;
}
