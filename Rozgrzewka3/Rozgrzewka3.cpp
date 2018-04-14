#include "stdafx.h"
#include <iterator>
#include "NeuralNet.h"
#include "SigmoidFunction.h"
#include <iostream>

static std::vector<std::vector<std::pair<double, double>>> PrepareTrainingSetTransformation()
{
	
	std::vector<std::pair<double, double>> map1;
	map1.push_back(std::pair<double,double>(1.0, 1.0));
	map1.push_back(std::pair<double,double>(0.0, 0.0));
	map1.push_back(std::pair<double,double>(0.0, 0.0));
	map1.push_back(std::pair<double,double>(0.0, 0.0));

	std::vector<std::pair<double, double>> map2;
	map2.push_back(std::pair<double, double>(0.0, 0.0));
	map2.push_back(std::pair<double, double>(1.0, 1.0));
	map2.push_back(std::pair<double, double>(0.0, 0.0));
	map2.push_back(std::pair<double, double>(0.0, 0.0));

	std::vector<std::pair<double, double>> map3;
	map3.push_back(std::pair<double, double>(0.0, 0.0));
	map3.push_back(std::pair<double, double>(0.0, 0.0));
	map3.push_back(std::pair<double, double>(1.0, 1.0));
	map3.push_back(std::pair<double, double>(0.0, 0.0));

	std::vector<std::pair<double, double>> map4;
	map4.push_back(std::pair<double, double>(0.0, 0.0));
	map4.push_back(std::pair<double, double>(0.0, 0.0));
	map4.push_back(std::pair<double, double>(0.0, 0.0));
	map4.push_back(std::pair<double, double>(1.0, 1.0));

	std::vector<std::vector<std::pair<double, double>>> set = { map1, map2, map3, map4 };
	return set;
}

int main()
{
	std::vector<int> configuration = { 4, 1, 4 };
	double learningRate = 0.01;
	int epochs = 1;

	auto trainingSet = PrepareTrainingSetTransformation();
	NeuralNet net = NeuralNet(configuration, new SigmoidFunction(), learningRate);

	for (int i = 1; i <= epochs; i++)
	{
		std::cout << "**** Epoch: " << i << " ****" << std::endl;
		for (auto map : trainingSet)
		{
			net.Train(map);
		}
	}
	getchar();
	return 0;
}
