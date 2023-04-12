#include <math.h>
#include <string>
#include <map>
#include <vector>

class NN_layer
{
    public:
        int n;
        std::string act_func;

        NN_layer(std::string activation_function, int n_neurons)
        {
            for (int i = 0; i < n_neurons; i++)
            {
                n = n_neurons;
                act_func = activation_function;
            }
        }
};

class neural_network
{   
    private:
        std::vector<std::string> act_funcs;
        std::vector<std::vector<std::vector<double>>> parameters_tensor;
    public:
        int epochs;

        neural_network(std::vector<NN_layer> layers, std::map<std::string, int> nn_parameters, int size)
        {
            for (int i = 0; i < layers.size(); i++)
            {
                act_funcs.push_back(layers[i].act_func);
                std::vector<std::vector<double>> layer;
                for (int i = 0; i < layers[i].n; i++)
                {
                                            //w,   b
                    std::vector<double> vect{0.0, 0.0};
                    layer.push_back(vect);
                }
                parameters_tensor.push_back(layer);
            }

            epochs = nn_parameters["epochs"];
        }

        void summary()
        {
            for (int i = 0; i < act_funcs.size(); i++)
            {
                std::cout << "-----" << std::endl;
                std::cout << "layer " << i << std::endl;
                std::cout << " - neurons " << parameters_tensor[i].size() << std::endl;
                std::cout << " - parameters " << parameters_tensor[i].size() * 2 << std::endl;
                std::cout << "-----" << std::endl;
            }
        }

        void random_init()
        {

        }

        void train(float *in1, float *in2)
        {
            float x = 16.333;
            float y = 99.5;

            *in1 = x;
            *in2 = y;
        }

        void test(float *in1, float *in2)
        {
            float x = 16.333;
            float y = 99.5;

            *in1 = x;
            *in2 = y;
        }

        std::vector<std::vector<std::vector<double>>> get_parameters()
        {
            return parameters_tensor;
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