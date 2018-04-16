#pragma once

class Neuron;

class Connection
{
public:
	Connection(Neuron *neuron, const double &weight);
	~Connection();

	double GetOutputXWeight() const;
	//void UpdateWeight(const double &learningRate, const double &neuronError, const double &momentum);

	Neuron * neuron;
	double weight;
	double previousWeight;
	double weightDelta;
	double previousWeightDelta;
	
};

