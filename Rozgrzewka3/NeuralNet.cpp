#include "stdafx.h"
#include "NeuralNet.h"
#include "IdentityFunction.h"
#include "InputNeuron.h"
#include <iostream>

std::vector<double> NeuralNet::GetKeysFromMap(const std::vector<std::pair<double, double>> &map)
{
	std::vector<double> v;
	for (auto const& element : map)
	{
		v.push_back(element.first);
	}
	return v;
}

std::vector<double> NeuralNet::GetValuesFromMap(const std::vector<std::pair<double, double>> & map)
{
	std::vector<double> v;
	for (auto const& element : map)
	{
		v.push_back(element.second);
	}
	return  v;
}

NeuralNet::NeuralNet(std::vector<int> layersConfiguration, IActivationFunction* func, double learningRate) : leariningRate(learningRate)
{
	int layersCount = layersConfiguration.size();
	layers = std::vector<Layer>();
	CreateInputLayer(layersConfiguration[0]);
	for(int i = 1; i < layersCount - 1; i++)
	{
		Layer layer = Layer(layersConfiguration[i], func, false, true);
		layer.SetConnections(&layers.back());
		layers.push_back(layer);
	}
	CreateOutputLayer(layersConfiguration[layersCount - 1]);
}

void NeuralNet::Train(std::vector<std::pair<double, double>> initData)
{
	InitInputLayer(initData);
	Predict(layers.back(), initData);
	ComputeOutputLayerError(layers.back(), initData);
	BackPropagation();
}

void NeuralNet::CreateInputLayer(int inputNeuronsCount)
{
	layers.push_back(Layer(inputNeuronsCount, new IdentityFunction(), true, true));
}

void NeuralNet::CreateOutputLayer(int outputNeuronsCount)
{
	Layer layer = Layer(outputNeuronsCount, new IdentityFunction(), false, false);
	layer.SetConnections(&layers.back());
	layers.push_back(layer);
}

void NeuralNet::InitInputLayer(std::vector<std::pair<double, double>> initData)
{
	auto inputLayer = layers[0];
	int size = inputLayer.GetIsWithBias() ? inputLayer.GetNeurons().size() - 1 : inputLayer.GetNeurons().size();

	for (int i = 0; i < size; i++)
	{
		static_cast<InputNeuron*>(&(inputLayer.GetNeurons()[i]))->initialInput = GetKeysFromMap(initData)[i];
	}
}

void NeuralNet::Predict(Layer &outputLayer, std::vector<std::pair<double, double>> initData)
{
	for(auto layer : layers)
	{
		for(auto neuron : layer.GetNeurons())
		{
			neuron.ComputeOutput();
		}
	}

	std::cout << "--Output--" << std::endl;

	for(int i = 0; i < outputLayer.GetNeurons().size(); i++)
	{
		auto neuron = outputLayer.GetNeurons()[i];
		double result = neuron.GetOutput();
		std::cout.precision(10);
		std::cout << "Input:     " << std::fixed << GetKeysFromMap(initData)[i] << std::endl;
		std::cout << "Expected:  " << std::fixed << GetValuesFromMap(initData)[i] << std::endl;
		std::cout << "Predicted: " << std::fixed << result << std::endl << std::endl;
	}
}

void NeuralNet::ComputeOutputLayerError(Layer outputLayer, std::vector<std::pair<double, double>> initData)
{
	for(int i = 0; i < outputLayer.GetNeurons().size(); i++)
	{
		auto neuron = outputLayer.GetNeurons()[i];
		double output = neuron.GetOutput();
		double neuronError = neuron.activationFunction->GetDerivativeFromOutput(output) * (GetValuesFromMap(initData)[i] - output);
		neuron.SetNeuronError(neuronError);
		neuron.AddErrorToNeighbours();
	}
}

void NeuralNet::BackPropagation()
{
	for(int i = layers.size() - 2; i >= 0; i--)
	{
		layers[i].ComputeNeuronErrors();
	}

	for(auto layer : layers)
	{
		layer.UpdateWeights(leariningRate);
	}
}
