//
// Created by Edzia on 2017-05-21.
//

#ifndef SDIZO_3_TRAVELLINGSALESMANPROBLEM_H
#define SDIZO_3_TRAVELLINGSALESMANPROBLEM_H


#include "Problem.h"
#include "GraphMatrix.h"
#include <fstream>

class TravellingSalesmanProblem: public Problem {
private:
    GraphMatrix gm;
    int numberOfCities;

public:
    std::string bruteForce() override;

    std::string greedyAlgorithm() override;

    std::string dynamicProgramming() override;

    void loadFromFile(std::string filename) override;

    void generateRandom() override;

    bool allVisited(bool pBoolean[]);

    void permute(int *permutation, int left, int right, int &min, std::string &result);

    void swap(int *pInt, int *pInt1);

    std::string countPath(int *permutation, int &min);
};


#endif //SDIZO_3_TRAVELLINGSALESMANPROBLEM_H
