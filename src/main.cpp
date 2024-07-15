#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "model.h"
#include "code.h"

using namespace std;

const char* nombre_archivo = "../ALL_atsp/br17.atsp";


int main() {
    
    vector<vector<int>> matrix = readMatrix(nombre_archivo);
    int dimension = matrix.size();
    printf("Dimension: %d\n", dimension);

    // print matrix
    /*
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    */
    Tour tourNN = nearestNeighbor(matrix);
    tourNN.printTour();

    Tour tourBF = optmimalSolBF(matrix);
    tourBF.printTour();

    return 0;
}
