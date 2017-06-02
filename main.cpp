#include <iostream>
#include "Problem.h"
#include "DiscreteKnapsackProblem.h"
#include "TravellingSalesmanProblem.h"

int main() {
    Problem * p = new DiscreteKnapsackProblem;
   // p->loadFromFile("data_knapsack.txt");
   // std::cout << p->greedyAlgorithm() << endl;
    delete p;

    p = new TravellingSalesmanProblem;
    p->loadFromFile("data_salesman.txt");
    std::cout << p->greedyAlgorithm();
    delete p;

    return 0;
}