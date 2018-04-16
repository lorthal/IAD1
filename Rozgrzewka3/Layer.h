#pragma once
#include <vector>
#include "Neuron.h"

class Layer
{
public:
	Layer(const int &neuronsCount, IActivationFunction *activation, bool isInputLayer, bool isWithBias);
	~Layer();

	void SetConnections(const Layer &previousLayer);

	void ComputeNeuronErrors();

	void UpdateWeights(const double &learningRate);

	bool GetIsWithBias() const { return isWithBias; }

	std::vector<Neuron*> GetNeurons() const { return neurons; }

private:
	std::vector<Neuron*> neurons;
	bool isWithBias;
};

