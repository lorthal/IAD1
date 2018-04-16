#include "stdafx.h"
#include <iterator>
#include "NeuralNet.h"
#include "SigmoidFunction.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

static const std::string path = "D:/Semestr 6/IAD/Zad1Res/";

static std::vector<std::vector<std::pair<double, double>>> PrepareTrainingSetTransformation(std::string filename)
{
	std::string line;
	std::ifstream file(path + filename);

	std::vector<std::vector<std::pair<double, double>>> set;
	if(file.is_open())
	{
		while (std::getline(file, line))
		{
			std::vector<std::pair<double, double>> pairs;
			std::string number;
			for (auto c : line)
			{
				if(c == ' ' || c == '\n')
				{
					pairs.push_back(std::pair<double, double>(std::stod(number), std::stod(number)));
					number = "";
				}
				else
				{
					number += c;
				}
			}
			pairs.push_back(std::pair<double, double>(std::stod(number), std::stod(number)));
			set.push_back(pairs);
		}
		file.close();
	}
	else
	{
		std::cout << "Error opening file" << std::endl;
	}
	return set;
}



int main()
{
	std::vector<int> configuration = { 4, 1, 4 };
	double learningRate = 0.1;
	int epochs = 100;

	auto trainingSet = PrepareTrainingSetTransformation("transformation.txt");
	IActivationFunction * func = new SigmoidFunction();
	NeuralNet * net = new NeuralNet(configuration, func, learningRate);

	for (int i = 1; i <= epochs; i++)
	{
		std::cout << "**** Epoch: " << i << " ****" << std::endl;
		for (auto map : trainingSet)
		{
			net->Train(map);
		}
	}
	getchar();
	return 0;
}
