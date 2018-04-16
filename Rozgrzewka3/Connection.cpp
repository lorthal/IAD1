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
	return neuron->output * weight;
}
