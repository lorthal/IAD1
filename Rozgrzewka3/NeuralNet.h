#pragma once
#include <vector>
#include "Neuron.h"
#include "Layer.h"
class NeuralNet
{

public:

	static std::vector<double> GetKeysFromMap(const std::vector<std::pair<double, double>> &map);

	static std::vector<double> GetValuesFromMap(const std::vector<std::pair<double, double>> &map);

	NeuralNet(const std::vector<int> &layersConfiguration, IActivationFunction *func, const double &learningRate);

	void Train(const std::vector<std::pair<double, double>> &initData);

private:

	std::vector<Layer> layers;
	double leariningRate;

	void CreateInputLayer(const int &inputNeuronsCount);

	void CreateOutputLayer(const int &outputNeuronsCount);

	void InitInputLayer(const std::vector<std::pair<double, double>> &initData);

	void Predict(const Layer &outputLayer, const std::vector<std::pair<double, double>> &initData);

	static void ComputeOutputLayerError(const Layer &outputLayer, const std::vector<std::pair<double, double>> &initData);

	void BackPropagation();
};
