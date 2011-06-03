#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <set>
#include <map>
#include <string>

using namespace std;

struct Vertex;

typedef map<string, Vertex*, less<string> > vmap;
typedef set<Vertex*> vset;

struct Vertex
{
    string  name;
    vset    neighbours;

    Vertex( const string& nm ) 
        : name( nm ) { }
};


class Graph
{
public:
    Graph();
    virtual ~Graph();
    
    void addEdge( const string& sourceName, const string& destName );
    void printGraph( );
    const vmap& getVertexMap( );
    const vset& getVertexSet( );
    void makeNotOriented( );

private:
    vmap vertexMap;
    vset vertexSet;
    
    Vertex* getVertex( const string& vertexName );
    
    // Copy semantics are disabled; these make no sense.
//    Graph( const Graph & rhs ) { }
//    const Graph & operator= ( const Graph & rhs )
//      { return *this; }

};

#endif /* __GRAPH_H__ */
