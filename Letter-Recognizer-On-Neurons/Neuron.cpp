#include "header.h"
#include "Neuron.h"

Neuron::Neuron(const int LAYER_SIZE)
	: _LAYER_SIZE(LAYER_SIZE)
{
	_wages = new double[_LAYER_SIZE];
	for (int i = 0; i < _LAYER_SIZE; i++)
	{
		_wages[i] = double(rand() % 101) / 100.0 - 0.5;
	}
	_fis = new double[_LAYER_SIZE];
}
void Neuron::execute(bool ** prevLayer, int x, int y)
{
	assert(x*y == _LAYER_SIZE);
	_sum = 0;
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			_sum += double(prevLayer[i][j]) * _wages[i*y + j];
		}
	}
	assert(_sum == _sum);
	_result = LReLU(_sum);
	_derivative = derivativeLReLU(_sum);
}
void Neuron::execute(Neuron ** prevLayer)
{
	_sum = 0;
	for (int i = 0; i < _LAYER_SIZE; i++)
	{
		_sum += prevLayer[i]->getResult() * _wages[i];
	}
	assert(_sum == _sum);
	_result = LReLU(_sum);
	_derivative = derivativeLReLU(_sum);
	_grad = 0;
}
double Neuron::LReLU(double x) const
{
	if (x <= 0)
		return 0.f;
	else
		return x;
}
double Neuron::derivativeLReLU(double x) const
{
	if (x <= 0)
		return 0.01f;
	else
		return 1.f;
}
double Neuron::lin(double x) const
{
	return x;
}
double Neuron::derivativeLin(double x) const
{
	return 1;
}
void Neuron::countGrad(Neuron ** prevLayer)
{
	_grad = 0;
	for (int i = 0; i < _LAYER_SIZE; i++)
	{
		_grad += _wages[i] * prevLayer[i]->getGrad();
	}
	_grad *= _derivative;
}
void Neuron::countGrad(Neuron ** prevLayer, int wi)
{
	_grad = prevLayer[wi]->getResult();
	_grad *= _derivative;
}
void Neuron::countGrad(bool ** prevLayer, int x, int y, int wi)
{
	_grad = double(int(prevLayer[wi%x][wi / x]));
	_grad *= _derivative;
}
void Neuron::countGrad()
{
	_grad = 0;
}
void Neuron::teach(int wage, double fi)
{
	_fis[wage] = fi;
}
void Neuron::executeTeaching()
{
	for (int i = 0; i < _LAYER_SIZE; i++)
	{
		_wages[i] -= _fis[i];
	}
}
double Neuron::getResult() const
{
	return _result;
}
double Neuron::getDerivative() const
{
	return _derivative;
}
double Neuron::getGrad() const
{
	return _grad;
}
Neuron::~Neuron()
{
	delete[] _wages;
}