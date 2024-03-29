//
// Created by Edzia on 2017-05-21.
//

#ifndef SDIZO_3_PROBLEM_H
#define SDIZO_3_PROBLEM_H

#include <string>

class Problem {
    //tu bedzie jakies menu i algorytmy
private:

public:
    virtual std::string bruteForce() = 0;
    virtual std::string greedyAlgorithm() = 0;
    virtual std::string dynamicProgramming() = 0;

    virtual void loadFromFile(std::string filename) = 0;
    virtual void saveToFile(std::string filename) = 0;
    virtual void generateRandom(int number, int size) = 0;

    virtual double testTime(int algorithmType) = 0;

    virtual void menu() = 0;
};


#endif //SDIZO_3_PROBLEM_H
