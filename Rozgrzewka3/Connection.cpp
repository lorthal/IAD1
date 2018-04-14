#include "stdafx.h"
#include "Connection.h"


Connection::Connection(Neuron neuron, double weight) : neuron(neuron), weight(weight), previousWeight(0), weightDelta(0), previousWeightDelta(0)
{
}


Connection::~Connection()
{
}
