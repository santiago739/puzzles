#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm> 
#include <limits>

#include <math.h>

using namespace std;

struct Point
{
    int id;
    double x;
    double y;
};

struct Minimum
{
    Point point;
    double distance;
};

struct KdNode
{
    Point point;
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
    KdTree() 
      : root(NULL) { }
    
    void addNode(KdNode n)
    {
        nodes.push_back(n);
        nodesOriginal.push_back(n);
    }
    
    KdNode* getRoot() const
    {
        return root;
    }
    
    vector<KdNode>& getNodes()
    {
        return nodesOriginal;
    }
    
    void build()
    {
        root = build(nodes.begin(), nodes.end());
    }
    
    void print()
    {
        print(root, 0);
    }
    
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
    
    double nearestKPoints(KdNode* node, Point& point, unsigned int k, 
                     vector<Minimum>& min, double kDistance, int depth = 0)
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
            
            kDistance = nearestKPoints(near, point, k, min, kDistance, depth + 1);
            
            if ((d * d) < kDistance)
            {
                kDistance = nearestKPoints(far, point, k, min, kDistance, depth + 1);
            }
            
            d = distance(point, node->point);
            
            if (d < kDistance)
            {
                int i, j, m;
                
                i = 0;
                j = min.size();
                while (i < j)
                {
                    m = (i + j) / 2;
                    if (min[m].distance < d)
                    {
                        i = m + 1;
                    }
                    else
                    {
                        j = m;
                    }
                }
                Minimum tmp;
                tmp.point = node->point;
                tmp.distance = d;
                
                vector<Minimum>::iterator it;
                it = min.begin() + i;
                min.insert(it, tmp);
                
                if (min.size() >= k)
                {
                    min.resize(k);
                    kDistance = min[min.size() - 1].distance;
                }
            }
        }
        return kDistance;
    }
      
private:
    
    KdNode* root;
    vector<KdNode> nodes;
    vector<KdNode> nodesOriginal;
    
    KdNode* build(vector<KdNode>::iterator begin, vector<KdNode>::iterator end, 
                  int depth = 0)
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
        
        int median = (end - begin) / 2;
        int offset = (begin - nodes.begin()) + median;
        
        nodes[offset].left = build(begin, begin + median, depth + 1);
        nodes[offset].right = build(begin + median + 1, end, depth + 1);
        
        return &nodes[offset];
    }

    double distance(Point& n1, Point& n2)
    {
        return pow((n2.x - n1.x), 2) + pow((n2.y - n1.y), 2);
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

    t.build();
//    t.print();
    
//    Point s = {0, 6, 5};
//    Point nn = t.nearest(root, s, root->point, 0);
//    cout << "nearest: ID=" << nn.id << " X=" << nn.x << " Y=" << nn.y << endl;
    
    KdNode* root = t.getRoot();
    vector<Minimum> min;
    vector<KdNode> nodes = t.getNodes();
    
    for (size_t i = 0; i < nodes.size(); i++)
    {
        min.clear();
        t.nearestKPoints(root, nodes[i].point, 4, min, numeric_limits<double>::max(), 0);
        
        cout << nodes[i].point.id << " ";
        for (size_t j = 1; j < min.size(); j++)
        {
            cout << min[j].point.id;
            if (j < min.size() - 1)
                cout << ",";
        }
        cout << endl;
    }
    
    return 0;
}
