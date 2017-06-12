//
// Created by Edzia on 2017-05-21.
//

#include <sstream>
#include <chrono>
#include "DiscreteKnapsackProblem.h"

string DiscreteKnapsackProblem::bruteForce() {
    int current_dec = 1;
    int current_best;
    int max = 0;
    while (true){
        bool *current_bin = dec2bin(current_dec);
        int sum = 0;
        int sumSize = 0;
        int checked = 0;
        for (int i = 0; i < numberOfItems; i++){
            if (current_bin[i]){
                sum += values[i];
                sumSize += sizes[i];
                checked++;
            }
        }

        if (sumSize <= sizeOfKnapsack && sum > max){
            current_best = current_dec;
            max = sum;
        }

        delete [] current_bin;
        current_dec++;
        if (checked == numberOfItems) break;
    }

    stringstream ss;
    ss << "Przeglad zupelny.\nWynik: " << endl;

    bool *current_bin = dec2bin(current_best);
    for (int i = 0; i < numberOfItems; i++){
        if (current_bin[i]){
            ss << numberOfItems-i-1 << " ";
        }
    }

    delete [] current_bin;

    ss << endl << max << endl;
    return ss.str();
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

   /* for (int i = 0; i < numberOfItems; i++){
        std::cout << i << " " << ratio[i] << " " << items[i] << endl;
    }
    std::cout << endl;*/

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
  /*  for (int i = 0; i < numberOfItems; i++){
        std::cout << i <<  " " << ratio[i] << " " << items[i] <</* " " << sizes[i] << " " << values[i] << *//*endl;
    }
    std::cout << endl;*/

    stringstream ss;
    ss << "Algorytm zachlanny.\nWynik: " << endl;

    int i = 0;
    while (maxSize > 0 && i < numberOfItems){
        if (maxSize - sizes[numberOfItems-1-items[i]] >= 0){
            maxSize -= sizes[numberOfItems-1-items[i]];
            sumOfValues += values[numberOfItems-1-items[i]];
            ss << items[i] << " ";
            //std::cout << i << " " << items[i] << " " << sizes[numberOfItems-1-items[i]] << " " <<
            //          values[numberOfItems-1-items[i]] << " " << sumOfValues << " " << maxSize<< endl;
        }
        i++;
    }
    ss << endl << sumOfValues << endl;
    return ss.str();
}

string DiscreteKnapsackProblem::dynamicProgramming() {
    Array3* resultArray = new Array3[numberOfItems+1];
    for (int i = 0; i < numberOfItems+1; i++){
        for (int j = 0; j < sizeOfKnapsack+1; j++){
            resultArray[i].addElement(0,0);
        }
    }

    for (int i = 1; i < numberOfItems+1; i++){
        for (int j = 1; j < sizeOfKnapsack+1; j++){
            if (j - sizes[i-1] >= 0 && resultArray[i-1][j-sizes[i-1]]+values[i-1] > resultArray[i-1][j]){
                resultArray[i][j] = resultArray[i-1][j-sizes[i-1]]+values[i-1];
            }
            else {
                resultArray[i][j] = resultArray[i-1][j];
            }
        }
    }


    stringstream ss;
    ss << "Programowanie dynamiczne.\nWynik: " << endl;

    int j = sizeOfKnapsack;
    int i = numberOfItems;
    while(j > 0 && i > 0){
        if(resultArray[i][j] == resultArray[i-1][j]) {
            //cout << i << " " << resultArray[i][j] << " " << resultArray[i-1][j] << endl;
            i--;
        }
        else {
            //cout << i << " Wyciagam " << resultArray[i][j] << " " << resultArray[i-1][j] << endl;
            ss << numberOfItems-(i) << " ";
            j -= sizes[i-1];
            i--;
        }
    }

    ss << endl << resultArray[numberOfItems][sizeOfKnapsack] << endl;
    return ss.str();
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

void DiscreteKnapsackProblem::generateRandom(int number, int size) {
    int sum = 0;
    numberOfItems = number;
    sizeOfKnapsack = size;
    do {
        sizes.deleteAll();
        values.deleteAll();
        for (int i = 0; i < numberOfItems; i++){
            int size_tmp = rand()%100;
            int value_tmp = rand()%100;
            sizes.addElement(size_tmp,0);
            values.addElement(value_tmp,0);
            sum += size_tmp;
        }
    } while (sum < sizeOfKnapsack);

}

bool* DiscreteKnapsackProblem::dec2bin(int dec) {
    bool* bin = new bool[numberOfItems];
    for (int i = 0; i < numberOfItems; i++){
        bool rest = dec%2;
        dec /= 2;
        bin[i] = rest;
    }

    return bin;
}

double DiscreteKnapsackProblem::testTime(int algorithmType) {
    std::chrono::nanoseconds time_start;
    std::chrono::nanoseconds time_end;
    //double time_duration;

    this->loadFromFile("data_knapsack.txt");
    switch (algorithmType){
        case 0:
            time_start = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            this->bruteForce();
            time_end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            break;
        case 1:
            time_start = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            this->greedyAlgorithm();
            time_end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            break;
        case 2:
            time_start = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            this->dynamicProgramming();
            time_end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            break;
    }


    return (time_end - time_start) / std::chrono::nanoseconds(1);
}

void DiscreteKnapsackProblem::saveToFile(std::string filename) {
    ofstream fout;
    fout.open(filename.c_str());
    fout << sizeOfKnapsack << std::endl;
    fout << numberOfItems << std::endl;
    for (int i = 0; i < numberOfItems; i++) {
        fout << sizes[i] << " ";
        fout << values[i] << std::endl;
    }
}

void DiscreteKnapsackProblem::menu() {
    std::chrono::nanoseconds time_start;
    std::chrono::nanoseconds time_end;
    std::cout << "MENU - Problem plecakowy\n"
            "1. Wczytaj z pliku.\n"
            "2. Generuj losowo.\n"
            "3. Przeglad zupelny.\n"
            "4. Algorytm zachlanny.\n"
            "5. Programowanie dynamiczne.\n"
            "6. Wyjdz do glownego menu.\n"
            "Prosze wpisac odpowiednia liczbe.\n";
    int chosen;
    std::cin >> chosen;
    switch(chosen){
        case 1:
            this->loadFromFile("data_knapsack.txt");
            break;
        case 2:
            cout << "Prosze podac liczbe przedmiotow.\n";
            int v;
            cin >> v;
            cout << "Prosze podac pojemnosc plecaka.\n";
            cin >> chosen;
            this->generateRandom(v, chosen);
            break;
        case 3:
            time_start = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            std::cout << "\n########################################\n" << this->bruteForce();
            time_end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            cout << "Czas: " << (time_end - time_start) / std::chrono::nanoseconds(1) << " nanosekund.\n";
            break;
        case 4:
            time_start = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            std::cout << "\n########################################\n" << this->greedyAlgorithm();
            time_end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            cout << "Czas: " << (time_end - time_start) / std::chrono::nanoseconds(1) << " nanosekund.\n";
            break;
        case 5:
            time_start = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            std::cout << "\n########################################\n" << this->dynamicProgramming();
            time_end = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch());
            cout << "Czas: " << (time_end - time_start) / std::chrono::nanoseconds(1) << " nanosekund.\n";
            break;
        case 6:
            return;
        default:
            cout << "Prosze podac poprawna liczbe.\n";
            cin.clear();
            cin.sync();
            break;
    }
    this->menu();
}
