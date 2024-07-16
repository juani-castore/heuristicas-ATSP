#include "model.h"
#include "code.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>
#include <utility>
#include <ctime>

using namespace std;
//const
int INT_MAX = 999999999;

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

int chooseGoodRandomCity(const vector<vector<int>>& matrix, const vector<bool>& visited, int currentCity, int N){
    int dimension = matrix.size();
    set<pair<int, int>> cities;
    // busco las opciones posibles
    for (int i = 0; i < dimension; ++i) {
        if (!visited[i]) {
            cities.insert(make_pair(matrix[currentCity][i], i));
        }
    }
    // elimino las peores opciones
    while (cities.size() > N) {
        pair<int, int> worstCity = *cities.begin();
        for (pair<int, int> city : cities) {
            if (city.first > worstCity.first) {
                worstCity = city;
            }
        }
        cities.erase(worstCity);
    }
    // devuelvo una ciudad al azar entre las mejores opciones
    return chooseOneCity(cities);
}

int chooseOneCity(set<pair<int, int>> cities){
    // elije una ciudad al azar entre las mejores opciones
    srand(time(0));
    int randomIndex = rand() % cities.size();
    auto it = cities.begin();
    advance(it, randomIndex);
    return it->second;
}

Tour probabilityGreedyConstructive(const vector<vector<int>>& matrix, int N){
    Tour tour = Tour();
    int dimension = matrix.size();
    int currentCity = 0;
    tour.addCity(currentCity, 0);
    vector<bool> visited(dimension, false);
    visited[currentCity] = true;
    for (int i = 0; i < dimension - 1; ++i) {
        int nextCity = chooseGoodRandomCity(matrix, visited, currentCity, N);
        int distance = matrix[currentCity][nextCity];
        tour.addCity(nextCity, distance);
        visited[nextCity] = true;
        currentCity = nextCity;
    }
    tour.addCity(0, matrix[currentCity][0]);
    return tour;
}


Tour localSearchSwap(const vector<vector<int>>& matrix, Tour tour){
    // first improvement
    int dimension = matrix.size();
    int bestLength = tour.getLength();
    for (int i = 1; i < dimension-1; ++i) {
        for (int j = i +1; j < dimension; ++j) {
            tour.swapCities(i, j);
            tour.calculateLength(matrix);
            if (tour.getLength() < bestLength) {
                return tour;
            }
            tour.swapCities(i, j);
            tour.calculateLength(matrix);
        }
    }
    return tour;
}

Tour multipleSwap(const vector<vector<int>>& matrix, Tour tour){
    int lastLength = tour.getLength();
    Tour bestTour = localSearchSwap(matrix, tour);
    while (bestTour.getLength() < lastLength) {
        lastLength = bestTour.getLength();
        bestTour = localSearchSwap(matrix, bestTour);
    }
    return bestTour;
}
    

Tour multiProbMultiSwap(const vector<vector<int>>& matrix, int N, int iterations){
    int bestLength = INT_MAX;
    Tour bestTour;
    for (int i = 0; i < iterations; ++i) {
        Tour tour = probabilityGreedyConstructive(matrix, N);
        tour = multipleSwap(matrix, tour);
        if (tour.getLength() < bestLength) {
            bestLength = tour.getLength();
            bestTour = tour;
        }
    }
    return bestTour;
}

Tour multiNNSwap(const vector<vector<int>>& matrix, int iterations){
    int bestLength = INT_MAX;
    Tour bestTour;
    for (int i = 0; i < iterations; ++i) {
        Tour tour = nearestNeighbor(matrix);
        tour = multipleSwap(matrix, tour);
        if (tour.getLength() < bestLength) {
            bestLength = tour.getLength();
            bestTour = tour;
        }
    }
    return bestTour;
}


    


Tour optmimalSolBF(const vector<vector<int>>& matrix){
    Tour bestTour = nearestNeighbor(matrix);
    Tour actualTour = Tour();
    actualTour.addCity(0, 0);
    return bestTourBruteForce(matrix, bestTour, actualTour);
}

Tour bestTourBruteForce(const vector<vector<int>>& matrix, Tour bestTour, Tour actualTour) {
    // encontre un mejor tour
    if (actualTour.getCities().size() == matrix.size()) {
        actualTour.addCity(0, matrix[actualTour.getCities().back()][0]);
        actualTour.setLength(actualTour.getLength() + matrix[actualTour.getCities().back()][0]);
        if (actualTour.getLength() < bestTour.getLength()) {
            return actualTour;
        }
        return bestTour;
    }
    // poda por optimalidad
    if (actualTour.getLength() > bestTour.getLength())
    {
        return bestTour;
    }
    
    else {
        for (int i = 0; i < bestTour.getCities().size()-1; ++i) {
            // aca chequeo si la ciudad i no esta en el tour actual, es una poda
            if (!actualTour.isCityInTour(i)) {
                // agrego una city
                int distance = matrix[actualTour.getCities().back()][i];
                actualTour.addCity(i, distance);
                actualTour.printTour();
                // llamada recursiva
                bestTour = bestTourBruteForce(matrix, bestTour, actualTour);
                // saco la city
                actualTour.removeLastCity(distance);
            }
        }
        return bestTour;
    }
}