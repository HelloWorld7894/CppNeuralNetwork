#include <math.h>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <iostream>

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
    return 1 / (pow(e, -input) + 1);
}

class loss_funcs
{
    public:
        static float binary_crossentropy(double output, double target);
};
float loss_funcs::binary_crossentropy(double output, double target)
{
    //-(y * log(f(y)) - + (1-y) * log(1 - f(y)))
    return -(target * log10(output) + (1 - target) * log10(1 - output));
}

//random generators
int random_gen_bias(unsigned int gen_i) //to stop pattern repeating
{
    srand((unsigned) time(NULL) + gen_i);
    int bias_val = rand() % 2;
    return bias_val;
}

double random_gen_weight(unsigned int gen_i)
{
    srand((unsigned) time(NULL) + gen_i);

    double weight = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
    return weight;
}

double compute_neuron(double input, double weights, double bias, std::string act_func)
{
    //y-hat = f(wx + b)
    double y = weights * input + bias;

    if(act_func == "ReLU")
    {
        y = activation_funcs::ReLU(y);
    }
    else if (act_func == "Sigmoid")
    {
        y = activation_funcs::Sigmoid(y);
    }

    return y;
}

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
            //random generator setup

            for (int n_layer = 0; n_layer < parameters_tensor.size(); n_layer++)
            {
                for (int y_i = 0; y_i < parameters_tensor[n_layer].size(); y_i++)
                {
                    unsigned int seed_i = 2 * y_i + 3 * n_layer; //to stop pattern repeating

                    int bias_val = random_gen_bias(seed_i);
                    double weight_val = random_gen_weight(seed_i);

                    parameters_tensor[n_layer][y_i][0] = weight_val;
                    parameters_tensor[n_layer][y_i][1] = (double) bias_val; //well, we gotta store it as a double
                }
            }
        }

        void train(float *in1, float *in2, std::vector<std::vector<int>> train)
        {
            float loss;
            float acc;
            //one batch iteration (lets assume that batch=1)
            for (int i = 0; i < train.size(); i++)
            {
                //forward pass
                double output = forward(train[i][0]);
                std::cout << output << std::endl;

                //calculate loss
                loss += loss_funcs::binary_crossentropy(output, train[i][1]);
                //calculate accuracy
                acc = calculate_accuracy(output, train[i][1]);

                //backward pass
                backward();


            }
            loss = loss / train.size();

            *in1 = loss;
            *in2 = acc;

        }

        void test(float *in1, float *in2, std::vector<std::vector<int>> test)
        {
            float loss;
            float acc;

            //one batch iteration (lets assume that batch=1)
            for (int i = 0; i < test.size(); i++)
            {
                //forward pass
                double output = forward(test[i][0]);

                //calculate loss
                loss = loss_funcs::binary_crossentropy(output, test[i][1]);

                //backward pass, backpropagation
                backward();
            }

            *in1 = loss;
            *in2 = acc;
        }

        std::vector<std::vector<std::vector<double>>> get_parameters()
        {
            return parameters_tensor;
        }

        double forward(int data)
        {
            double input;
            std::vector<std::vector<double>> forward_pass_history;

            for (int n_layer = 0; n_layer < parameters_tensor.size(); n_layer++)
            {
                if (forward_pass_history.size() == 0)
                {
                    input = (double) data;
                }
                else
                {
                    input = forward_pass_history[forward_pass_history.size() - 1][0]; //i forgor :skull:
                }



                std::vector<double> neuron_res;

                for (int neuron_i = 0; neuron_i < parameters_tensor[n_layer].size(); neuron_i++)
                {
                    double output = compute_neuron(input, parameters_tensor[n_layer][neuron_i][0], 
                                                                        parameters_tensor[n_layer][neuron_i][1], act_funcs[n_layer]);
                    neuron_res.push_back(output);
                }

                forward_pass_history.push_back(neuron_res);
            }

            return forward_pass_history[forward_pass_history.size() - 1][0];
        }
        void backward()
        {
            //TODO: dodělat!


        }

        float calculate_accuracy(double input, double target)
        {

        }
};
