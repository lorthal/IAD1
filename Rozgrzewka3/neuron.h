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

	double GetOutput() const { return output; }

	void AddConnection(Connection &connection);

	void AddErrorToNeighbours();

	void UpdateWeights(const double &learningRate);

	void ComputeNeuronError();

	virtual void ComputeOutput();

	void SetNeuronError(const double &neuronError) { this->neuronError = neuronError; }

protected:
	double GetInputSum();
	double output;

private:

	double neuronError;
	double neighbourErrorSum;

	std::vector<Connection> connections;

	double momentum = .6;
};
