#include "stdafx.h"
#include "Layer.h"
#include "InputNeuron.h"
#include <ctime>


Layer::Layer(const int &neuronsCount, IActivationFunction *activation, bool isInputLayer = false, bool isWithBias = true) : isWithBias(isWithBias)
{
	for (int i = 0; i < neuronsCount; i++)
	{
		if (isInputLayer)
		{
			neurons.push_back(new InputNeuron(activation, false));
		}
		else
		{
			neurons.push_back(new Neuron(activation));
		}
	}
	if (isWithBias)
	{
		InputNeuron *n = new InputNeuron(activation, true);
		n->initialInput = 1;
		neurons.push_back(n);
	}
}

Layer::~Layer()
{
}

void Layer::SetConnections(const Layer &previousLayer)
{
	if (&previousLayer == nullptr) return;
	srand(time(nullptr));

	for (auto i = 0; i < previousLayer.neurons.size(); i ++)
	{
		for(auto j = 0; j < neurons.size(); j++)
		{
			InputNeuron* in = dynamic_cast<InputNeuron*>(neurons[j]);
			if (in != nullptr && in->isBias)
			{
				continue;
			}
			double weight = static_cast<double>(rand() / static_cast<double>(RAND_MAX / (1 - (-1))));
			Neuron& n = *previousLayer.neurons[i];
			Connection connection = Connection(&n, weight);
			neurons[j]->AddConnection(connection);
		}
	}
}

void Layer::ComputeNeuronErrors()
{
	for(auto i = 0; i < neurons.size(); i++)
	{
		Neuron& n = *neurons[i];
		n.ComputeNeuronError();
		n.AddErrorToNeighbours();
	}
}

void Layer::UpdateWeights(const double &learningRate)
{
	for (auto i = 0; i < neurons.size(); i++)
	{
		neurons[i]->UpdateWeights(learningRate);
	}
}
