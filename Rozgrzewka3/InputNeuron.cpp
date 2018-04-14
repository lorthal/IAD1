#include "stdafx.h"
#include "InputNeuron.h"


InputNeuron::InputNeuron(IActivationFunction *activation, bool isBias = false) : Neuron(activation), isBias(isBias), initialInput(0)
{
}

InputNeuron::~InputNeuron()
{
}

void InputNeuron::ComputeOutput()
{
	output = activationFunction->GetResult(initialInput);
}
