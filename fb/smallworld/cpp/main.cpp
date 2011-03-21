#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm> 

#include <math.h>

using namespace std;

struct Point
{
    int id;
    double x;
    double y;
};

struct KdNode
{
//    int depth;
    Point point;
    
//    KdNode* parent;
    KdNode* left;
    KdNode* right;

    KdNode(Point p)
      : left(NULL), right(NULL) 
    { 
        point.id = p.id;
        point.x = p.x;
        point.y = p.y;
    }
};

bool sortNodesByX(const KdNode & lhs, const KdNode & rhs) 
{
	return lhs.point.x < rhs.point.x;
}

bool sortNodesByY(const KdNode & lhs, const KdNode & rhs) 
{
	return lhs.point.y < rhs.point.y;
}

class KdTree
{
public:
    KdNode* root;
    
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
    
//    KdNode* nearest(KdNode& target)
//    {
//        if (root == NULL)
//        {
//            return NULL;
//        }
        
//        // find parent node to which target would have been inserted. This is our
//        // best shot at locating closest point; compute best distance guess so far
//        KdNode* parent = target.parent;
        
//        double smallest = distance(x, (*n));
//        KdNode better;
        
//        min = 
//        better = nearest((*root), min, x);
        
//        return n;
//    }

    Point nearest(KdNode* node, Point& point, Point min, int depth = 0)
    {
        if (node != NULL)
        {
            double d;
            int axis = depth % 2;
            
            if (axis == 0)
                d = point.x - node->point.x;
            else
                d = point.y - node->point.y;
                
            KdNode* near = (d <= 0) ? node->left : node->right;
            KdNode* far  = (d <= 0) ? node->right : node->left;
            
            min = nearest(near, point, min, depth + 1);
            
            if ((d * d) < distance(point, min))
            {
                min = nearest(far, point, min, depth + 1);
            }
            
            if (distance(point, node->point) < distance(point, min))
            {
                min = node->point;
            }
        }
        return min;
    }
      
private:
    
    vector<KdNode> nodes;
    
    KdNode* build(vector<KdNode>::iterator begin, vector<KdNode>::iterator end, 
                  int depth = 0, KdNode* parent = NULL)
    {
        if (end - begin == 0)
        {
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
        
//        nodes[offset].depth = depth;
//        nodes[offset].parent = parent;
        nodes[offset].left = build(begin, begin + median, depth + 1, &nodes[offset]);
        nodes[offset].right = build(begin + median + 1, end, depth + 1, &nodes[offset]);
        
        return &nodes[offset];
    }

    double distance(Point& n1, Point& n2)
    {
        return pow((n2.x - n1.x), 2) + pow((n2.y - n1.y), 2);
    }
    
//    double distance(KdNode& n1, KdNode& n2)
//    {
//        return sqrt( pow((n2.x - n1.x), 2) + pow((n2.y - n1.y), 2) );
//    }
    
//    double distancePerpendicular(KdNode& n1, KdNode& n2)
//    {
//        double d;
        
//        if (n1.depth % 2)
//        {
//            d = n1.x - n2.x;
//        }
//        else
//        {
//            d = n1.y - n2.y;
//        }
        
//        return fabs(d);
//    }
    
//    KdNode nearest(KdNode& node, double min, KdNode& x)
//    {
//        double d, dp, dpt;
//        KdNode result, pt;
        
//        d = distance(x, node);
//        if (d < min)
//        {
//            result = node;
//            min = d;
//        }
//        dp = distancePerpendicular(x, node);
        
//        if (dp < min)
//        {
//            pt = nearest(node.parent, min, x);
//            dpt = distance(pt, x);
//            if (dpt < min)
//            {
//                result = pt;
//                min = dpt;
//            }
//        }
//        else
//        {
//            if (node.depth < x.depth)
//            {
//                pt = nearest(node.parent, min, x);
//            }
//            else
//            {
                
//            }
            
            
//        }
        
//        return result;
//    }
    
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
                 << " ID: " << n->point.id 
                 << " X: " << n->point.x << " Y: " << n->point.y 
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
    Point tmp;

    if (!inFile)
    {
        cerr << "Cannot open " << fileName << endl;
        return false;
    }

    while (getline(inFile, fileLine))
    {
        iss.clear();
        iss.str(fileLine);
        iss >> tmp.id >> tmp.x >> tmp.y;
        KdNode node(tmp);
        t.addNode(node);
    }

    return true;
}

int main(int argc, char *argv[])
{
    KdTree t;

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
    
    Point s = {0, 6, 5};
    Point nn = t.nearest(t.root, s, t.root->point, 0);
    
    cout << "nearest: ID=" << nn.id << " X=" << nn.x << " Y=" << nn.y << endl;

    //vector<KdNode> nodes;
    //nodes = t.getNodes();

    
    //KdNode x = nodes[0];
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
