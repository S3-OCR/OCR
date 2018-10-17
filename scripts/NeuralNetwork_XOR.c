#include "Tools.h"
#include "NeuralNetwork_XOR.h"

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
	// Matrix of the output of the hidden layer (after the sum)
	struct Matrix matOutputH;
	// Matrix of the sum of weights * inputs
	struct Matrix matSumIH;
	// Sum of the weights * outputs of hidden neurons
	struct Matrix matSumHOutputs;
	// Error values
	struct Matrix matErrors;

// Other variables
	// Bias of output neuron
        double BiasO;
	// Sum of the weights * outputs of hidden neurons
	double SumHOutputs;;
	// Final Output
	double FinalOutput;
};


struct NeuralNetwork InitializeNetwork()
{
	struct NeuralNetwork net;
	
	net.nbInputs = 2;
	net.nbHidden = 3;
	net.nbOutputs = 1;

// Initializing input matrix
	net.matInputValues = CreateMatrix(8, 1);
	// First Input		
	ChangeMatrix(net.matInputValues, 0, 0, 0); // Goes
	ChangeMatrix(net.matInputValues, 1, 0, 0); // By
	ChangeMatrix(net.matInputValues, 2, 0, 1); // Pairs
	ChangeMatrix(net.matInputValues, 3, 0, 1); // 
	// Second Input				   // Exemples:
	ChangeMatrix(net.matInputValues, 4, 0, 0); // 
	ChangeMatrix(net.matInputValues, 5, 0, 1); // First[0].Second[0]=[0][4]=00
	ChangeMatrix(net.matInputValues, 6, 0, 0); // First[1].Second[1]=[1][5]=01
	ChangeMatrix(net.matInputValues, 7, 0, 1); // First[2].Second[2]=[2][6]=10
	// It's just to make it easier to mamage Error matrix value changing 
		
// Initializing error matrix
	net.matErrors = CreateMatrix(4, 1);
	ChangeMatrix(net.matErrors, 0, 0, 1);
	ChangeMatrix(net.matErrors, 1, 0, 1);
	ChangeMatrix(net.matErrors, 2, 0, 1);
	ChangeMatrix(net.matErrors, 3, 0, 1);

// Initializing the aim matrix
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
	// Matrix of the sum of weights * inputs
	net.matSumIH = CreateMatrix(net.nbHidden, 1);
	// Sum of the weights * outputs of hidden neurons
	net.SumHOutputs = 0;
// Initialize matrix values and lasts values
	net.BiasO = Random();
	InitMatrix(net.matWeightsIH);
	InitMatrix(net.matWeightsHO);
	InitMatrix(net.matBiasH);
	
	return net;
}

double Sigmoid(double Sum)
{
	 return (1.0/(1.0 + exp(-Sum)));
}

void ForwardPass(struct NeuralNetwork net, int inpValues, int epoch)
{
	for (int h = 0; h < net.nbHidden; h++)
	{
		double SumIH = 0;
		for (int i = 0; i < net.nbInputs; i++)
		{
			SumIH += NavMatrix(net.matWeightsIH, h, i) * 
				NavMatrix(net.matInputValues, inpValues + 4 + i, 0);
		}
		SumIH += NavMatrix(net.matBiasH, h, 0);
		ChangeMatrix(net.matSumIH, h, 0, SumIH);
		ChangeMatrix(net.matOutputH, h, 0, Sigmoid(SumIH));
	}
	
	double SumHO = 0;
        for (int i = 0; i < net.nbHidden; i++)
        {
        	SumHO += NavMatrix(net.matWeightsIH, 0, i) *
                	 NavMatrix(net.matInputValues, inpValues + 4 + i, 0);
        }
        SumHO += net.BiasO;
        net.SumHOutputs = SumHO;
        net.FinalOutput = Sigmoid(SumHO);

	if (epoch % 100 == 0)
		ChangeMatrix(net.matErrors, inpValues, 0, net.FinalOutput
			       		- NavMatrix(net.matAim, inpValues, 0));
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
	printf("Error Rates\n");
	PrintMatrix(nettest.matErrors);
}


