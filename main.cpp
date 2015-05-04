/*! 
 *  \mainpage Dijkstra Algorithm
 *  \section intro_sec Description
 *  There is example of using Dijkstra Algorithm.
 */

/*!
 *  \file main.cpp 
 */
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

/* IMPORTANT NOTE:
   Using atoi() instead of stoi()
   atoi() can convert words to 0 value unlike stoi()
   Simple protection from fools */

/*! 
 *  \brief String-splitting algorithm.
 *  \param string Splitted string.
 *  \param delim Delimiter for splitting.
 *  \return items Vector of source string parts.
 */
std::vector <std::string> split(std::string &string, char delim) 
{
    std::vector <std::string> items;
    std::stringstream stringStream (string);
    std::string item;

    while (std::getline(stringStream, item, delim))
        if (item.size())
            items.push_back(item);

    return items;
}

/*! 
 *  \brief Dijkstra algorithm function.
 *  \warning The result will be shown in console.
 *  \param matrix Reference to matrix of weights of routes between vertexes.
 *  \param amount Amount of vertexes.
 *  \param vertex Vertex to start the algorithm.
 *  \return Function returns nothing.
 */
void DijkstraAlgorithm(int**& matrix, int amount, int vertex)
{
    int infinity = std::numeric_limits<int>::max(),
        index, minValue;

    int* routeLength = new int [amount];
    bool* routeVisited = new bool [amount];

    for (int i = 0; i < amount; i ++)
    {
        routeLength[i] = i == vertex ? 0 : infinity;
        routeVisited[i] = false;
    }

    for (int i = 0; i < amount - 1; i ++)
    {
        minValue = infinity;

        for (int j = 0; j < amount; j ++)
        {
            if (!routeVisited[j] && routeLength[j] <= minValue)
            {
                minValue = routeLength[j]; 
                index = j;
            }
        }

        routeVisited[index] = true;

        for (int j = 0; j < amount; j ++)
            if (!routeVisited[j] && matrix[index][j] && routeLength[index] != infinity && routeLength[j] > (routeLength[index] + matrix[index][j]))
                routeLength[j] = routeLength[index] + matrix[index][j];
    }

    std::cout << std::endl << "All routes for vertex #" << vertex + 1 << " :" << std::endl;

    for (int i = 0; i < amount; i ++)
    {
        if (vertex != i)
        {
            if (routeLength[i] != infinity)
                std::cout << vertex + 1 << " ---> " << i + 1 << " : route length = " << routeLength[i] << std::endl;
            else 
                std::cout << vertex + 1 << " ---> " << i + 1 << " : route is unavailabe" << std::endl;
        }
    }

    std::cout << std::endl;

    delete [] routeLength;
    delete [] routeVisited;
}


/*! 
 *  \brief Program entry point.
 *  \details User initializes a graph: he sets amount of vertexes, the vertex for start and the matrix itself. Then, users launches Dijkstra algorithm.
 */
void main()
{
    int amount = 0,
        vertex = 0,
        **matrix;

    std::string string;
    std::vector <std::string> matrixRow;

    do
    {
        std::cout << "Vertex amount (2 or more) : "; 
        std::cin >> string;

        amount = atoi(string.c_str()); 

        if (amount < 2)
            std::cout << "Bad vertex amount." << std::endl; 
    }
    while (amount < 2);

    std::cout << std::endl;

    matrix = new int* [amount];
    for (int i = 0; i < amount; i ++)
        matrix[i] = new int [amount];

    for (int i = 0; i < amount; i ++)
    {
        std::cout << "Matrix row #" << i + 1 << " : ";

        fflush (stdin);
        getline (std::cin, string);
        matrixRow = split(string, ' ');

        if (matrixRow.size() != amount)
        {
            std::cout << "Bad matrix row." << std::endl;
            i --;
            continue;
        }

        if (atoi(matrixRow.at(i).c_str()) != 0)
        {
            std::cout << "No loops in Dijkstra Algorithm. (self-route should be equal zero)" << std::endl;
            i --;
            continue;
        }

        for (int j = 0; j < amount; j ++)
            matrix [i][j] = atoi(matrixRow[j].c_str());
    }

    std::cout << std::endl;

    do
    {
        std::cout << "All routes for vertex (1 - " << amount << ") : "; 
        std::cin >> string;

        vertex = atoi(string.c_str()); 
        if (vertex < 1 || vertex > amount)
            std::cout << "Bad vertex chosen." << std::endl;
    
    }
    while (vertex < 1 || vertex > amount);

    DijkstraAlgorithm(matrix, amount, vertex - 1);

    for (int i = 0; i < amount; i ++)
        delete [] matrix[i];
    delete [] matrix;
}
