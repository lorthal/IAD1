#include "stdafx.h"
#include <iterator>
#include "NeuralNet.h"
#include "SigmoidFunction.h"
#include "IdentityFunction.h"
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <iomanip>

typedef std::vector<std::vector<std::pair<double, double>>> DataSet;

struct Args
{
	std::string filename = "approximation_train_1.txt";
	//std::string filename = "transformation.txt";
	std::vector<int> configuration = { 1, 4, 1 };
	//std::vector<int> configuration = { 4, 2, 4 };
	std::string outputFileName = "output.txt";
	double learningRate = 0.1;
	double momentum = .6;
	int epochs = 5000;
	double destError = 0.001;
	bool bias = true;
	bool outputHiddenLayer = false;
};

static const std::string path = "./../Zad1Res/";
static const std::string appr_test_set = "approximation_test.txt";

void ReadArgs(int argc, char* argv[], Args& args);
void RunTransformation(Args args, NeuralNet* net, DataSet trainingSet);
void RunApproximation(Args args, NeuralNet* net, DataSet trainingSet, DataSet testSet);

static DataSet PrepareTrainingSetApproximation(std::string filename)
{
	std::string line;
	std::ifstream file(filename);

	DataSet set;
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			std::vector<std::pair<double, double>> pairs;
			std::pair<double, double> a_pair;
			std::string number;
			for (auto c : line)
			{
				if (c == ' ')
				{
					a_pair.first = std::stod(number);
					number = "";
				}
				else
				{
					number += c;
				}
			}
			a_pair.second = std::stod(number);
			number = "";
			pairs.push_back(a_pair);
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

static DataSet PrepareTrainingSetTransformation(std::string filename)
{
	std::string line;
	std::ifstream file(filename);

	DataSet set;
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			std::vector<std::pair<double, double>> pairs;
			std::string number;
			for (auto c : line)
			{
				if (c == ' ')
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


int main(int argc, char* argv[])
{
	Args args;

	ReadArgs(argc, argv, args);

	DataSet trainingSet;
	DataSet testSet;

	IActivationFunction * func = new SigmoidFunction();
	IActivationFunction * funcout = new SigmoidFunction();

	bool approximation = false;

	if (args.filename == "transformation.txt")
	{
		trainingSet = PrepareTrainingSetTransformation(args.filename);
	}
	else {
		trainingSet = PrepareTrainingSetApproximation(args.filename);
		funcout = new IdentityFunction();
		testSet = PrepareTrainingSetApproximation(appr_test_set);
		approximation = true;
	}

	NeuralNet * net = new NeuralNet(args.configuration, func, funcout, args.learningRate, args.momentum, args.bias);

	//std::cout << "[-------" << "learning rate: " << args.learningRate << ", epochs: " << args.epochs << ", layers: " << args.configuration.size() << "-------]" << std::endl;

	if (trainingSet.size() > 0)
	{
		if (approximation)
		{
			RunApproximation(args, net, trainingSet, testSet);
		}
		else
		{
			RunTransformation(args, net, trainingSet);
		}
	}
	//getchar();
	return 0;
}

void RunTransformation(Args args, NeuralNet* net, DataSet trainingSet)
{
	double error = 0;
	std::ofstream outputFile;
	outputFile.open(path + args.outputFileName);
	outputFile.precision(precision);
	if (args.outputHiddenLayer)
	{
		outputFile << std::setw(6) << std::left << "Epoch" << std::setw(15) << std::left << "Hidden outputs\n";
	}
	else
	{
		outputFile << std::setw(6) << std::left << "Epoch" << std::setw(15) << std::left << "Error\n";
	}
	if (args.epochs > 1)
	{
		for (int i = 1; i <= args.epochs; i++)
		{
			//std::cout << "**** Epoch: " << i << " ****" << std::endl << std::endl;
			for (auto map : trainingSet)
			{
				net->Train(map);
				if (args.outputHiddenLayer)
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
			//std::cout << "&&&&& Error: " << error << std::endl << std::endl;
			if (!args.outputHiddenLayer)
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
			//std::cout << "**** Epoch: " << i << " ****" << std::endl << std::endl;
			for (auto map : trainingSet)
			{
				net->Train(map);
				error += net->ComputeError(map);
			}
			error /= trainingSet.size();
			//std::cout << "&&&&& Error: " << error << std::endl << std::endl;
			outputFile << std::setw(6) << std::left << i << " " << std::fixed << error << "\n";
			i++;
		} while (error > args.destError);
	}
	outputFile.close();
}

void RunApproximation(Args args, NeuralNet* net, DataSet trainingSet, DataSet testSet)
{
	double error = 0, errorTest = 0;
	std::ofstream outputFile;
	outputFile.open(path + args.outputFileName);
	outputFile.precision(precision);
	bool outputFunc = args.outputHiddenLayer;

	if (!outputFunc)
	{
		outputFile << std::setw(6) << std::left << "Epoch" << std::setw(15) << std::left << "Error_Train" << std::setw(15) << std::left << "Error_Test\n";
	}
	else
	{
		outputFile << std::setw(6) << std::left << "X" << std::setw(15) << std::left << "Y\n";
	}

	for (int i = 1; i <= args.epochs; i++)
	{
		for (auto map : trainingSet)
		{
			net->Train(map);
			error += net->ComputeError(map);
		}
		error /= trainingSet.size();

		for (auto map : testSet)
		{
			net->Test(map);
			errorTest += net->ComputeError(map);
		}
		errorTest /= testSet.size();

		if (!outputFunc)
		{
			outputFile << std::setw(6) << std::left << i << " " << std::fixed << error << " " << std::fixed << errorTest << "\n";
		}
	}

	if (outputFunc)
	{
		for (auto map : trainingSet)
		{
			net->Test(map);
			outputFile << std::setw(6) << std::left << map.front().first << " " << std::fixed << net->GetOutputLayer().GetNeurons()[0]->output << "\n";
		}
	}

	outputFile.close();
}

void ReadArgs(int argc, char* argv[], Args& args)
{
	switch (argc)
	{
	case 0:
	case 1:
		break;
	default:
	case 8:
		args.filename = argv[7];
	case 7:
		args.outputHiddenLayer = stob(argv[6]);
	case 6:
		args.outputFileName = argv[5];
	case 5:
		args.bias = stob(argv[4]);
	case 4:
		if (std::stod(argv[3]) < 1)
		{
			args.destError = std::stod(argv[3]);
			args.epochs = 0;
		}
		else
		{
			args.epochs = std::stoi(argv[3]);
		}
	case 3:
		args.momentum = std::stod(argv[2]);
	case 2:
		args.learningRate = std::stod(argv[1]);
		break;
	}

	if (argc >= 9)
	{
		args.configuration.clear();
		for (int i = 8; i < argc; i++)
		{
			args.configuration.push_back(std::stoi(argv[i]));
		}
	}
}