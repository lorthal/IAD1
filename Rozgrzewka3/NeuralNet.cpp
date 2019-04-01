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

NeuralNet::NeuralNet(const std::vector<int> &layersConfiguration, IActivationFunction *func, IActivationFunction *funcout, const double &learningRate, const double &momentum, const bool &bias) : leariningRate(learningRate)
{
	IActivationFunction * identity = new IdentityFunction();
	int layersCount = layersConfiguration.size();
	CreateInputLayer(layersConfiguration[0], identity, bias);
	for (int i = 1; i < layersCount - 1; i++)
	{
		Layer layer = Layer(layersConfiguration[i], func, false, bias);
		layer.SetConnections(layers.back());
		layers.push_back(layer);
	}
	CreateOutputLayer(layersConfiguration[layersCount - 1], funcout);

	SetMomentum(momentum);
}

void NeuralNet::Train(const std::vector<std::pair<double, double>> &initData)
{
	InitInputLayer(initData);
	Predict(layers.back(), initData);
	ComputeOutputLayerError(layers.back(), initData);
	BackPropagation();
}

double NeuralNet::ComputeError(const std::vector<std::pair<double, double>> &initData)
{
	double error = 0;
	for (int i = 0; i < layers.back().GetNeurons().size(); i ++)
	{
		error += (layers.back().GetNeurons()[i]->output - initData[i].second) * (layers.back().GetNeurons()[i]->output - initData[i].second);
	}
	error /= 2;
	return error;
}

void NeuralNet::CreateInputLayer(const int &inputNeuronsCount, IActivationFunction * func, const bool &bias)
{
	layers.push_back(Layer(inputNeuronsCount, func, true, bias));
}

void NeuralNet::CreateOutputLayer(const int &outputNeuronsCount, IActivationFunction * func)
{
	Layer layer = Layer(outputNeuronsCount, func, false, false);
	layer.SetConnections(layers.back());
	layers.push_back(layer);
}

void NeuralNet::InitInputLayer(const std::vector<std::pair<double, double>> &initData)
{
	auto& inputLayer = layers[0];
	int size = inputLayer.GetIsWithBias() ? inputLayer.GetNeurons().size() - 1 : inputLayer.GetNeurons().size();

	for (int i = 0; i < size; i++)
	{
		static_cast<InputNeuron*>((inputLayer.GetNeurons()[i]))->initialInput = GetKeysFromMap(initData)[i];
	}
}

void NeuralNet::Predict(const Layer &outputLayer, const std::vector<std::pair<double, double>> &initData)
{
	for (auto layer : layers)
	{
		for (auto& neuron : layer.GetNeurons())
		{
			neuron->ComputeOutput();
		}
	}

	std::cout << "--Output--" << std::endl;


	std::cout << "Input: ";
	for (int i = 0; i < outputLayer.GetNeurons().size(); i++)
	{
		std::cout.precision(precision);
		std::cout << std::fixed << GetKeysFromMap(initData)[i] << " ";
		/*<< ", Expected:  " << std::fixed << GetValuesFromMap(initData)[i] 
		<< ", Predicted: " << std::fixed << outputLayer.GetNeurons()[i]->output << std::endl << std::endl;*/
	}
	std::cout << std::endl << "Expected: ";
	for (int i = 0; i < outputLayer.GetNeurons().size(); i++)
	{
		std::cout.precision(precision);
		std::cout << std::fixed << GetValuesFromMap(initData)[i] << " ";
	}
	std::cout << std::endl << "Predicted: ";
	for (int i = 0; i < outputLayer.GetNeurons().size(); i++)
	{
		std::cout.precision(precision);
		std::cout << std::fixed << outputLayer.GetNeurons()[i]->output << " ";
	}
	std::cout << std::endl << std::endl;
}

void NeuralNet::ComputeOutputLayerError(const Layer &outputLayer, const std::vector<std::pair<double, double>> &initData)
{
	for (int i = 0; i < outputLayer.GetNeurons().size(); i++)
	{
		double& output = outputLayer.GetNeurons()[i]->output;
		double neuronError = outputLayer.GetNeurons()[i]->activationFunction->GetDerivativeFromOutput(output) * (GetValuesFromMap(initData)[i] - output);
		outputLayer.GetNeurons()[i]->SetNeuronError(neuronError);
		outputLayer.GetNeurons()[i]->AddErrorToNeighbours();
	}
}

void NeuralNet::BackPropagation()
{
	for (int i = layers.size() - 2; i >= 0; i--)
	{
		layers[i].ComputeNeuronErrors();
	}

	for (auto& layer : layers)
	{
		layer.UpdateWeights(leariningRate);
	}
}

void NeuralNet::SetMomentum(const double& momentum)
{
	for (auto& layer : layers)
	{
		for(auto& neuron : layer.GetNeurons())
		{
			neuron->SetMomentum(momentum);
		}
	}
}

Layer& NeuralNet::GetHiddenLayer()
{
	return layers[layers.size() - 2];
}

std::vector<double> NeuralNet::Test(const std::vector<std::pair<double, double>>& testData)
{
	InitInputLayer(testData);
	Predict(layers.back(), testData);

	std::vector<double> output;

	for (auto neuron : layers.back().GetNeurons())
	{
		output.push_back(neuron->output);
	}

	return output;
}
