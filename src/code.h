#include <vector>
#include "model.h"
#include <set>

using namespace std;

vector<vector<int>> readMatrix(const char* filename);
Tour nearestNeighbor(const vector<vector<int>>& matrix);
Tour bestTourBruteForce(const vector<vector<int>>& matrix, Tour actualTour, Tour bestTour);
Tour optmimalSolBF(const vector<vector<int>>& matrix);
int chooseGoodRandomCity(const vector<vector<int>>& matrix, const vector<bool>& visited, int currentCity, int N);
Tour probabilityGreedyConstructive(const vector<vector<int>>& matrix, int N = 4);
int chooseOneCity(set<pair<int, int>> cities);
Tour localSearchSwap(const vector<vector<int>>& matrix, Tour tour);
Tour multipleSwap(const vector<vector<int>>& matrix, Tour tour);
Tour multiProbMultiSwap(const vector<vector<int>>& matrix, int N, int iterations);
Tour multiNNSwap(const vector<vector<int>>& matrix, int iterations);