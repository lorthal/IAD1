#pragma once
#include <vector>
#include "IActivationFunction.h"
#include "Connection.h"


class Neuron
{
public:
	Neuron(IActivationFunction *activation);
	virtual ~Neuron();

	IActivationFunction * activationFunction;

	double output;

	void AddConnection(Connection &connection);

	void AddErrorToNeighbours();

	void UpdateWeights(const double &learningRate);

	void ComputeNeuronError();

	virtual void ComputeOutput();

	void SetNeuronError(double neuronError) { this->neuronError = neuronError; }

protected:
	double GetInputSum();

private:

	double neuronError;
	double neighbourErrorSum;

	std::vector<Connection> connections;

	double momentum = .6;
};
