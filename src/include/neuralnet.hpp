#include <math.h>
#include <string>
#include <map>
#include <vector>

#include "tensor.hpp"

class NN_layer
{
    public:
        NN_layer(std::string activation_function, int n_neurons)
        {
            for (int i = 0; i << n_neurons; i++)
            {
                //activation_funcs::ReLU(w * x + b);
            }
        }
};

class neural_network
{
    public:
        neural_network(std::vector<NN_layer> layers, int size)
        {
            Tensor parameters(0, 0, 0, (double) 0.0); //ah yes, tensor my beloved

        }

        void summary()
        {

        }
};

//activation functions
class activation_funcs
{
    public:
        static double ReLU(double input);
        static double Sigmoid(double input);
};
double activation_funcs::ReLU(double input)
{
    if (input <= 0){return 0.0;}
    return input;
}
double activation_funcs::Sigmoid(double input)
{
    float e = 2.718281;
    return pow(e, input) / pow(e, input) + 1;
}