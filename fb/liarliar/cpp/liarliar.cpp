#include <limits.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include <string>
#include <map>
#include <vector>
#include <queue>
#include <functional>
#include <list>
#include <typeinfo>

#include "Except.h"

using namespace std;

static const int INFINITY = INT_MAX;

struct Vertex;

// Basic item stored in adjacency list.
struct Edge
{
                     // First vertex in edge is implicit
    Vertex  *dest;   // Second vertex in edge

    Edge( Vertex *d = 0 )
      : dest( d ) { }
};

// Basic info for each vertex.
struct Vertex
{
    string        name;    // Vertex name
    vector<Edge>  adj;     // Adjacent vertices (and costs)
    double        dist;    // Cost
    Vertex       *prev;    // Previous vertex on shortest path
    int           color;   // Color of vertex

    Vertex( const string & nm ) : name( nm )
      { reset( ); }

    void reset( )
      { dist = INFINITY; prev = NULL; color = 0; }
};

class Graph
{
  public:
    Graph( ) { }
    ~Graph( );
    void addEdge( const string & sourceName, const string & destName );
    void doBFS( const string & startName );
    void doTwoColor( );
      
  private:
    Vertex * getVertex( const string & vertexName );
    void print( );

    typedef map<string,Vertex *,less<string> > vmap;

      // Copy semantics are disabled; these make no sense.
    Graph( const Graph & rhs ) { }
    const Graph & operator= ( const Graph & rhs )
      { return *this; }

    vmap vertexMap;
};

// Add a new edge to the graph.
void Graph::addEdge( const string & sourceName, const string & destName )
{
    Vertex * v = getVertex( sourceName );
    Vertex * w = getVertex( destName );
    v->adj.push_back( Edge( w ) );
}

// If vertexName is not present, add it to vertexMap.
// In either case, return (a pointer to) the Vertex.
Vertex * Graph::getVertex( const string & vertexName )
{
    vmap::iterator itr = vertexMap.find( vertexName );

    if( itr == vertexMap.end( ) )
    {
        Vertex *newv = new Vertex( vertexName );
        vertexMap[ vertexName ] = newv;
        return newv;
    }
    return (*itr).second;
}

// Single-source unweighted shortest-path algorithm.
void Graph::doBFS( const string & startName )
{
    vmap::iterator itr = vertexMap.find( startName );

    if( itr == vertexMap.end( ) )
    {
        throw GraphException( startName + " is not a vertex in this graph" );
    }

    Vertex *start = (*itr).second;
    list<Vertex *> q;
    q.push_back( start ); 
    start->dist = 0;
    start->color = 1;

    while( !q.empty( ) )
    {
        Vertex *v = q.front( ); 
        q.pop_front( );

        for( unsigned int i = 0; i < v->adj.size( ); i++ )
        {
            Edge e = v->adj[ i ];
            Vertex *w = e.dest;
            w->color = ( v->color == 1 ) ? 2 : 1;

            if( w->dist == INFINITY )
            {
                w->dist = v->dist + 1;
                w->prev = v;
                
                q.push_back( w );
            }

            if( v->color == w->color )
            {
                cerr << "Not bipartite graph" << ", v: " << v->name;
                //cerr << ", w: " << w->name << ", color: " << v->color << endl;
                //cerr << "Graph:" << endl;
                //print( );
            }
        }
    }
}

void Graph::print( )
{
    for( vmap::iterator itr = vertexMap.begin( ); itr != vertexMap.end( ); ++itr )
    {
        Vertex *v = (*itr).second;
        cerr << "v: " << v->name << ", color: " << v->color << endl;
    }
}

// Two-coloring
void Graph::doTwoColor( )
{
    int x( 0 ), y( 0 ), z( 0 );
    
    for( vmap::iterator itr = vertexMap.begin( ); itr != vertexMap.end( ); ++itr )
    {
        if( (*itr).second->dist == INFINITY )
        {
            doBFS( (*itr).second->name );
        }
    }
    
    for( vmap::iterator itr = vertexMap.begin( ); itr != vertexMap.end( ); ++itr )
    {
        if( (*itr).second->color == 1 )
        {
            x++;
        }
        if( (*itr).second->color == 2 )
        {
            y++;
        }
    }
    z = x;
    x = (x > y) ? x : y;
    y = (y < x) ? y : x;
    cout << x << ' ' << y << endl;
}

// Destructor: cleans up the Vertex structs.
Graph::~Graph( )
{
    for( vmap::iterator itr = vertexMap.begin( ); itr != vertexMap.end( ); ++itr )
        delete (*itr).second;
}

// Process a request; return false if end of file.
bool processRequest( Graph & g )
{
    try
    {
        g.doTwoColor( );
    }
    catch( const GraphException & e )
    {
        cerr << e.toString( ) << endl;
    }
    return true;
}

bool readGraph( const char * fileName, Graph & g )
{
    ifstream inFile( fileName );
    if( !inFile )
    {
        cerr << "Cannot open " << fileName << endl;
        return false;
    }

    //cout << "Reading file... " << endl;

    string oneLine;
    istringstream iss;
    string source, dest;
    int totalEdges = 0;
    int totalAccused = 0;
    
    if( !getline( inFile, oneLine ).eof( ) )
    {
        iss.str( oneLine );
        iss >> totalEdges;
        
        if( iss.fail( ) )
        {
            cerr << "Bad line: " << oneLine << endl;
            return false;
        }
//        else
//        {            
//            cout << totalEdges << endl;
//        }
    }
    
    for( int i = 0; i < totalEdges && !getline( inFile, oneLine ).eof( ); i++ )
    {
        iss.clear( );
        iss.str( oneLine );
        iss >> source >> totalAccused;
        
        if( iss.fail( ) )
        {
            cerr << "Bad line: " << oneLine << endl;
            return false;
        }
        else
        {
            //cout << source << " " << totalAccused << endl;
            
            for( int j = 0; j < totalAccused && !getline( inFile, oneLine ).eof( ); j++ )
            {
                iss.clear( );
                iss.str( oneLine );
                iss >> dest;
                
                if( iss.fail( ) )
                {
                    cerr << "Bad line: " << oneLine << endl;
                    return false;
                }
                else
                {
                    g.addEdge( source, dest );
                    //cout << dest << endl;
                }
            }
        }
    }
    
    //cout << "File read" << endl << endl;
    
    return true;
}

int main( int argc, char *argv[ ] )
{
    Graph g;

    if( argc != 2 )
    {
        cerr << "Usage: " << argv[ 0 ] << " graphfile" << endl;
        return 1;
    }

    if( !readGraph( argv[ 1 ], g ) )
    {
        return 1;
    }
    
    processRequest( g );
    
    return 0;
}
