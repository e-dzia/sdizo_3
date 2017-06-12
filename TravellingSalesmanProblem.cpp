//
// Created by Edzia on 2017-05-21.
//

#include "TravellingSalesmanProblem.h"
#include <sstream>
#include <algorithm>

std::string TravellingSalesmanProblem::bruteForce() {
    int start = 0;
    int *permutation = new int[numberOfCities];
    for (int i = 0; i < numberOfCities; i++){
        permutation[i] = i;
    }

    int min = INT32_MAX;
    std::string result = "";
    permute(permutation, 1, numberOfCities - 1, min, result);
    std::stringstream ss;
    ss << "Przeglad zupelny.\nWynik: " << std::endl;
    ss << result;

    ss << ": " << min << std::endl;
    return ss.str();
}

std::string TravellingSalesmanProblem::greedyAlgorithm() {
    bool visited[numberOfCities];
    int path[numberOfCities];
    int length = 0;

    for (int i = 0; i < numberOfCities; i++){
        visited[i] = false;
        path[i] = -1;
    }
    int start = 0;
    int i = start;

    while(!allVisited(visited)){
        visited[i] = true;
        int min = INT32_MAX;
        int position = -1;
        for (int j = 0; j < numberOfCities; j++){
            if (!visited[j] && gm.getEdgeLength(i,j) != -1 && gm.getEdgeLength(i,j)  < min){
                min = gm.getEdgeLength(i,j);
                position = j;
            }
        }
        if (min != INT32_MAX)
            length += min;
        else {
            length += gm.getEdgeLength(i,start);
        }
        path[i] = position;
        i = position;
    }


    std::stringstream ss;
    ss << "Algorytm zachlanny.\nWynik: " << std::endl;
    int j = start;
    while (path[j] != -1) {
        ss << path[j] << " ";
        j = path[j];
    }
    ss << ": " << length << std::endl;
    return ss.str();
}

std::string TravellingSalesmanProblem::dynamicProgramming() {
    return nullptr;
}

void TravellingSalesmanProblem::loadFromFile(std::string filename) {
    std::ifstream fin;
    fin.open(filename.c_str());
    fin >> numberOfCities;
    gm.createMatrix(numberOfCities);
    for (int i = 0; i < numberOfCities; i++){
        for (int j = 0; j < numberOfCities; j++){
            int length;
            fin >> length;
            gm.setEdge(i,j,length);
        }
    }
}

void TravellingSalesmanProblem::generateRandom() {

}

bool TravellingSalesmanProblem::allVisited(bool *visited) {
    for (int i = 0; i < numberOfCities; i++){
        if (!visited[i]) return false;
    }
    return true;
}

void TravellingSalesmanProblem::permute(int *permutation, int left, int right, int &min, std::string &result) {
    int i;
    if (left == right){
        std::string result_tmp = countPath(permutation, min);
        if (result_tmp != ""){
            result = result_tmp;
        }
    }
    else
    {
        for (i = left; i <= right; i++)
        {
            swap((permutation+left), (permutation+i));
            permute(permutation, left + 1, right, min, result);
            swap((permutation+left), (permutation+i)); //backtrack
        }
    }

}

void TravellingSalesmanProblem::swap(int *pInt, int *pInt1) {
    int tmp = *pInt;
    *pInt = *pInt1;
    *pInt1 = tmp;
}

std::string TravellingSalesmanProblem::countPath(int *permutation, int &min) {
    int length = 0;
    int end;
    for (int i = 1; i < numberOfCities; i++){
        length += gm.getEdgeLength(permutation[i-1],permutation[i]);
        end = i;
    }
    length += gm.getEdgeLength(permutation[end],permutation[0]);

    if (length < min){
        min = length;
        std::stringstream ss;
        for (int i = 0; i < numberOfCities; i++){
            ss << permutation[i] << " ";
        }
        return ss.str();
    }
    return "";
}
