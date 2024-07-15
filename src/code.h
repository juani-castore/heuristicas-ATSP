#include <vector>
#include "model.h"

using namespace std;

vector<vector<int>> readMatrix(const char* filename);
Tour nearestNeighbor(const vector<vector<int>>& matrix);
Tour bestTourBruteForce(const vector<vector<int>>& matrix, Tour actualTour, Tour bestTour);
Tour optmimalSolBF(const vector<vector<int>>& matrix);