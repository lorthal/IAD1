#pragma once
#include <vector>
#include "IActivationFunction.h"

class Connection;

class Neuron
{
public:
	Neuron(IActivationFunction* activation);
	virtual ~Neuron();

	IActivationFunction* activationFunction;

	double GetOutput() const { return output; }

	void AddConnection(Connection connection);

	void AddErrorToNeighbours();

	void UpdateWeights(double learningRate);

	void ComputeNeuronError();

	virtual void ComputeOutput();

	void SetNeuronError(double neuronError) { this->neuronError = neuronError; }

protected:
	double GetInputSum();
	double output;
	
private:
	
	double neuronError;
	double neighbourErrorSum;
	
	std::vector<Connection*> connections;

	double momentum = .6;
};