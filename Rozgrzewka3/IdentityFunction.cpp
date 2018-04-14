#include "stdafx.h"
#include "IdentityFunction.h"

double IdentityFunction::GetResult(double input)
{
	return input;
}

double IdentityFunction::GetDerivativeFromOutput(double output)
{
	return 1;
}

double IdentityFunction::GetDerivativeFromInput(double input)
{
	return 1;
}
