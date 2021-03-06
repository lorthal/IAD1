#include "stdafx.h"
#include <iterator>
#include "NeuralNet.h"
#include "SigmoidFunction.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <iomanip>

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
	std::vector<int> configuration = { 4, 2, 4 };
	std::string outputFileName = "output.txt";

	double learningRate = 0.1;
	double momentum = .6;
	int epochs = 5000;
	double destError = 0.001;
	bool bias = true;
	bool outputHiddenLayer = false;

	switch (argc)
	{
	case 0:
	case 1:
		break;
	default:
	case 7:
		outputHiddenLayer = stob(argv[6]);
	case 6:
		outputFileName = argv[5];
	case 5:
		bias = stob(argv[4]);
	case 4:
		if (std::stod(argv[3]) < 1)
		{
			destError = std::stod(argv[3]);
			epochs = 0;
		}
		else
		{
			epochs = std::stoi(argv[3]);
		}
	case 3:
		momentum = std::stod(argv[2]);
	case 2:
		learningRate = std::stod(argv[1]);
		break;
	}

	if (argc >= 8)
	{
		configuration.clear();
		for (int i = 7; i < argc; i++)
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
		std::ofstream outputFile;
		outputFile.open(path + outputFileName);
		outputFile.precision(precision);
		if (outputHiddenLayer)
		{
			outputFile << std::setw(6) << std::left << "Epoch" << std::setw(15) << std::left << "Hidden outputs\n";
		}
		else
		{
			outputFile << std::setw(6) << std::left << "Epoch" << std::setw(15) << std::left << "Error\n";
		}
		if (epochs > 1)
		{
			for (int i = 1; i <= epochs; i++)
			{
				std::cout << "**** Epoch: " << i << " ****" << std::endl << std::endl;
				for (auto map : trainingSet)
				{
					net->Train(map);
					if (outputHiddenLayer)
					{
						outputFile << std::setw(6) << std::left << i;
						for (auto neuron : net->GetHiddenLayer().GetNeurons())
						{
							outputFile << std::fixed << neuron->output << " ";
						}
						outputFile << "\n";
					}
					error += net->ComputeError(map);
				}
				error /= trainingSet.size();
				std::cout << "&&&&& Error: " << error << std::endl << std::endl;
				if (!outputHiddenLayer)
				{
					outputFile << std::setw(6) << std::left << i << " " << std::fixed << error << "\n";
				}
			}
		}
		else
		{
			int i = 1;
			do
			{
				std::cout << "**** Epoch: " << i << " ****" << std::endl << std::endl;
				for (auto map : trainingSet)
				{
					net->Train(map);
					error += net->ComputeError(map);
				}
				error /= trainingSet.size();
				std::cout << "&&&&& Error: " << error << std::endl << std::endl;
				outputFile << std::setw(6) << std::left << i << " " << std::fixed << error << "\n";
				i++;
			} while (error > destError);
		}
		outputFile.close();
	}
	//getchar();
	return 0;
}
