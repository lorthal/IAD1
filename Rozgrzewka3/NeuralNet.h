#pragma once
#include <vector>
#include "Neuron.h"
#include "Layer.h"
class NeuralNet
{

public:

	static std::vector<double> GetKeysFromMap(const std::vector<std::pair<double, double>> &map);

	static std::vector<double> GetValuesFromMap(const std::vector<std::pair<double, double>> & map);

	NeuralNet(std::vector<int> layersConfiguration, IActivationFunction* func, double learningRate);

	//void SetActivationFunc(ActivationFunction func) { activationFunc = func; }

	void Train(std::vector<std::pair<double, double>> initData);

private:

	std::vector<Layer> layers;
	double leariningRate;

	void CreateInputLayer(int inputNeuronsCount);

	void CreateOutputLayer(int outputNeuronsCount);

	void InitInputLayer(std::vector<std::pair<double, double>> initData);

	void Predict(Layer &outputLayer, std::vector<std::pair<double, double>> initData);

	static void ComputeOutputLayerError(Layer outputLayer, std::vector<std::pair<double, double>> initData);

	void BackPropagation();
	//int layerCount;
	//std::vector<int> neuronsOnLayers;
	//std::vector<std::vector<Neuron>> layers;

	//ActivationFunction activationFunc;
};
