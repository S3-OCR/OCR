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
	// Error values
	struct Matrix matErrors;
	// Matrix of derivatives
	struct Matrix matDerivatives;
	// Matrix gradients hidden to output weights
	struct Matrix matGradientsHO;
	// Matrix gradients input weights
	struct Matrix matGradientsIH;
	// Matrix gradients bias
	struct Matrix matGradientsB;
	// Matrix previous weights for backpropagation IH
	struct Matrix matPreviousWeightsIH;
	// Matrix previous weights for backpropagation HO
	struct Matrix matPreviousWeightsHO;
	// Matrix previous bias for hidden
	struct Matrix matPreviousBiasH;

// Other variables
	// Gradient Bias Output
        struct Matrix GradientBiasOutput;
	// Bias of output neuron
        struct Matrix BiasO;
	// Sum of the weights * outputs of hidden neurons
	struct Matrix SumHOutputs;;
	// Final Output
	struct Matrix FinalOutput;
	// Derivative Output
	struct Matrix DerivativeO;
	// Learning rate
	double LearningRate;
	// Constante
	double ConstanteUpdate;
	// previous bias output
	struct Matrix PreviousBiasO;
};


struct NeuralNetwork InitializeNetwork()
{
	struct NeuralNetwork net;
	
	net.nbInputs = 2;
	net.nbHidden = 2;
	net.nbOutputs = 1;

// Initializing input matrix
	net.matInputValues = CreateMatrix(8, 1);
	ChangeMatrix(net.matInputValues, 0, 0, 0); 
	ChangeMatrix(net.matInputValues, 1, 0, 0); 
	ChangeMatrix(net.matInputValues, 2, 0, 0); 
	ChangeMatrix(net.matInputValues, 3, 0, 1); 
	ChangeMatrix(net.matInputValues, 4, 0, 1); 
	ChangeMatrix(net.matInputValues, 5, 0, 0); 
	ChangeMatrix(net.matInputValues, 6, 0, 1);
	ChangeMatrix(net.matInputValues, 7, 0, 1); 
		
// Initializing error matrix
	net.matErrors = CreateMatrix(8, 1);
	ChangeMatrix(net.matErrors, 0, 0, 1);
	ChangeMatrix(net.matErrors, 2, 0, 1);
	ChangeMatrix(net.matErrors, 4, 0, 1);
	ChangeMatrix(net.matErrors, 6, 0, 1);

// Initializing the aim matrix
	net.matAim = CreateMatrix(8, 1);
	ChangeMatrix(net.matAim, 0, 0, 0);
	ChangeMatrix(net.matAim, 2, 0, 1);
	ChangeMatrix(net.matAim, 4, 0, 1);
        ChangeMatrix(net.matAim, 6, 0, 0);

// Matrices of weights, in first layer rows are hidden neurons and cloums are imput
// neurons, for example, [0;0] would be the weight of the connection between the first
// input neuron and the first hidden neuron, [0;1] would be the weight of
// the connection between the second input neuron and the first hidden 
// neuron; sum of a row is the sum you need to normalize
	net.matWeightsIH = CreateMatrix(net.nbHidden, net.nbInputs);
	net.matWeightsHO = CreateMatrix(net.nbOutputs, net.nbHidden);
	net.matOutputH = CreateMatrix(net.nbHidden, 1); 
	net.matBiasH = CreateMatrix(net.nbHidden, 1);
	net.matSumIH = CreateMatrix(net.nbHidden, 1);
	net.matDerivatives = CreateMatrix(net.nbHidden, 1);
	net.matPreviousWeightsIH = CreateMatrix(net.nbHidden, net.nbInputs);
	net.matPreviousWeightsHO = CreateMatrix(net.nbOutputs, net.nbHidden);
	net.matPreviousBiasH = CreateMatrix(net.nbHidden, 1);
	net.matGradientsIH = CreateMatrix(net.nbHidden, net.nbInputs);
	net.matGradientsHO = CreateMatrix(net.nbOutputs, net.nbHidden);
	net.matGradientsB = CreateMatrix(net.nbHidden, 1);

// Initialize matrix values and lasts values
	net.BiasO = CreateMatrix(1, 1);
        net.SumHOutputs = CreateMatrix(1, 1);
	net.PreviousBiasO = CreateMatrix(1, 1);
	net.GradientBiasOutput = CreateMatrix(1, 1);
	net.SumHOutputs = CreateMatrix(1, 1);

	ChangeMatrix(net.BiasO, 0, 0, Random());
	
	net.FinalOutput = CreateMatrix(1, 1);
	net.DerivativeO = CreateMatrix(1, 1);
	
	InitMatrix(net.matWeightsIH);
	InitMatrix(net.matWeightsHO);
	InitMatrix(net.matBiasH);
	InitMatrixZero(net.matPreviousWeightsHO);
	InitMatrixZero(net.matPreviousWeightsIH);
        InitMatrixZero(net.matPreviousBiasH);
	ChangeMatrix(net.SumHOutputs, 0, 0, 0.0);
	net.LearningRate = 1.414213562;
	net.ConstanteUpdate =  0.25;
	ChangeMatrix(net.PreviousBiasO, 0, 0, 0.0);
	return net;
}

double Sigmoid(double Sum)
{
	 return (1.0/(1.0 + exp(-Sum)));
}

void ForwardPass(struct NeuralNetwork net, int inpValues, int epoch)
{
	//printf("avzzavejazkjazrf");
	for (int h = 0; h < net.nbHidden; h++)
	{
		double SumIH = 0;
		for (int i = 0; i < net.nbInputs; i++)
		{
			SumIH += NavMatrix(net.matWeightsIH, h, i) * 
				NavMatrix(net.matInputValues, inpValues + i, 0);
		}
		SumIH += NavMatrix(net.matBiasH, h, 0);
		ChangeMatrix(net.matSumIH, h, 0, SumIH);
		ChangeMatrix(net.matOutputH, h, 0, Sigmoid(SumIH));
	}
	
	double SumHO = 0;
        for (int i = 0; i < net.nbHidden; i++)
        {
        	SumHO += NavMatrix(net.matWeightsHO, 0, i) *
                	 NavMatrix(net.matOutputH, i, 0);
        }
        SumHO += NavMatrix(net.BiasO, 0, 0);
	//printf("avzzavejazkjazrf");
        ChangeMatrix(net.SumHOutputs, 0, 0, SumHO);
	//printf("000000000000000000000000");
        ChangeMatrix(net.FinalOutput, 0, 0, Sigmoid(SumHO));
	//printf("bite");	
	ChangeMatrix(net.matErrors, inpValues, 0,
			    NavMatrix(net.FinalOutput, 0, 0) - 
			    NavMatrix(net.matAim, inpValues, 0));
	//printf("Sum HO  net\n%f\n", NavMatrix(net.SumHOutputs, 0, 0));
	//printf("Sum IH\n");
	//PrintMatrix(net.matSumIH);
	//printf("Error matrix forward\n");
	//PrintMatrix(net.matErrors);
	 if (epoch % 100 == 0)
         {
		 printf("Input 1 : %f, Input 2 : %f, Output : %f\n",
                 	NavMatrix(net.matInputValues, inpValues, 0),
                        NavMatrix(net.matInputValues, inpValues + 1, 0),
                        NavMatrix(net.FinalOutput, 0, 0));
	 }

}

void CalculateDerivative(struct NeuralNetwork net, int pattern)
{
	//printf("Enter Calculate");
	// Initialise the derivative of output in first position in the list.
    	ChangeMatrix(net.DerivativeO, 0, 0, -(NavMatrix(net.matErrors, pattern, 0)*
			  exp(NavMatrix(net.SumHOutputs, 0, 0))) /
		 	  (pow((1 + exp(NavMatrix(net.SumHOutputs, 0, 0))), 2)));
    	for (int i = 0; i < net.nbHidden; i++)
    	{
        	//Calculate the derivative of each 
        	ChangeMatrix(net.matDerivatives, i, 0, 
				(exp(NavMatrix(net.matSumIH, i, 0)) / 
				pow((1 + exp(NavMatrix(net.matSumIH, i, 0))), 2)) * 
				NavMatrix(net.matWeightsHO, 0, i) * 
				(NavMatrix(net.DerivativeO, 0, 0)));
    	}
}


void CalculateGradient(struct NeuralNetwork net, int pattern)
{
	//printf("Enter Gradient");
	// Initialise the gradients for the weights input - hidden
    	for (int i = 0; i < net.nbInputs; i++)
    	{
        	for (int h = 0; h < net.nbHidden; h++)
        	{
            		ChangeMatrix(net.matGradientsIH, h, i,
			      Sigmoid(NavMatrix(net.matInputValues, pattern + i, 0))* 
			      NavMatrix(net.matDerivatives, h, 0));
        	}
    	}	
	
    	//Initialise the gradients for the bias hidden neurones
    	for (int h = 0; h < net.nbHidden; h++)
    	{
        	ChangeMatrix(net.matGradientsB, h, 0, Sigmoid(1) *
		       		NavMatrix(net.matDerivatives, h, 0));
    	}

	ChangeMatrix(net.GradientBiasOutput, 0, 0, Sigmoid(1) * (NavMatrix(net.DerivativeO, 0, 0)));

    	//Initialise the gradients for the weights hidden - output
    	for (int h = 0; h < net.nbHidden; h++)
    	{
        	ChangeMatrix(net.matGradientsHO, 0, h,
			       	Sigmoid(NavMatrix(net.matOutputH, h, 0)) *
		       		NavMatrix(net.DerivativeO, 0, 0));
    	}
}

void UpdateWeights(struct NeuralNetwork net)
{
	//printf("Enter update");
	for (int h = 0; h < net.nbHidden; h++)
	{
		for (int i = 0; i < net.nbInputs; i++)
		{
			ChangeMatrix(net.matPreviousWeightsIH, h, i,
			    (net.LearningRate *
			    NavMatrix(net.matGradientsIH, h, i)) +
			    (net.ConstanteUpdate *
			     NavMatrix(net.matPreviousWeightsIH, h, i)));
			
			ChangeMatrix(net.matWeightsIH, h, i,
				(NavMatrix(net.matWeightsIH, h, i) +
				 NavMatrix(net.matPreviousWeightsIH, h, i)));
		}
	}

	for (int h = 0; h < net.nbHidden; h++)
        {
        	ChangeMatrix(net.matPreviousWeightsHO, 0, h,
                            (net.LearningRate *
                            NavMatrix(net.matGradientsHO, 0, h)) +
                            (net.ConstanteUpdate *
                             NavMatrix(net.matPreviousWeightsHO, 0, h)));
                        
                ChangeMatrix(net.matWeightsHO, 0, h,
                            (NavMatrix(net.matWeightsHO, 0, h) +
                            NavMatrix(net.matPreviousWeightsHO, 0, h)));
        } 

	for (int h = 0; h < net.nbHidden; h++)
        {
                ChangeMatrix(net.matPreviousBiasH, h, 0,
                            (net.LearningRate *
                            NavMatrix(net.matGradientsB, h, 0)) +
                            (net.ConstanteUpdate *
                             NavMatrix(net.matPreviousBiasH, h, 0)));

                ChangeMatrix(net.matBiasH, h, 0,
                            (NavMatrix(net.matBiasH, h, 0) +
                            NavMatrix(net.matPreviousBiasH, h, 0)));
        }

	ChangeMatrix(net.PreviousBiasO, 0, 0,
		       	(net.LearningRate * NavMatrix(net.GradientBiasOutput, 0, 0)) +
			    (net.ConstanteUpdate * NavMatrix(net.PreviousBiasO, 0, 0)));
	ChangeMatrix(net.BiasO, 0, 0, NavMatrix(net.BiasO, 0, 0) + NavMatrix(net.PreviousBiasO, 0, 0));
}

void BackPropagation(struct NeuralNetwork net, int pattern)
{
    CalculateDerivative(net, pattern);
    CalculateGradient(net, pattern);
    UpdateWeights(net);
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
	printf("Bias O = %f\n", NavMatrix(nettest.BiasO, 0, 0));	
	for(int epoch = 0; epoch < 100000; epoch++)
	{
		//printf("aaaaaaaaaaaaaaaaaaaaaaaa");
		for (int i = 0; i < 7; i += 2)
		{
			ForwardPass(nettest, i, epoch);
			//printf("Output\n%f\n", NavMatrix(nettest.FinalOutput, 0, 0));
			//printf("Sum\n");
			//PrintMatrix(nettest.matSumIH);
			//printf("Error matrix\n");
        		//PrintMatrix(nettest.matErrors);
			BackPropagation(nettest, i);
				
				/*printf("\nError Rates\n");
				printf("%f\n", NavMatrix(nettest.matErrors, 0, 0));
				printf("%f\n", NavMatrix(nettest.matErrors, 2, 0));
        			printf("%f\n", NavMatrix(nettest.matErrors, 4, 0));
        			printf("%f\n", NavMatrix(nettest.matErrors, 6, 0));*/
			
		}			
	}
	//printf("Derivatives\n");
	//PrintMatrix(nettest.matDerivatives);


}


