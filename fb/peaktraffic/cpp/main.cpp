#include <fstream>
#include <sstream>
#include <iostream>
#include <list>
#include <set>
//#include <algorithm> 


using namespace std;

list<set<int> > kerbosh(int **&a,int SIZE)
{
   set<int> M,G,K,P;
   list<set<int> > REZULT;
   for (int i=0; i<SIZE;i++)
   {
       K.insert(i);
   }
   int v,Count=0,cnt=0;
   int Stack1[100];
   std::set<int> Stack2[100];
   std::set<int>::iterator theIterator;
   theIterator=K.begin();
   while ((K.size()!=0)||(M.size()!=0))
   {
       if (K.size()!=0)
       {
           theIterator=K.begin();
           v=*theIterator;
           Stack2[++Count]=M;
           Stack2[++Count]=K;
           Stack2[++Count]=P;
           Stack1[++cnt]=v;
           M.insert(v);
           for (int i=0;i<SIZE;i++)
           {
               if (a[v][i])
               {
                   theIterator=K.find(i);
                   if (theIterator!=K.end())
                   {
                       K.erase(theIterator);
                   }
                   theIterator=P.find(i);
                   if (theIterator!=P.end())
                   {
                       P.erase(theIterator);
                   }
               }
           }
           theIterator=K.find(v);
           if (theIterator!=K.end())
           {
               K.erase(theIterator);
           }
       }
       else
       {
           if (P.size()==0)
           {
               REZULT.push_back(M);
           }
           v=Stack1[cnt--];
           P=Stack2[Count--];
           K=Stack2[Count--];
           M=Stack2[Count--];
           theIterator=K.find(v);
           if (theIterator!=K.end())
           {
               K.erase(theIterator);
           }
           P.insert(v);
       }
   }
   return  REZULT;
}


//bool readInput(const char* fileName, KdTree& t)
//{
//    ifstream inFile(fileName);
//    istringstream iss;
//    string fileLine;
//    Point tmp;

//    if (!inFile)
//    {
//        cerr << "Cannot open " << fileName << endl;
//        return false;
//    }

//    while (getline(inFile, fileLine))
//    {
//        iss.clear();
//        iss.str(fileLine);
//        iss >> tmp.id >> tmp.x >> tmp.y;
//        KdNode node(tmp);
//        t.addNode(node);
//    }

//    return true;
//}

int main(int argc, char *argv[])
{
    const int gSize = 2;
//    int graph[gSize][gSize] = {{1, 1},
//                               {1, 1}
//                              };

    int **g(new int*[gSize]);
    for (int row = 0; row != gSize; ++row)
    {
        g[row] = new int[gSize];
    }
    
//    for (int row = 0; row != gSize; ++row)
//    {
//        for (int col = 0; col != gSize; ++col)
//        {
//            g[row][col] = 1;
//        }
//    }
    
//    g[0][0] = 0;    g[0][1] = 0;    g[0][2] = 0;
//    g[1][0] = 1;    g[1][1] = 0;    g[1][2] = 0;
//    g[2][0] = 0;    g[2][1] = 0;    g[2][2] = 0;

    g[0][0] = 0;    g[0][1] = 0;    
    g[1][0] = 1;    g[1][1] = 0;    
    
    list<set<int> > cliques;
    list<set<int> >::iterator itList;
    set<int>::iterator itSet;
    
    cliques = kerbosh(g, gSize);
    
    cout << "cliques contains: " << endl;
    for (itList = cliques.begin(); itList != cliques.end(); itList++)
    {
        for (itSet = (*itList).begin(); itSet != (*itList).end(); itSet++)
        {
            cout << " " << *itSet;
        }
        cout << endl;
    }

    cout << endl;
    
                              
//    if (argc != 2 || !readInput(argv[1], t))
//    {
//        return 1;
//    }
    
    return 0;
}
