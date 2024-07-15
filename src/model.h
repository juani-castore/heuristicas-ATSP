// tour.h

#include <iostream>
#include <vector>

using namespace std;

#ifndef TOUR_H // Guardia de inclusión para evitar inclusiones duplicadas
#define TOUR_H


class Tour {
private:
    std::vector<int> cities;   // List of cities (integers)
    int length;                // Length of the tour
    
public:

    // Constructor
    Tour() : length(0) {}

    // Constructor
    Tour(std::vector<int> cities, int length) : cities(cities), length(length) {}

    // Destructor
    ~Tour() {}

    // Getters
    std::vector<int> getCities() const { return cities; }
    int getLength() const { return length; }

    // Setters
    void setCities(std::vector<int> cities) { this->cities = cities; }
    void setLength(int length) { this->length = length; }
    void addCity(int city, int distance) { cities.push_back(city); length += distance; }
    void removeLastCity(int distance) { cities.pop_back(); length -= distance; }
    void calculateLength(const std::vector<std::vector<int>>& matrix) {
        length = 0;
        for (int i = 0; i < cities.size() - 1; ++i) {
            length += matrix[cities[i]][cities[i + 1]];
        }
        length += matrix[cities.back()][cities.front()];
    }
    // Print the tour
    void printTour() const {
        for (int city : cities) {
            std::cout << city << " ";
        }
        std::cout << std::endl;
        std::cout << "Length: " << length;
        std::cout << std::endl;
    }
};
#endif // TOUR_H