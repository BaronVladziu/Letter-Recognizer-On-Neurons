#pragma once
#include "header.h"

class NeuralNetwork
{
	const int _LAYER_SIZE;
	const int _NO_LAYERS;
	const int _MAP_X;
	const int _MAP_Y;
	const double _LEARNING_RATE;

	bool ** _spriteColors;
	Neuron *** _layersPtrs;

	void executeNeurons();
	void executeCountingGrad(int layer, int neuron, int wage);
	int checkResult() const;
	void teach(int correct);
	double countErrorDerivative(int correct) const;
	double countError(int correct) const;
	void executeTeaching();

public:
	NeuralNetwork(int mapX, int mapY);
	void recognize(bool ** spriteColors);
	~NeuralNetwork();
};