#include <vector>
#include <stdint.h>

class dataset_generators
{
    public:
        std::vector<std::vector<int>> dumb_dataset_gen()
        {
            //range from 0 to 10
            //thats it

            std::vector<std::vector<int>> DumbDataset;

            for (uint8_t i = 0; i < 10; i++){
                std::vector<int> row;
                row.insert(row.end(), {i, ((i <= 5) ? 0 : 1)});

                DumbDataset.push_back(row);
            }
            return DumbDataset;
        }
};