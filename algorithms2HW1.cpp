// algorithms2HW1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Graph.h"
#include <random>
#include <ctime>
#include<fstream>
#include<cmath>
#define V 1000
#define graphs_num 500
#include <chrono>
using namespace std::chrono;

void main()
{
    vector<vector<long double> > vec;
    long double prediction[10];
    long double prediction1[10];
    long double treshold_1_2 = logf(V) / V;
    long double treshold_3 = sqrtf(2 * treshold_1_2);
    long double connected = 0.0;
    long double isolated = 0.0;
    long double diam = 0.0;
    int ConnectedGraph = 0;
    long double p = 0;
    srand(static_cast <unsigned> (time(0)));
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 10; i++)
    {
        p = (i + 1) * 2 * treshold_1_2 / 10.1;
        isolated = 0.0;
        diam = 0.0;
        connected = 0.0;
        for (int j = 0; j < graphs_num; j++)
        {
            Graph g = build_random_graph(V, p);
            if (Is_Isolated(g)) {
                isolated++;
                continue;
            }
            if (connectivity(g)) {
                connected++;
            }
        }
        prediction[i] = p;
        cout << "finished cheking connectivity and isolated of " << (i+1)*500 << " graphs"<<endl;
        p = (i + 1) * 2 * treshold_3 / 10.1;
        for (int j = 0; j < graphs_num; j++)
        {
            Graph g = build_random_graph(V, p);
            if (diameter(g) == 2) {
                diam ++ ;
            }
        }
        cout << "finished cheking diameter of " << (i + 1) * 500 << " graphs" << endl;
        prediction1[i] = p;
        vector<long double> v1;
        v1.push_back(connected / graphs_num);
        v1.push_back(isolated / graphs_num);
        v1.push_back(diam / graphs_num);
        vec.push_back(v1);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<minutes>(stop - start);
    cout << "Time taken by function: "
        << duration.count() << " minuts" << endl;
    // Send data to the stream
    ofstream file("results.csv");
    file << "P";
    for (int i = 0; i < 10; i++)
    {
        file << "," << prediction[i];
    }
    file << "\n";

        file << "Probability of connected graphs:"<< ",";
        for (int j = 0; j < vec.size(); ++j)
        {
            file << vec[j][0];
            if (j != vec.size()-1) file << ","; // No comma at end of line
        }
        file << "\n";
        file << "Probability of isolated graphs:" << ",";
        for (int j = 0; j < vec.size(); ++j)
        {
            file << vec[j][1];
            if (j != vec.size() - 1) file << ","; // No comma at end of line
        }
        file << "\n";

    file << "\n";
    file << "P";
    for (int i = 0; i < 10; i++)
    {
        file << "," << prediction1[i];
    }

    file << "\nDiameter averages:,";
    for (int j = 0; j < vec.size(); ++j)
    {
        file << vec[j][2];
        if (j != vec.size() - 1) file << ","; // No comma at end of line
    }

    file.close();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
