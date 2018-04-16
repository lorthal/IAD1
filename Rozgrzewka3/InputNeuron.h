#pragma once
#include "neuron.h"

class InputNeuron :
	public Neuron
{
public:
	InputNeuron(IActivationFunction *activation, bool isBias);
	~InputNeuron();

	void ComputeOutput() override;

	bool isBias;

	double initialInput;
};

