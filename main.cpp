#include <iostream>
#include <ctime>
#include "Problem.h"
#include "DiscreteKnapsackProblem.h"
#include "TravellingSalesmanProblem.h"

void test();
void mainMenu(Problem *p);

int main() {
    srand(time(NULL));

    Problem * p;
    mainMenu(p);
    delete p;
    //test();

    return 0;
}

void mainMenu(Problem *p) {
    std::cout << "MENU\n"
            "1. Problem plecakowy.\n"
            "2. Problem komiwojazera.\n"
            "3. Wyjdz z programu.\n"
            "Prosze wpisac odpowiednia liczbe.";
    int chosen;
    std::cin >> chosen;
    switch(chosen){
        case 1:{
            p = new DiscreteKnapsackProblem();
            p->menu();
        }
            break;
        case 2: {
            p = new TravellingSalesmanProblem();
            p->menu();
        }
            break;
        case 3:{
            if (p!=NULL) delete p;
            exit(0);
            break;
        }
        default:
            cout << "Prosze podac poprawna liczbe.\n";
            cin.clear();
            cin.sync();
            break;
    }
    mainMenu(p);
}

void test(){
    Problem *p = new TravellingSalesmanProblem();
    std::ofstream fout;
    fout.open("results.txt");
    int size[] = {8,9,10,11,12};
    int knapsack[] = {50,100,500};
    int algorithms[] = {0, 1, 2};
    for (int j = 0; j < 3; j++){ //gestosc
        cout << "d:  " << knapsack[j] << endl;
        for (int k = 0; k < 2; k++){ //algorytmy
            cout << "a:    " << algorithms[k] << endl;
            for (int l = 0; l < 5; l++){ //wielkosc
                for (int i = 0; i < 10; i++){ //powtorzenia
                    p->generateRandom(size[l],0);
                    p->saveToFile("data_salesman.txt");

                    fout << knapsack[j] << " " << algorithms[k] << " " << size[l] << " "
                         << p->testTime(algorithms[k])
                         << endl;
                }
            }
        }
    }

    fout.close();
    delete p;
}