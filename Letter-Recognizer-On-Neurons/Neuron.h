#pragma once
#include"header.h"

class Neuron
{
	const int _LAYER_SIZE;

	double * _wages;
	double * _fis;
	double _sum;
	double _result;
	double _derivative;
	double _grad;

	double LReLU(double x) const;
	double derivativeLReLU(double x) const;
	double lin(double x) const;
	double derivativeLin(double x) const;

public:
	Neuron(const int LAYER_SIZE);
	void execute(bool ** prevLayer, int x, int y);
	void execute(Neuron ** prevLayer);
	void countGrad(Neuron ** prevLayer);
	void countGrad(Neuron ** prevLayer, int wi);
	void countGrad(bool ** prevLayer, int x, int y, int wi);
	void countGrad();
	void teach(int wage, double fi);
	void executeTeaching();
	double getResult() const;
	double getDerivative() const;
	double getGrad() const;
	~Neuron();
};