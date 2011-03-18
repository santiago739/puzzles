#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm> 

#include <math.h>

using namespace std;

struct KdNode
{
    int id;
    int depth;
    double x;
    double y;
    
    KdNode* parent;
    KdNode* left;
    KdNode* right;

    KdNode()
      : left(NULL), right(NULL) { }
};

bool sortNodesByX(const KdNode & lhs, const KdNode & rhs) 
{
	return lhs.x < rhs.x;
}

bool sortNodesByY(const KdNode & lhs, const KdNode & rhs) 
{
	return lhs.y < rhs.y;
}

class KdTree
{
public:    
    KdTree() 
      : root(NULL) { }
    
    void addNode(KdNode n)
    {
        nodes.push_back(n);
    }
    
    vector<KdNode> getNodes() const
    {
        return nodes;
    }
    
    void build()
    {
        root = build(nodes.begin(), nodes.end());
    }
    
    void print()
    {
        print(root, 0);
    }
    
    KdNode* nearest(KdNode& x)
    {
        KdNode* n = x.parent;
        
        double min;
        KdNode better;
        
        min = distance(x, (*n));
        better = nearest((*root), min, x);
        
        return n;
    }
      
private:
    KdNode* root;
    vector<KdNode> nodes;
    
    KdNode* build(vector<KdNode>::iterator begin, vector<KdNode>::iterator end, 
                  int depth = 0, KdNode* parent = NULL)
    {
        if (end - begin == 0)
        {
//            cout << "end - begin: " << (end - begin) << endl;
//            cout << "depth: " << depth << endl;
//            cout << endl;
            return NULL;
        }
        
        if (depth % 2)
        {
            sort(begin, end, sortNodesByY);
        }
        else
        {
            sort(begin, end, sortNodesByX);
        }
        
//        cout << "Nodes:\n";
//        for (vector<KdNode>::iterator i = begin; i != end; ++i) 
//        {
//            cout << (*i).id << " " << (*i).x << " " << (*i).y << endl;
//        }
        
        int median = (end - begin) / 2;
        int offset = (begin - nodes.begin()) + median;
//        cout << "end - begin: " << (end - begin) << endl;
//        cout << "median: " << median << endl;
//        cout << "offset: " << offset << endl;
//        cout << "depth: " << depth << endl;
//        cout << "nodes[offset].id: " << nodes[offset].id;
//        cout << " nodes[offset].x: " << nodes[offset].x;
//        cout << " nodes[offset].y: " << nodes[offset].y << endl;
//        cout << endl;
        
        nodes[offset].depth = depth;
        nodes[offset].parent = parent;
        nodes[offset].left = build(begin, begin + median, depth + 1, &nodes[offset]);
        nodes[offset].right = build(begin + median + 1, end, depth + 1, &nodes[offset]);
        
        return &nodes[offset];
    }
    
    double distance(KdNode& n1, KdNode& n2)
    {
        return sqrt( pow((n2.x - n1.x), 2) + pow((n2.y - n1.y), 2) );
    }
    
    double distancePerpendicular(KdNode& n1, KdNode& n2)
    {
        
        return sqrt( pow((n2.x - n1.x), 2) + pow((n2.y - n1.y), 2) );
    }
    
    KdNode nearest(KdNode& node, double min, KdNode& x)
    {
        double d, dp;
        KdNode result;
        
        d = distance(x, node);
        if (d < min)
        {
            result = node;
            min = d;
        }
        dp - distancePerpendicular(x, node);
        
        return result;
    }
    
    void print(KdNode *n, int level, char side = 'c')
    {
        if (n == NULL)
        {
            return;
        }
        else 
        {
            string where;
            
            where = (side == 'l') ? "LEFT" : ((side == 'r') ? "RIGHT" : "");
            cout << showbase << setw(level * 5) << "[ "
                 << where
                 << " ID: " << n->id 
                 << " X: " << n->x << " Y: " << n->y 
                 << " ] " << endl;
                 
            print(n->left, level + 1, 'l');
            print(n->right, level + 1, 'r');
        }
    }
};

bool readInput(const char* fileName, KdTree& t)
{
    ifstream inFile(fileName);
    istringstream iss;
    string fileLine;
    KdNode tmpNode;

    if (!inFile)
    {
        cerr << "Cannot open " << fileName << endl;
        return false;
    }

    while (getline(inFile, fileLine))
    {
        iss.clear();
        iss.str(fileLine);
        iss >> tmpNode.id >> tmpNode.x >> tmpNode.y;
        t.addNode(tmpNode);
    }

    return true;
}

int main(int argc, char *argv[])
{
//    vector<KdNode> nodes;
    KdTree t;
    //Point nn;

    if (argc != 2 || !readInput(argv[1], t))
    {
        return 1;
    }

#ifdef DEBUG
//    vector<KdNode> nodes;
//    cout << "Nodes:\n";
//    nodes = t.getNodes();
//    for (size_t i = 0; i < nodes.size(); i++)
//    {
//        cout << nodes[i].id << " " << nodes[i].x << " " << nodes[i].y << endl;
//    }
#endif

    t.build();
    t.print();

    vector<KdNode> nodes;
    nodes = t.getNodes();

    
    KdNode x = nodes[0];
//    KdNode* n = t.nearest(x);
    
//    cout << "Nearest points:\n";
//    cout << "point: ID=" << x.id << " X=" << x.x << " Y=" << x.y << endl;
//    cout << "nearest: ID=" << n->id << " X=" << n->x << " Y=" << n->y << endl;



//    for (size_t i = 0; i < points.size(); i++)
//    {
//        t.insert(points[i]);
//    }
//    cout << "\n\n";
//    t.print();
    
//    cout << "Nearest points:\n";
//    for (size_t i = 0; i < points.size(); i++)
//    {
//        nn = t.nearest(points[i]);
        
//        cout << points[i].id << " " << points[i].coord[0] << " " << points[i].coord[1] << endl;
//        cout << "neighbour: " << nn.id << " " << nn.coord[0] << " " << nn.coord[1] << endl;
//    }
    
    
    return 0;
}
