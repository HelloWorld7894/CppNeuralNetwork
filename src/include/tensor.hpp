#include <vector>
#include <typeinfo>
#include <iostream>

class Tensor
{
    public:

        template <typename T>
        Tensor(int x, int y, int z, T type) //x, y, z axis size + typeid
        {
            std::vector<std::vector<std::vector<T>>> tensor;  
        } 
};