/****************************
 * Lab 3: exercise 2        *
 ****************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> // For std::ostringstream
#include <cmath>
#include <numeric> // For std::adjacent_difference
#include <iomanip> // For formatting output
#include <iterator> // For std::istream_iterator and std::ostream_iterator
#include <functional>  // For std::transform

int main() {
    std::ifstream file("/Users/romeodahlstrom/Documents/lab3/code/points.txt");
    if (!file) {
        std::cerr << "Error: Could not open file." << std::endl;
        return 1;
    }

    std::vector<std::pair<int, int>> points;
    std::string line;

    /*// Read points from file
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int x, y;
        char comma;
        ss >> x >> comma >> y; // Read in the format x,y
        points.emplace_back(x, y); // Store the point as a pair in the vector
    }*/
    
    // Process file line by line and transform lines into pairs
    std::vector<std::string> lines((std::istream_iterator<std::string>(file)),
                                   std::istream_iterator<std::string>());

    std::transform(lines.begin(), lines.end(), std::back_inserter(points),
                   [](const std::string& entry) {
                       std::stringstream ss(entry);
                       int x, y;
                       char comma;
                       ss >> x >> comma >> y;
                       return std::make_pair(x, y);
                   });

    // Debug: Print points
        if (points.empty()) {
            std::cerr << "Error: No points found in the file." << std::endl;
            return 1;
        }
    
    // Print the points using std::transform
   std::cout << "The points:" << std::endl;
   std::transform(points.begin(), points.end(), std::ostream_iterator<std::string>(std::cout, "\n"),
                  [](const std::pair<int, int>& point) {
                      std::ostringstream oss;
                      oss << "(" << point.first << ", " << point.second << ")";
                      return oss.str();
                  });

    // Vector to store distances between consecutive points
    std::vector<double> distances(points.size(), 0.0);
    
    // Handle the first element manually
    distances[0] = 0.0; // First element is a placeholder

    // Calculate distances using std::transform
    std::transform(points.begin(), points.end() - 1, points.begin() + 1, distances.begin(),
                   [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                       int dx = b.first - a.first;
                       int dy = b.second - a.second;
                       return std::sqrt(dx * dx + dy * dy);
                   });
    
    /*for (size_t i = 0; i < distances.size(); ++i) {
        std::cout << "distances[" << i << "] = " << distances[i] << std::endl;
    }*/

    // Sum up the distances to get the total distance travelled
    double totalDistance = std::accumulate(distances.begin(), distances.end(), 0.0); // Skip the first element

    // Print the total distance travelled
    std::cout << "\n" << "Distance travelled: " << std::fixed << std::setprecision(3) << totalDistance << std::endl;

    return 0;
}
