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
    bool **testConnectivityMatrix;
    float **testDistanceMatrix;

    void generateMatrices()
    {
        srand(time(0));
        connectivityMatrix = new bool *[size];
        for (int i = 0; i < size; ++i)
        {
            connectivityMatrix[i] = new bool[size];
        }

        distanceMatrix = new float *[size];
        for (int i = 0; i < size; ++i)
        {
            distanceMatrix[i] = new float[size];
        }

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
    CityMap(int s, float d)
    {
        size = s;
        density = d;
        generateMatrices();
        generateTestMatrices();
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
        cout << "Connectivity Matrix" << endl;
        for (int j = 0; j < size; ++j)
        {
            for (int k = 0; k < size; ++k)
            {
                cout << connectivityMatrix[j][k] << "\t";
            }
            cout << endl;
        }
    }

    void printDistanceMatrix()
    {
        cout << "Distance Matrix" << endl;
        for (int l = 0; l < size; ++l)
        {
            for (int m = 0; m < size; ++m)
            {
                cout << distanceMatrix[l][m] << "\t";
            }
            cout << endl;
        }
    }

    vector<City> GetNeighbors(City currentCity, bool testing = false)
    {
        if (testing)
        {
            connectivityMatrix = testConnectivityMatrix;
            distanceMatrix = testDistanceMatrix;
        }
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

    void printTestConnectivityMatrix()
    {
        cout << "Test Connectivity Matrix" << endl;
        for (int j = 0; j < 9; ++j)
        {
            for (int k = 0; k < 9; ++k)
            {
                cout << testConnectivityMatrix[j][k] << "\t";
            }
            cout << endl;
        }
    }

    void printTestDistanceMatrix()
    {
        cout << "Test Distance Matrix" << endl;
        for (int l = 0; l < 9; ++l)
        {
            for (int m = 0; m < 9; ++m)
            {
                cout << testDistanceMatrix[l][m] << "\t";
            }
            cout << endl;
        }
    }

    void generateTestMatrices()
    {
        srand(time(0));
        testConnectivityMatrix = new bool *[9];
        for (int i = 0; i < 9; ++i)
        {
            testConnectivityMatrix[i] = new bool[9];
        }

        testDistanceMatrix = new float *[9];
        for (int i = 0; i < 9; ++i)
        {
            testDistanceMatrix[i] = new float[9];
        }

        testConnectivityMatrix[0][1] = true;
        testConnectivityMatrix[0][7] = true;
        testConnectivityMatrix[1][0] = true;
        testConnectivityMatrix[1][7] = true;
        testConnectivityMatrix[1][2] = true;
        testConnectivityMatrix[2][1] = true;
        testConnectivityMatrix[2][8] = true;
        testConnectivityMatrix[2][5] = true;
        testConnectivityMatrix[2][3] = true;
        testConnectivityMatrix[3][2] = true;
        testConnectivityMatrix[3][5] = true;
        testConnectivityMatrix[3][4] = true;
        testConnectivityMatrix[4][3] = true;
        testConnectivityMatrix[4][5] = true;
        testConnectivityMatrix[5][6] = true;
        testConnectivityMatrix[5][2] = true;
        testConnectivityMatrix[5][3] = true;
        testConnectivityMatrix[5][4] = true;
        testConnectivityMatrix[6][7] = true;
        testConnectivityMatrix[6][8] = true;
        testConnectivityMatrix[6][5] = true;
        testConnectivityMatrix[7][0] = true;
        testConnectivityMatrix[7][1] = true;
        testConnectivityMatrix[7][8] = true;
        testConnectivityMatrix[7][6] = true;
        testConnectivityMatrix[8][7] = true;
        testConnectivityMatrix[8][2] = true;
        testConnectivityMatrix[8][6] = true;

        testDistanceMatrix[0][1] = 4;
        testDistanceMatrix[0][7] = 8;
        testDistanceMatrix[1][0] = 4;
        testDistanceMatrix[1][7] = 11;
        testDistanceMatrix[1][2] = 8;
        testDistanceMatrix[2][1] = 8;
        testDistanceMatrix[2][8] = 2;
        testDistanceMatrix[2][5] = 4;
        testDistanceMatrix[2][3] = 7;
        testDistanceMatrix[3][2] = 7;
        testDistanceMatrix[3][5] = 14;
        testDistanceMatrix[3][4] = 9;
        testDistanceMatrix[4][3] = 9;
        testDistanceMatrix[4][5] = 10;
        testDistanceMatrix[5][6] = 2;
        testDistanceMatrix[5][2] = 4;
        testDistanceMatrix[5][3] = 14;
        testDistanceMatrix[5][4] = 10;
        testDistanceMatrix[6][7] = 1;
        testDistanceMatrix[6][8] = 6;
        testDistanceMatrix[6][5] = 2;
        testDistanceMatrix[7][0] = 8;
        testDistanceMatrix[7][1] = 11;
        testDistanceMatrix[7][8] = 7;
        testDistanceMatrix[7][6] = 1;
        testDistanceMatrix[8][7] = 7;
        testDistanceMatrix[8][2] = 2;
        testDistanceMatrix[8][6] = 6;
    }

    int GetIdxOfShortestDistanceCity(vector<City> openCities)
    {
        float shortestDist = INFINITY;
        int tempCityIdx;
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

vector<City> dijkstras(CityMap cityMapObj, bool testing = false)
{
    // Intiailzing necessary containers
    vector<City> closedCities,
        openCities,
        neighbors;
    City originCity(0, 0.0);
    City currentCity = originCity;

    // Control statement to support testing data
    // Retrieving initial neighboring cities for currentCity
    if (testing)
    {
        neighbors = cityMapObj.GetNeighbors(currentCity, true);
    }
    else
    {
        neighbors = cityMapObj.GetNeighbors(currentCity);
    }

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

int main(void)
{
    // Hard assign size & density
    int size = 9;
    float density = .40;

    // Generate graph & print
    CityMap cityMap(size, density);
    vector<City> dijkstrasShortestPath = dijkstras(cityMap);
    vector<City> testDijkstrasShortestPath = dijkstras(cityMap, true);
    double sum = 0.0,
           testSum = 0.0;
    cout << "dijkstrasShortestPath:" << endl;
    for (vector<City>::iterator i = dijkstrasShortestPath.begin(); i != dijkstrasShortestPath.end(); ++i)
    {
        sum += (*i).distance;
    }
    for (vector<City>::iterator i = testDijkstrasShortestPath.begin(); i != testDijkstrasShortestPath.end(); ++i)
    {
        testSum += (*i).distance;
    }
    double testAvg = testSum / (testDijkstrasShortestPath.size() - 1);
    cout << "testDijkstrasShortestPath sum: " << testSum << endl;
    cout << "testDijkstrasShortestPath avg: " << testAvg << endl;

    double avg = sum / (dijkstrasShortestPath.size() - 1);
    cout << "dijkstrasShortestPath sum: " << sum << endl;
    cout << "dijkstrasShortestPath avg: " << avg << endl;
    return 0;
}