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
#include <utility>
#include <queue>
#include <iterator>
#include <map>
#include <set>
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
    bool **testConnectivityMatrix;
    float **testDistanceMatrix;

    // void generateMatrices()
    // {
    //     srand(time(0));
    //     connectivityMatrix = new bool *[size];
    //     for (int i = 0; i < size; ++i)
    //     {
    //         connectivityMatrix[i] = new bool[size];
    //     }

    //     distanceMatrix = new float *[size];
    //     for (int i = 0; i < size; ++i)
    //     {
    //         distanceMatrix[i] = new float[size];
    //     }

    //     for (int j = 0; j < size; ++j)
    //     {
    //         for (int k = 0; k < size; ++k)
    //         {
    //             if (j != k && k > j)
    //             {
    //                 int x = rand() % 100;
    //                 if (x < density * 100)
    //                 {
    //                     int randVal = rand() / 100;
    //                     int randMax = RAND_MAX / 100;
    //                     float d = static_cast<float>((90 * randVal) / randMax) / 10 + 1;
    //                     connectivityMatrix[j][k] = 1;
    //                     connectivityMatrix[k][j] = 1;
    //                     distanceMatrix[j][k] = d;
    //                     distanceMatrix[k][j] = d;
    //                 }
    //             }
    //         }
    //     }
    // }

public:
    CityMap(int s, float d)
    {
        size = s;
        density = d;
        generateMatrices();
        // generateTestMatrices();
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

    void generateMatrices()
    {
        srand(time(0));
        connectivityMatrix = new bool *[9];
        for (int i = 0; i < 9; ++i)
        {
            connectivityMatrix[i] = new bool[9];
        }

        distanceMatrix = new float *[9];
        for (int i = 0; i < 9; ++i)
        {
            distanceMatrix[i] = new float[9];
        }

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

vector<City> dijkstras(CityMap cityMapObj)
{
    vector<City> closedCities;
    vector<City> openCities;
    City originCity(0, 0.0);
    City currentCity = originCity;
    vector<City> neighbors = cityMapObj.GetNeighbors(currentCity);

    for (int i = 0; i < neighbors.size(); ++i)
    {
        openCities.push_back(neighbors[i]);
    }

    // Print neighbors found
    // cout << "NEIGHBORDS FOUND:" << endl;
    // for (int i = 0; i < neighbors.size(); ++i)
    // {
    //     cout << "\tindex i: " << i << endl;
    //     cout << "\tneighbors[i].index: " << neighbors[i].index << endl;
    //     cout << "\tneighbors[i].distance: " << neighbors[i].distance << endl;
    // }

    openCities = cityMapObj.SortCitiesDesc(openCities);

    closedCities.push_back(originCity);
    // Print cities in openSet
    // cout << "openCities CURRENTLY:" << endl;
    // for (int i = 0; i < openCities.size(); ++i)
    // {
    //     cout << "\tindex i: " << i << endl;
    //     cout << "\topenCities[i].index: " << openCities[i].index << endl;
    //     cout << "\topenCities[i].distance: " << openCities[i].distance << endl;
    // }

    while (openCities.size())
    {
        // Find the lowest distance city in openCities
        City lowestDistCity = openCities.back();
        // cout << "lowestDistCity.index: " << lowestDistCity.index << endl;
        // cout << "lowestDistCity.distance: " << lowestDistCity.distance << endl;

        // Move lowest distance city from openCities to closedCities
        openCities.pop_back();
        closedCities.push_back(lowestDistCity);

        // Reassign currentCity to lowestDistCity
        currentCity = lowestDistCity;

        cout << "CURRENT CITY UPDATED:" << endl;
        cout << "currentCity.index: " << currentCity.index << endl;
        cout << "currentCity.distance: " << currentCity.distance << endl;

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
                    cout << "UPDATE: --------  UpdateNeighborInCities:" << endl;
                    for (int i = 0; i < openCities.size(); ++i)
                    {
                        cout << "\tindex i: " << i << endl;
                        cout << "\topenCities[i].index: " << openCities[i].index << endl;
                        cout << "\topenCities[i].distance: " << openCities[i].distance << endl;
                    }
                }
            }
        }
        // Print cities in openSet
        cout << "XXxxXXXXxxXXxxxX openCities UPDATED XxxxxxxxXXxx:" << endl;
        for (int i = 0; i < openCities.size(); ++i)
        {
            cout << "\tindex i: " << i << endl;
            cout << "\topenCities[i].index: " << openCities[i].index << endl;
            cout << "\topenCities[i].distance: " << openCities[i].distance << endl;
        }
        cout << "``````````````CLOSED CITIES UPDATED ```````````:" << endl;
        for (int i = 0; i < closedCities.size(); ++i)
        {
            cout << "\tindex i: " << i << endl;
            cout << "\tclosedCities[i].index: " << closedCities[i].index << endl;
            cout << "\tclosedCities[i].distance: " << closedCities[i].distance << endl;
        }

        // Sort cities by descending order
        openCities = cityMapObj.SortCitiesDesc(openCities);
    }

    return closedCities;
}

int main(void)
{
    // Hard assign size & density
    int size = 9;
    float density = .40;

    // Generate graph & print
    CityMap cityMap(size, density);
    cityMap.printConnectivityMatrix();
    cityMap.printDistanceMatrix();
    vector<City> dijkstrasShortestPath = dijkstras(cityMap);
    double sum;
    cout << "dijkstrasShortestPath:" << endl;
    for (int i = 0; i < dijkstrasShortestPath.size(); ++i)
    {
        cout << "\tindex i: " << i << endl;
        cout << "\tdijkstrasShortestPath[i].index: " << dijkstrasShortestPath[i].index << endl;
        cout << "\tdijkstrasShortestPath[i].distance: " << dijkstrasShortestPath[i].distance << endl;
        sum += dijkstrasShortestPath[i].distance;
    }
    double avg = sum / (dijkstrasShortestPath.size() - 1);
    cout << "dijkstrasShortestPath sum: " << sum << endl;
    cout << "dijkstrasShortestPath avg: " << avg << endl;
    return 0;
}

// Vertex   Distance from Source
// 0                0
// 1                4
// 2                12
// 3                19
// 4                21
// 5                11
// 6                9
// 7                8
// 8                14

// 98 / 8 = 12.25
