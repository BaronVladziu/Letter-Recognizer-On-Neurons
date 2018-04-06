#include "NeuralNetwork.h"
#include "Neuron.h"

NeuralNetwork::NeuralNetwork(int mapX, int mapY)
	: _LAYER_SIZE(127-33),
	_NO_LAYERS(2),
	_MAP_X(mapX),
	_MAP_Y(mapY),
	_LEARNING_RATE(0.03)
{
	_layersPtrs = new Neuron **[_NO_LAYERS];
	_layersPtrs[0] = new Neuron *[_LAYER_SIZE];
	for (int j = 0; j < _LAYER_SIZE; j++)
	{
		_layersPtrs[0][j] = new Neuron(_MAP_X*_MAP_Y);
	}
	for (int i = 1; i < _NO_LAYERS; i++)
	{
		_layersPtrs[i] = new Neuron *[_LAYER_SIZE];
		for (int j = 0; j < _LAYER_SIZE; j++)
		{
			_layersPtrs[i][j] = new Neuron(_LAYER_SIZE);
		}
	}
}
void NeuralNetwork::recognize(bool ** spriteColors)
{
	_spriteColors = spriteColors;
	executeNeurons();
	int guess = checkResult();
	guess += 33;
	std::cout << "My guess is: " << char(guess) << std::endl;
	std::cout << "Please tell me what the true answer was" << std::endl;
	char trueAnswer;
	std::cin >> trueAnswer;
	if (trueAnswer >= '!' && trueAnswer <= '~')
	{
		teach(trueAnswer);
		if (trueAnswer == guess)
		{
			std::cout << "Yay! I was correct!" << std::endl;
			std::cout << "Draw me more, please :3" << std::endl;
		}
		else
		{
			std::cout << "Thank you, maybe next time I'll guess right" << std::endl;
		}
	}
	else
	{
		std::cout << "Sorry, that's not a valid sign :c" << std::endl;
	}
	std::cout << "Recognition Error = " << countError(trueAnswer) << std::endl;
	std::cout << "Draw me something more, please :)" << std::endl;
}
void NeuralNetwork::executeNeurons()
{
	for (int j = 0; j < _LAYER_SIZE; j++)
	{
		_layersPtrs[0][j]->execute(_spriteColors, _MAP_X, _MAP_Y);
	}
	for (int i = 1; i < _NO_LAYERS; i++)
	{
		for (int j = 0; j < _LAYER_SIZE; j++)
		{
			_layersPtrs[i][j]->execute(_layersPtrs[i - 1]);
		}
	}
}
int NeuralNetwork::checkResult() const
{
	int mi = 0;
	double m = _layersPtrs[_NO_LAYERS - 1][0]->getResult();
	double sum = m;
	double n;
	for (int i = 1; i < _LAYER_SIZE; i++)
	{
		n = _layersPtrs[_NO_LAYERS - 1][i]->getResult();
		if (n > m)
		{
			m = n;
			mi = i;
		}
		if (n > 0)
		{
			sum += n;
		}
	}
	return mi;
}
void NeuralNetwork::teach(int correct)
{
	double derE;
	for (int neuron = 0; neuron < _LAYER_SIZE; neuron++)
	{
		for (int wage = 0; wage < _MAP_X*_MAP_Y; wage++)
		{
			executeCountingGrad(0, neuron, wage);
			derE = countErrorDerivative(correct);
			_layersPtrs[0][neuron]->teach(wage, derE*_LEARNING_RATE);
		}
	}
	for (int layer = 1; layer < _NO_LAYERS; layer++)
	{
		for (int neuron = 0; neuron < _LAYER_SIZE; neuron++)
		{
			for (int wage = 0; wage < _LAYER_SIZE; wage++)
			{
				executeCountingGrad(layer, neuron, wage);
				derE = countErrorDerivative(correct);
				_layersPtrs[layer][neuron]->teach(wage, derE*_LEARNING_RATE);
			}
		}
	}
	executeTeaching();
}
void NeuralNetwork::executeCountingGrad(int layer, int neuron, int wage)
{
	for (int n = 0; n < _LAYER_SIZE; n++)
	{
		_layersPtrs[layer][n]->countGrad();
	}
	if (layer == 0)
		_layersPtrs[layer][neuron]->countGrad(_spriteColors, _MAP_X, _MAP_Y, wage);
	else
		_layersPtrs[layer][neuron]->countGrad(_layersPtrs[layer - 1], wage);
	for (int l = layer + 1; l < _NO_LAYERS; l++)
	{
		for (int n = 0; n < _LAYER_SIZE; n++)
		{
			_layersPtrs[l][n]->countGrad(_layersPtrs[l - 1]);
		}
	}
}
double NeuralNetwork::countErrorDerivative(int correct) const
{
	double derE = 0;
	for (int i = 0; i < _LAYER_SIZE; i++)
	{
		if (i == correct)
			derE += (_layersPtrs[_NO_LAYERS - 1][i]->getResult() - 1) * _layersPtrs[_NO_LAYERS - 1][i]->getGrad();
		else
			derE += (_layersPtrs[_NO_LAYERS - 1][i]->getResult()) * _layersPtrs[_NO_LAYERS - 1][i]->getGrad();
	}
	derE /= _LAYER_SIZE;
	return derE;
}
double NeuralNetwork::countError(int correct) const
{
	double E = 0;
	double el;
	for (int i = 0; i < _LAYER_SIZE; i++)
	{
		if (i == correct)
			el = (_layersPtrs[_NO_LAYERS - 1][i]->getResult() - 1);
		else
			el = (_layersPtrs[_NO_LAYERS - 1][i]->getResult());
		E += el*el;
	}
	E /= 2 * _LAYER_SIZE;
	return E;
}
void NeuralNetwork::executeTeaching()
{
	for (int layer = 0; layer < _NO_LAYERS; layer++)
	{
		for (int neuron = 0; neuron < _LAYER_SIZE; neuron++)
		{
			_layersPtrs[layer][neuron]->executeTeaching();
		}
	}
}
NeuralNetwork::~NeuralNetwork()
{
	for (int i = 0; i < _NO_LAYERS; i++)
	{
		for (int j = 0; j < _LAYER_SIZE; j++)
		{
			delete _layersPtrs[i][j];
		}
		delete[] _layersPtrs[i];
	}
	delete[] _layersPtrs;
}