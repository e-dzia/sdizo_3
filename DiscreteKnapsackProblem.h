//
// Created by Edzia on 2017-05-21.
//

#ifndef SDIZO_3_DISCRETEKNAPSACKPROBLEM_H
#define SDIZO_3_DISCRETEKNAPSACKPROBLEM_H


#include "Problem.h"
#include "Array3.h"

class DiscreteKnapsackProblem: public Problem {
private:
    Array3 sizes;
    Array3 values;
    int numberOfItems;
    int sizeOfKnapsack;

public:
    string bruteForce() override;

    string greedyAlgorithm() override;

    string dynamicProgramming() override;

    void loadFromFile(std::string filename) override;

    void generateRandom() override;

    bool* dec2bin(int dec);

    long long int power(int n);
};


#endif //SDIZO_3_DISCRETEKNAPSACKPROBLEM_H
