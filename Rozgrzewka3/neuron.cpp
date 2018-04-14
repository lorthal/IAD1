#include "stdafx.h"
#include "Neuron.h"
#include "Connection.h"

Neuron::Neuron(IActivationFunction* activation) : activationFunction(activation), output(0), neuronError(0), neighbourErrorSum(0)
{
	connections = std::vector<Connection*>();
}


Neuron::~Neuron()
{
}

void Neuron::AddConnection(Connection connection)
{
	connections.push_back(&connection);
}

void Neuron::AddErrorToNeighbours()
{
	if(connections.empty()) return;
	for(auto c : connections)
	{
		auto connetion = *c;
		Neuron neighbour = connetion.neuron;
		neighbour.neighbourErrorSum += connetion.weight * neuronError;
	}
}

void Neuron::UpdateWeights(double learningRate)
{
	for (auto c : connections)
	{
		auto connetion = *c;
		Neuron neighbour = connetion.neuron;
		connetion.previousWeight = connetion.weight;
		connetion.weightDelta = learningRate * neuronError * neighbour.GetOutput() + momentum * connetion.previousWeightDelta;
		connetion.previousWeightDelta = connetion.weightDelta;
		connetion.weight = connetion.previousWeight + connetion.weightDelta;
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

	for(auto con : connections)
	{
		auto c = *con;
		Neuron n = c.neuron;
		sum += n.output * c.weight;
	}
	return sum;
}