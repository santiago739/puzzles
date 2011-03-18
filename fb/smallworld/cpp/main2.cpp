#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm> 

using namespace std;

struct Point
{
    int id;
    double coord[2];
};

struct KdNode
{
    Point data;
    KdNode *left;
    KdNode *right;

    KdNode(const Point & item)
      : data(item), left(NULL), right(NULL) { }
};

bool sortPointsByX(const Point & lhs, const Point & rhs) 
{
	return lhs.coord[0] < rhs.coord[0];
}

bool sortPointsByY(const Point & lhs, const Point & rhs) 
{
	return lhs.coord[1] < rhs.coord[1];
}

class KdTree
{
public:
    KdTree() : root(NULL) { }
    
//    void build(vector<Point> & points, size_t nPoints, int depth)
//    {
//        if (depth & 1)
//            sort(points.begin(), points.end(), sortPointsByY);
//        else
//            sort(points.begin(), points.end(), sortPointsByX);
            
//        size_t nPoints = nPoints >> 1;
//    }

    void insert(const Point & x)
    {
        insert(x, root, 0);
    }
    
    void print()
    {
        print(root, 0);
    }
    
    const Point nearest(const Point & x)
    {
        Point p;
        
        p = findParent(x, root, 0);
        
        return p;
    }
    
    const Point findParent(const Point & x, KdNode * & t, int level)
    {
        Point p;
        
        if (x.coord[level] < t->data.coord[level])
        {
            if (t->left == NULL)
                p = x;
            else 
                p = findParent(x, t->left, 1 - level);
        }
        else
        {
            if (t->right == NULL)
                p = x;
            else 
                p = findParent(x, t->right, 1 - level);
        }
            
        return p;
    }
        

private:
    KdNode *root;

    void insert(const Point & x, KdNode * & t, int level)
    {
        if (t == NULL)
            t = new KdNode(x);
        else if (x.coord[level] < t->data.coord[level])
            insert(x, t->left, 1 - level);
        else
            insert(x, t->right, 1 - level);
    }
    
    void print(KdNode * t, int level)
    {
        if (t == NULL)
        {
            return;
        }
        else 
        {
            cout << showbase << setw((level + 1) * 5) << "[ ID: " << t->data.id 
                 << " X: " << t->data.coord[0] << " Y: " << t->data.coord[1] 
                 << " ] " << endl;
            print(t->left, level + 1);
            print(t->right, level + 1);
                         
        }
    }
    
    

//    void printRange( const vector<Comparable> & low,
//                     const vector<Comparable> & high,
//                     KdNode *t, int level ) const
//    {
//        if( t != NULL )
//        {
//            if( low[ 0 ] <= t->data[ 0 ] && high[ 0 ] >= t->data[ 0 ] && 
//                low[ 1 ] <= t->data[ 1 ] && high[ 1 ] >= t->data[ 1 ] )
//                cout << "(" << t->data[ 0 ] << "," 
//                            << t->data[ 1 ] << ")" << endl;

//            if( low[ level ] <= t->data[ level ] )
//                printRange( low, high, t->left, 1 - level );
//            if( high[ level ] >= t->data[ level ] )
//                printRange( low, high, t->right, 1 - level );
//        }
//    }
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

    while (getline(inFile, fileLine))
    {
        iss.clear();
        iss.str(fileLine);
        iss >> tmpPoint.id >> tmpPoint.coord[0] >> tmpPoint.coord[1];
        points.push_back(tmpPoint);
    }

    return true;
}

int main(int argc, char *argv[])
{
    vector<Point> points;
    KdTree t;
    Point nn;

    if (argc != 2 || !readInput(argv[1], points))
    {
        return 1;
    }

#ifdef DEBUG
    cout << "Points:\n";
    for (size_t i = 0; i < points.size(); i++)
    {
        cout << points[i].id << " " << points[i].coord[0] << " " << points[i].coord[1] << endl;
    }
#endif

    for (size_t i = 0; i < points.size(); i++)
    {
        t.insert(points[i]);
    }
    cout << "\n\n";
    t.print();
    
    cout << "Nearest points:\n";
    for (size_t i = 0; i < points.size(); i++)
    {
        nn = t.nearest(points[i]);
        
        cout << points[i].id << " " << points[i].coord[0] << " " << points[i].coord[1] << endl;
        cout << "neighbour: " << nn.id << " " << nn.coord[0] << " " << nn.coord[1] << endl;
    }
    
    
    return 0;
}
