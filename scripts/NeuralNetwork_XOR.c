#include "Tools.h"

struct NeuralNetwork
{
	// Size of the neural network
	int nbInputs;
	int nbHidden;
	int nbOutputs;

// Matrices
	// Matrix of the input values
        struct Matrix matInputValues;
	// Matrix of ecpected outputs
	struct Matrix matAim;
	// Matrix of weights between input neurons to hidden neurons
	struct Matrix matWeightsIH;
	// Matrix of weights between hidden neurons to output neurons
	struct Matrix matWeightsHO;
	// Matrix of the biases of hidden neurons
	struct Matrix matBiasH;
	// Matrix of the biases of output neurons
	double BiasO;
	// Matrix of the output of the hidden layer (after the sum)
	struct Matrix matOutputH;
};


struct NeuralNetwork InitializeNetwork()
{
	struct NeuralNetwork net;
	
	net.nbInputs = 2;
	net.nbHidden = 3;
	net.nbOutputs = 1;

	net.matInputValues = CreateMatrix(8, 1);
	ChangeMatrix(net.matInputValues, 0, 0, 0);
	ChangeMatrix(net.matInputValues, 1, 0, 0);
	ChangeMatrix(net.matInputValues, 2, 0, 0);
	ChangeMatrix(net.matInputValues, 3, 0, 1);
	ChangeMatrix(net.matInputValues, 4, 0, 1);
	ChangeMatrix(net.matInputValues, 5, 0, 0);
	ChangeMatrix(net.matInputValues, 6, 0, 1);
	ChangeMatrix(net.matInputValues, 7, 0, 1);

	net.matAim = CreateMatrix(4, 1);
	ChangeMatrix(net.matAim, 0, 0, 0);
	ChangeMatrix(net.matAim, 1, 0, 1);
	ChangeMatrix(net.matAim, 2, 0, 1);
        ChangeMatrix(net.matAim, 3, 0, 0);

// Matrices of weights, in first layer rows are hidden neurons and cloums are imput
// neurons, for example, [0;0] would be the weight of the connection between the first
// input neuron and the first hidden neuron, [0;1] would be the weight of
// the connection between the second input neuron and the first hidden 
// neuron; sum of a row is the sum you need to normalize
	// Matrix of weights between input layer and hidden layer
	net.matWeightsIH = CreateMatrix(net.nbHidden, net.nbInputs);
	// Matrix of weights between hidden layer and output layer
	net.matWeightsHO = CreateMatrix(net.nbOutputs, net.nbHidden);
	// Matrix of the output of hidden layer after sum
	net.matOutputH = CreateMatrix(net.nbOutputs, net.nbHidden); 
	// Matrix of the biases of hidden layer
	net.matBiasH = CreateMatrix(net.nbHidden, 1);
	
// Initialize matrix values and lasts values
	net.BiasO = Random();
	InitMatrix(net.matWeightsIH);
	InitMatrix(net.matWeightsHO);
	InitMatrix(net.matBiasH);
	
	return net;
}

void TestForNeuralNetwork()
{
	struct NeuralNetwork nettest = InitializeNetwork();
	printf("Aim\n");
	PrintMatrix(nettest.matAim);
	printf("Input\n");
	PrintMatrix(nettest.matInputValues);
	printf("Weights IH\n");
	PrintMatrix(nettest.matWeightsIH);
	printf("Weights HO\n");
	PrintMatrix(nettest.matWeightsHO);
	printf("Bias H\n");
	PrintMatrix(nettest.matBiasH);
	printf("Bias O = %f\n", nettest.BiasO);
}


