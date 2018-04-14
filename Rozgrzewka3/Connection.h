#pragma once
#include "Neuron.h"

class Connection
{
public:
	Connection(Neuron neuron, double weight);
	~Connection();

	Neuron neuron;
	double weight;
	double previousWeight;
	double weightDelta;
	double previousWeightDelta;
	
};

