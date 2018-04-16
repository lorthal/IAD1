#include "stdafx.h"
#include "InputNeuron.h"

Connection::Connection(Neuron* neuron, const double& weight) : neuron(neuron), weight(weight), previousWeight(0), weightDelta(0), previousWeightDelta(0)
{

}

Connection::~Connection()
{
}

double Connection::GetOutputXWeight() const
{
	return neuron->GetOutput() * weight;
}

void Connection::UpdateWeight(const double &learningRate, const double &neuronError, const double &momentum)
{
	previousWeight = weight;
	weightDelta = learningRate * neuronError * neuron->GetOutput() + momentum * previousWeightDelta;
	previousWeightDelta = weightDelta;
	weight = previousWeight + weightDelta;
}
