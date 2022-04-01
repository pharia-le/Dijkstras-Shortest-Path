/*
    Graph algorithms and graph representation are a critical tool in CS.
    We want to create a graph as an ADT (Abstract Data Type) using C++ classes.
    The basic problem will be to write Dijkstra’s algorithm as a class member function (method in OO speak).
    You should already know Dijkstra’s algorithm for the shortest path problem from prior experience, but it will be reviewed in class.
    It is the basis for many route calculations and optimizations programs.

    There are 2 basic implementations used for graphs – one is edge lists, and the other is connectivity matrices.
    You can decide which to use, but comment on your choice.

    Basic problem:
    Write a set of constructors for declaring and initializing a gra ph.
    An edge will have a positive cost that is its distance.
    Have a procedure that produces a randomly generated set of edges with positive distances.
    Assume the graphs are undirected.
    The random graph procedure should have edge density as a parameter and distance range as a parameter.
    So a graph whose density is 0.1 would have 10% of its edges picked at random and
    its edge distance would be selected at random from the distance range.
    The procedure should run through all possible undirected edges, say (i,j) and
    place the edge in the graph if a random probability calculation is less than the density.
    Compute for a set of randomly generated graphs an average shortest path.

    Turn in:
    Printout of program, 200 words on what you learned, and output showing the average path length calculation.
    Use densities: 20% and 40% on a graph of 50 nodes with a distance range of 1.0 to 10.0.
    To get an average path length, compute the 49 paths:

    1 to 2, 1 to 3, 1 to 4, …, 1 to 50.

    [In an instance where there is no path between 1 and n, omit that value from the average. This should be very rare for the chosen density and size in this homework.]

    Pharia Le
    23 March 2022
*/

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

class City
{
public:
    int index;
    float distance;

    City(int index, float distance)
    {
        this->index = index;
        this->distance = distance;
    }
};

bool compareCityDistances(City city1, City city2)
{
    return (city1.distance > city2.distance);
}

class CityMap
{
private:
    int size;
    float density;
    bool **connectivityMatrix;
    float **distanceMatrix;

    void generateMatrices()
    {
        connectivityMatrix = new bool* [size];
        distanceMatrix = new float* [size];
        for (int i = 0; i < size; ++i)
        {
            connectivityMatrix[i] = new bool[size];
            distanceMatrix[i] = new float[size];
        }

        for (int j = 0; j < size; ++j)
        {
            for (int k = 0; k < size; ++k)
            {
                connectivityMatrix[j][k] = false;
                connectivityMatrix[k][j] = false;
                distanceMatrix[j][k] = 0;
                distanceMatrix[k][j] = 0;
            }
        }
    }

    void populateMatricesWithRandomData()
    {
        srand(static_cast<unsigned int>(time(0)));
        for (int j = 0; j < size; ++j)
        {
            for (int k = 0; k < size; ++k)
            {
                if (j != k && k > j)
                {
                    int x = rand() % 100;
                    if (x < density * 100)
                    {
                        int randVal = rand() / 100;
                        int randMax = RAND_MAX / 100;
                        float d = static_cast<float>((90 * randVal) / randMax) / 10 + 1;
                        connectivityMatrix[j][k] = 1;
                        connectivityMatrix[k][j] = 1;
                        distanceMatrix[j][k] = d;
                        distanceMatrix[k][j] = d;
                    }
                }
            }
        }
    }

public:
    //default constructor for test data matrices
    CityMap()
    {
        size = 9;
        density = 0;
        generateMatrices();
        populateMatricesWithTestData();
    }

    //default constructor to generate random data matrices
    CityMap(int s, float d)
    {
        size = s;
        density = d;
        generateMatrices();
        populateMatricesWithRandomData();
    }

    // ~CityMap()
    // {
    //     for (int i = 0; i < size; ++i)
    //     {
    //         delete[] connectivityMatrix[i];
    //         delete[] distanceMatrix[i];
    //     }
    //     delete connectivityMatrix;
    //     delete distanceMatrix;
    // }

    void printConnectivityMatrix()
    {
        cout << "---------------------- Connectivity Matrix ----------------------" << endl;
       
        int columns = 15;
        int pages = 0;
        if (size / 15 > 0) {
            pages = size / 15;
            if (size % 15 != 0) pages++;
        } else {
            pages = 1;
        }

        for (int p = 0; p < pages; p++) {
            cout << "------------------------- Index " << p*columns << " - " << (min((p + 1)* columns, size)) << " -------------------------\n";
            for (int q = 0; q < size; q++) {
                cout << q << " | ";
                for (int r = p * columns; r < min((p + 1)*columns, size); r++) {
                    cout << connectivityMatrix[q][r] << " | ";
                }
                cout << endl;
            }
        }
    }

    void printDistanceMatrix()
    {
        cout << "---------------------- Distance Matrix ----------------------" << endl;
        
        int columns = 15;
        int pages = 0;
        if (size / 15 > 0) {
            pages = size / 15;
            if (size % 15 != 0) pages++;
        } else {
            pages = 1;
        }
        
        for (int p = 0; p < pages; p++) {
            cout << "------------------------- Index " << p*columns << " - " << min((p + 1) * columns, size) << " -------------------------\n";
            for (int q = 0; q < size; q++) {
                cout << q << " | ";
                for (int r = p * columns; r < min((p + 1) * columns, size); r++) {
                    cout << distanceMatrix[q][r] << " | ";
                }
                cout << endl;
            }
        }
    }

    vector<City> GetNeighbors(City currentCity)
    {
        vector<City> neighbors;
        for (int i = 0; i < size; ++i)
        {
            if (connectivityMatrix[currentCity.index][i])
            {
                City neighbor(i, distanceMatrix[currentCity.index][i]);
                neighbors.push_back(neighbor);
            }
        }
        return neighbors;
    }

    int get_size_()
    {
        return size;
    }

    void populateMatricesWithTestData()
    {
        connectivityMatrix[0][1] = true;
        connectivityMatrix[0][7] = true;
        connectivityMatrix[1][0] = true;
        connectivityMatrix[1][7] = true;
        connectivityMatrix[1][2] = true;
        connectivityMatrix[2][1] = true;
        connectivityMatrix[2][8] = true;
        connectivityMatrix[2][5] = true;
        connectivityMatrix[2][3] = true;
        connectivityMatrix[3][2] = true;
        connectivityMatrix[3][5] = true;
        connectivityMatrix[3][4] = true;
        connectivityMatrix[4][3] = true;
        connectivityMatrix[4][5] = true;
        connectivityMatrix[5][6] = true;
        connectivityMatrix[5][2] = true;
        connectivityMatrix[5][3] = true;
        connectivityMatrix[5][4] = true;
        connectivityMatrix[6][7] = true;
        connectivityMatrix[6][8] = true;
        connectivityMatrix[6][5] = true;
        connectivityMatrix[7][0] = true;
        connectivityMatrix[7][1] = true;
        connectivityMatrix[7][8] = true;
        connectivityMatrix[7][6] = true;
        connectivityMatrix[8][7] = true;
        connectivityMatrix[8][2] = true;
        connectivityMatrix[8][6] = true;
        
        distanceMatrix[0][1] = 4;
        distanceMatrix[0][7] = 8;
        distanceMatrix[1][0] = 4;
        distanceMatrix[1][7] = 11;
        distanceMatrix[1][2] = 8;
        distanceMatrix[2][1] = 8;
        distanceMatrix[2][8] = 2;
        distanceMatrix[2][5] = 4;
        distanceMatrix[2][3] = 7;
        distanceMatrix[3][2] = 7;
        distanceMatrix[3][5] = 14;
        distanceMatrix[3][4] = 9;
        distanceMatrix[4][3] = 9;
        distanceMatrix[4][5] = 10;
        distanceMatrix[5][6] = 2;
        distanceMatrix[5][2] = 4;
        distanceMatrix[5][3] = 14;
        distanceMatrix[5][4] = 10;
        distanceMatrix[6][7] = 1;
        distanceMatrix[6][8] = 6;
        distanceMatrix[6][5] = 2;
        distanceMatrix[7][0] = 8;
        distanceMatrix[7][1] = 11;
        distanceMatrix[7][8] = 7;
        distanceMatrix[7][6] = 1;
        distanceMatrix[8][7] = 7;
        distanceMatrix[8][2] = 2;
        distanceMatrix[8][6] = 6;
    }

    int GetIdxOfShortestDistanceCity(vector<City> openCities)
    {
        float shortestDist = INFINITY;
        int tempCityIdx = -1;
        for (int m = 0; m < openCities.size(); ++m)
        {
            if (openCities[m].distance < shortestDist)
            {
                shortestDist = openCities[m].distance;
                tempCityIdx = m;
            }
        }
        return tempCityIdx;
    }

    vector<City> SortCitiesDesc(vector<City> openCities)
    {
        sort(openCities.begin(), openCities.end(), compareCityDistances);
        return openCities;
    }

    bool NeighborInCities(vector<City> cities, City neighbor)
    {
        for (int i = 0; i < cities.size(); ++i)
        {
            if (cities[i].index == neighbor.index)
            {
                return true;
            }
        }

        return false;
    }

    vector<City> UpdateNeighborInCities(vector<City> cities, City neighbor)
    {
        for (int i = 0; i < cities.size(); ++i)
        {
            if (cities[i].index == neighbor.index)
            {
                if (cities[i].distance > neighbor.distance)
                {
                    cities[i].distance = neighbor.distance;
                    break;
                }
            }
        }

        return cities;
    }
};

vector<City> dijkstras(CityMap cityMapObj)
{
    // Intiailzing necessary containers
    vector<City> closedCities,
        openCities,
        neighbors;
    City originCity(0, 0.0);
    City currentCity = originCity;

    // Retrieving initial neighboring cities for currentCity
    neighbors = cityMapObj.GetNeighbors(currentCity);
    
    // Adding initial neighbor cities to openCities
    for (int i = 0; i < neighbors.size(); ++i)
    {
        openCities.push_back(neighbors[i]);
    }

    // Adding originCity to closedCities
    closedCities.push_back(originCity);

    // Sorting openCities by distance
    openCities = cityMapObj.SortCitiesDesc(openCities);

    while (openCities.size())
    {
        // Find the lowest distance city in openCities
        City lowestDistCity = openCities.back();

        // Move lowest distance city from openCities to closedCities
        openCities.pop_back();
        closedCities.push_back(lowestDistCity);

        // Reassign currentCity to lowestDistCity
        currentCity = lowestDistCity;

        // Find neighbors of currentCity
        neighbors = cityMapObj.GetNeighbors(currentCity);

        // Check if each neighbor city in closedCities
        for (int i = 0; i < neighbors.size(); i++)
        {
            // Temp variable for current neighbor
            City neighbor = neighbors[i];

            // Update distance to account for path to originCity
            neighbor.distance = neighbor.distance + currentCity.distance;

            // Proceed if neighbor not in closedCities
            if (!cityMapObj.NeighborInCities(closedCities, neighbor))
            {
                // Check if neighbor in openCities

                // NOT in openCities, Add neighbor to openCities
                if (!cityMapObj.NeighborInCities(openCities, neighbor))
                {
                    openCities.push_back(neighbor);
                }
                // IN openCities, Update if distance is greater in neighbor within openCities
                else
                {
                    openCities = cityMapObj.UpdateNeighborInCities(openCities, neighbor);
                }
            }
        }

        // Sort cities by descending order
        openCities = cityMapObj.SortCitiesDesc(openCities);
    }

    // Returning closedCities containing dijkstras shortest paths
    return closedCities;
}

double averagePathLengths(vector<City> cities)
{
    // Initialize sum container
    double sum = 0.0;

    // Add all distances in cities
    for (vector<City>::iterator i = cities.begin(); i != cities.end(); ++i)
    {
        sum += (*i).distance;
    }

    // Calculate avg using sum of distances
    double avg = sum / (cities.size() - 1);

    return avg;
}

int main(void)
{
    // Hard assign size & density
    int size1 = 50;
    int size2 = 50;
    double density1 = .20;
    double density2 = .40;

    // Generate graph
    CityMap cityMap0;
    CityMap cityMap1(size1, density1);
    CityMap cityMap2(size2, density2);

    // Calculate shortest paths using dijkstras algorithms
    vector<City> dijkstrasShortestPath0 = dijkstras(cityMap0);
    vector<City> dijkstrasShortestPath1 = dijkstras(cityMap1);
    vector<City> dijkstrasShortestPath2 = dijkstras(cityMap2);

    // Calculate averages for path lengths                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     r paths
    double avg0 = averagePathLengths(dijkstrasShortestPath0);
    double avg1 = averagePathLengths(dijkstrasShortestPath1);
    double avg2 = averagePathLengths(dijkstrasShortestPath2);
    
    // Print graphs & calculated avg path lengths
    cout << "----------------------------------------------------------------" << endl;
    cout << "------------------------- Testing Data -------------------------" << endl;
    cout << "----------------------------------------------------------------" << endl;
    cityMap0.printConnectivityMatrix();
    cityMap0.printDistanceMatrix();
    cout << "----------------------------------------------------------------" << endl;
    cout << "Dijkstras Shortest Path Lengths Average: " << avg0 << endl;
    cout << "----------------------------------------------------------------\n\n";

    cout << "----------------------------------------------------------------" << endl;
    cout << "------------------- Size: 50 & Density: 20% -------------------" << endl;
    cout << "----------------------------------------------------------------" << endl;
    cityMap1.printConnectivityMatrix();
    cityMap1.printDistanceMatrix();
    cout << "----------------------------------------------------------------" << endl;
    cout << "Dijkstras Shortest Path Lengths Average: " << avg1 << endl;
    cout << "----------------------------------------------------------------\n\n";

    cout << "----------------------------------------------------------------" << endl;
    cout << "------------------- Size: 50 & Density: 40% -------------------" << endl;
    cout << "----------------------------------------------------------------" << endl;
    cityMap2.printConnectivityMatrix();
    cityMap2.printDistanceMatrix();
    cout << "----------------------------------------------------------------" << endl;
    cout << "Dijkstras Shortest Path Lengths Average: " << avg2 << endl;
    cout << "----------------------------------------------------------------\n\n";
    return 0;
}