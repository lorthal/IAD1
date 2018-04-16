#include "stdafx.h"
#include "IdentityFunction.h"

double IdentityFunction::GetResult(const double & input)
{
	return input;
}

double IdentityFunction::GetDerivativeFromOutput(const double & output)
{
	return 1;
}

double IdentityFunction::GetDerivativeFromInput(const double & input)
{
	return 1;
}
