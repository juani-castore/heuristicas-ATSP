#include "model.h"
#include "code.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;
//const
int INT_MAX = 9999;

// read .atsp file
vector<vector<int>> readMatrix(const char* filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        exit(1);
    }
    
    std::string line;
    int dimension = 0;
    bool readMatrix = false;
    std::vector<std::vector<int>> matrix;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string keyword;
        iss >> keyword;

        if (keyword == "DIMENSION:") {
            iss >> dimension;
            matrix.resize(dimension, std::vector<int>(dimension));
        } else if (keyword == "EDGE_WEIGHT_SECTION") {
            readMatrix = true;
            break;  // Start reading the matrix in the next loop
        }
    }

    if (readMatrix) {
        for (int i = 0; i < dimension; ++i) {
            for (int j = 0; j < dimension; ++j) {
                file >> matrix[i][j];
            }
        }
    }

    file.close();
    return matrix;

}


Tour nearestNeighbor(const vector<vector<int>>& matrix) {
    vector<int> cities;
    int length = 0;
    int dimension = matrix.size();
    vector<bool> visited(dimension, false);
    int currentCity = 0;
    cities.push_back(currentCity);
    visited[currentCity] = true;
    for (int i = 0; i < dimension - 1; ++i) {
        int nearestCity = -1;
        int minDistance = INT_MAX;
        for (int j = 0; j < dimension; ++j) {
            if (!visited[j] && matrix[currentCity][j] < minDistance) {
                nearestCity = j;
                minDistance = matrix[currentCity][j];
            }
        }
        cities.push_back(nearestCity);
        length += minDistance;
        visited[nearestCity] = true;
        currentCity = nearestCity;
    }
    length += matrix[currentCity][0];
    cities.push_back(0);
    return Tour(cities, length);
}

Tour optmimalSolBF(const vector<vector<int>>& matrix){
    Tour optimalTour = nearestNeighbor(matrix);
    return bestTourBruteForce(matrix, optimalTour, optimalTour);
}

Tour bestTourBruteForce(const vector<vector<int>>& matrix, Tour bestTour, Tour actualTour) {
    // poda por optimalidad
    if (actualTour.getLength() > bestTour.getLength()) {
        return bestTour;
    }
    // encontre un mejor tour
    if (actualTour.getCities().size() == matrix.size()) {
        return actualTour;
    }
    // busco el mejor tour
    for (int i = 0; i < matrix.size(); ++i) {
        if (std::find(actualTour.getCities().begin(), actualTour.getCities().end(), i) == actualTour.getCities().end()) {
            Tour newTour = actualTour;
            newTour.addCity(i, matrix[actualTour.getCities().back()][i]);
            bestTour = bestTourBruteForce(matrix, bestTour, newTour);
            newTour.removeLastCity(matrix[actualTour.getCities().back()][i]);
        }
    }
    return bestTour;
}