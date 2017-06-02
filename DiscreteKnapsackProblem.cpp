//
// Created by Edzia on 2017-05-21.
//

#include <sstream>
#include "DiscreteKnapsackProblem.h"

string DiscreteKnapsackProblem::bruteForce() {
    return nullptr;
}

string DiscreteKnapsackProblem::greedyAlgorithm() {
    int maxSize = sizeOfKnapsack;
    int sumOfValues = 0;
    double *ratio = new double[numberOfItems];
    Array3 items;
    for (int i = 0; i < numberOfItems; i++){
        ratio[i] = 1.0 * values[i]/sizes[i];
        items.addElement(i,0);
    }

    for (int i = 0; i < numberOfItems; i++){
        std::cout << i << " " << ratio[i] << " " << items[i] << endl;
    }
    std::cout << endl;

    //sortowanie
    for (int i = 0; i < numberOfItems; i++)
        for (int j = 0; j < numberOfItems; j++)
            if (ratio[j] < ratio[j+1]){
                double tmp = ratio[j];
                ratio[j] = ratio[j+1];
                ratio[j+1] = tmp;
                int tmp2 = items[j];
                items[j] = items[j+1];
                items[j+1] = tmp2;
            }
    for (int i = 0; i < numberOfItems; i++){
        std::cout << i <<  " " << ratio[i] << " " << items[i] <</* " " << sizes[i] << " " << values[i] << */endl;
    }
    std::cout << endl;

    stringstream ss;
    ss << "Wynik: " << endl;

    int i = 0;
    while (maxSize > 0 && i < numberOfItems){
        if (maxSize - sizes[numberOfItems-1-items[i]] >= 0){
            maxSize -= sizes[numberOfItems-1-items[i]];
            sumOfValues += values[numberOfItems-1-items[i]];
            ss << items[i] << " ";
            std::cout << i << " " << items[i] << " " << sizes[numberOfItems-1-items[i]] << " " <<
                      values[numberOfItems-1-items[i]] << " " << sumOfValues << " " << maxSize<< endl;
        }
        i++;
    }
    ss << endl << sumOfValues << endl;
    return ss.str();
}

string DiscreteKnapsackProblem::dynamicProgramming() {
    return nullptr;
}

void DiscreteKnapsackProblem::loadFromFile(std::string filename) {
    int size;
    int weight;
    ifstream fin;
    fin.open(filename.c_str());
    fin >> sizeOfKnapsack;
    fin >> numberOfItems;
    for (int i = 0; i < numberOfItems; i++){
        fin >> size;
        fin >> weight;
        sizes.addElement(size,0);
        values.addElement(weight,0);
    }
}

void DiscreteKnapsackProblem::generateRandom() {

}
