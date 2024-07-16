#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "model.h"
#include "code.h"

using namespace std;

// el prob_num deberia ser estimado en base al tamanio de la instancia
const char* nombre_archivo = "../ALL_atsp/ftv170.atsp";
const int PROB_NUM = 30;


int main() {
    
    vector<vector<int>> matrix = readMatrix(nombre_archivo);

    // print matrix
    /*
    int dimension = matrix.size();
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    */
    Tour tourNN = nearestNeighbor(matrix);
    tourNN.printTour();

    Tour improvedTour = multipleSwap(matrix, tourNN);
    improvedTour.printTour();

    //Tour tourProbabilistic = probabilityGreedyConstructive(matrix, PROB_NUM);
    //tourProbabilistic.printTour();

    //Tour tourLS = multipleSwap(matrix, tourProbabilistic);
    //tourLS.printTour();


    Tour tourProbaSwap = multiProbMultiSwap(matrix, PROB_NUM, 100);
    tourProbaSwap.printTour();




    //Tour tourBF = optmimalSolBF(matrix);
    //tourBF.printTour();



    return 0;
}
