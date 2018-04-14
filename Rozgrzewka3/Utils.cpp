#include "stdafx.h"
#include "Utils.h"
#include <cmath>


Utils::Utils()
{
}


Utils::~Utils()
{
}

double Utils::Sigmoid(double x)
{
	return 1 / (1 + exp(-x));
}

double Utils::SigmoidDerivative(double x)
{
	return Sigmoid(x) * (1 - Sigmoid(x));
}
