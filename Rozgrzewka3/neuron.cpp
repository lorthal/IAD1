#include "stdafx.h"
#include "neuron.h"
#include "Connection.h"


Neuron::Neuron(IActivationFunction *activation) : activationFunction(activation), output(0), neuronError(0), neighbourErrorSum(0)
{

}


Neuron::~Neuron()
{
}

void Neuron::AddConnection(Connection &connection)
{
	connections.push_back(connection);
}

void Neuron::AddErrorToNeighbours()
{
	if (connections.empty()) return;
	for (auto& c : connections)
	{
		auto& neighbour = c.neuron;
		neighbour->neighbourErrorSum += c.weight * neuronError;
	}
}

void Neuron::UpdateWeights(const double &learningRate)
{
	for (auto& c : connections)
	{
		c.previousWeight = c.weight;
		c.weightDelta = learningRate * neuronError * c.neuron->output + momentum * c.previousWeightDelta;
		c.previousWeightDelta = c.weightDelta;
		c.weight = c.previousWeight + c.weightDelta;
	}
}

void Neuron::ComputeNeuronError()
{
	neuronError = activationFunction->GetDerivativeFromOutput(output) * neighbourErrorSum;
	neighbourErrorSum = 0;
}

void Neuron::ComputeOutput()
{
	output = activationFunction->GetResult(GetInputSum());
}

double Neuron::GetInputSum()
{
	double sum = 0;

	for (int i = 0; i < connections.size(); i++)
	{
		sum += connections[i].GetOutputXWeight();
	}
	return sum;
}
