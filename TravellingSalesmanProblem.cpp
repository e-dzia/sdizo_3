//
// Created by Edzia on 2017-05-21.
//

#include "TravellingSalesmanProblem.h"
#include <sstream>

std::string TravellingSalesmanProblem::bruteForce() {

    return nullptr;
}

std::string TravellingSalesmanProblem::greedyAlgorithm() {
    bool visited[numberOfCities];
    int path[numberOfCities];
    int length = 0;

    for (int i = 0; i < numberOfCities; i++){
        visited[i] = false;
        path[i] = -1;
    }
    int start = 1;
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
    ss << "Wynik: " << std::endl;
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
