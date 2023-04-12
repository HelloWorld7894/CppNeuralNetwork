#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <tuple>

#include "include/json.hpp"
#include "include/neuralnet.hpp"
#include "include/dataset.hpp"

using json = nlohmann::json;
int main()
{
    std::string dec;
    std::vector<NN_layer> layers;
    std::map<std::string, int> nn_parameters;

    std::cout << "read from json config? (y | n)";
    std::getline(std::cin, dec);

    if (dec == "y" || dec == "yes") //define using json file
    {
        //read json file
        std::cout << "loading default .json configuration..." << std::endl;
        std::ifstream config("config/NN1.json");

        json data = json::parse(config);
        //std::cout << data["layers"][0]["func"];

        int n_layers = sizeof(data["layers"][0]) / sizeof(data["layers"][0][0]);

        //register all parameters
        for (int i = 0; i < n_layers; i++)
        {
            layers.push_back(NN_layer(data["layers"][i]["func"], data["layers"][i]["n"]));
        }

    }
    else
    {
        //you can define number of layers explicitly
        layers.push_back(NN_layer("ReLU", 1));
        layers.push_back(NN_layer("Sigmoid", 1));

        nn_parameters["epochs"] = 7;
    }

    //or read from json file

    //create neuralnet
    neural_network DumbNeuralNet(layers, nn_parameters, 2);

    //
    // just testing if this actually works, so i am going to make my own dumb classifier if x > 5 or x <= 5
    //

    //create dataset
    dataset_generators dat_gen;
    std::vector<std::vector<int>> dataset_train = dat_gen.dumb_dataset_gen();
    std::vector<std::vector<int>> dataset_test = dat_gen.dumb_dataset_gen();

    //print neural network summary
    DumbNeuralNet.summary();

    //train and test
    DumbNeuralNet.random_init();
    for (int i = 1; i < DumbNeuralNet.epochs + 1; i++)
    {   
        float train_loss, test_loss, train_acc, test_acc;

        DumbNeuralNet.train(&train_loss, &train_acc, dataset_train);
        DumbNeuralNet.test(&test_loss, &test_acc, dataset_test);

        //log loss and accuracy
        std::cout << "----" << std::endl;
        std::cout << "EPOCH " << i << std::endl;
        std::cout << "----" << std::endl;


        std::cout << "train loss: " << train_loss << ", train acc: " << train_acc << std::endl;
        std::cout << "test loss: " << test_loss << ", test acc " << test_acc << std::endl;
    }

    return 0;
}