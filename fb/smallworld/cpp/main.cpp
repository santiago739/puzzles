#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

struct Point
{
    int id;
    double x;
    double y;
};


bool readInput(const char* fileName, vector<Point>& points)
{
    ifstream inFile(fileName);
    istringstream iss;
    string fileLine;
    Point tmpPoint;

    if (!inFile)
    {
        cerr << "Cannot open " << fileName << endl;
        return false;
    }

    while (!getline(inFile, fileLine).eof())
    {
        iss.clear();
        iss.str(fileLine);
        iss >> tmpPoint.id >> tmpPoint.x >> tmpPoint.y;
        points.push_back(tmpPoint);
    }

    return true;
}

int main(int argc, char *argv[])
{
    vector<Point> points;

    if (argc != 2 || !readInput(argv[1], points))
    {
        return 1;
    }

#ifdef DEBUG
    cout << "Points:\n";
    for (size_t i = 0; i < points.size(); i++)
    {
        cout << points[i].id << " " << points[i].x << " " << points[i].y << endl;
    }
#endif

    return 0;
}
