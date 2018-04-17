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
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			std::vector<std::pair<double, double>> pairs;
			std::string number;
			for (auto c : line)
			{
				if (c == ' ' || c == '\n')
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

static bool stob(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	if (str == "true")
	{
		return true;
	}
	if (str == "false")
	{
		return false;
	}
	return true;
}

/**
 * \brief
 * \param argc
 * \param argv first argument is filename rest are net config (at least 3 numbers)
 * \return
 */
int main(int argc, char* argv[])
{
	std::string filename = "transformation.txt";
	std::vector<int> configuration = { 4, 3, 4 };

	double learningRate = 0.1;
	double momentum = .6;
	int epochs = 100;
	bool bias = true;

	switch (argc)
	{
	case 0:
	case 1:
		break;
	case 5:
		bias = stob(argv[4]);
	case 4:
		epochs = std::stoi(argv[3]);
	case 3:
		momentum = std::stod(argv[2]);
	case 2:
		learningRate = std::stod(argv[1]);
	default:
		break;
	}

	if (argc >= 8)
	{
		configuration.clear();
		for (int i = 5; i < argc; i++)
		{
			configuration.push_back(std::stoi(argv[i]));
		}
	}

	auto trainingSet = PrepareTrainingSetTransformation(filename);
	IActivationFunction * func = new SigmoidFunction();
	NeuralNet * net = new NeuralNet(configuration, func, learningRate, momentum, bias);

	std::cout << "[-------" << "learning rate: " << learningRate << ", epochs: " << epochs << ", layers: " << configuration.size() << "-------]" << std::endl;

	if (trainingSet.size() > 0)
	{
		double error = 0;
		for (int i = 1; i <= epochs; i++)
		{
			std::cout << "**** Epoch: " << i << " ****" << std::endl;
			for (auto map : trainingSet)
			{
				net->Train(map);
				error = net->ComputeError(map);
				std::cout << "&&&&& Error: " << error << std::endl;
			}
			//error /= trainingSet.size();
		}
	}
	return 0;
}
