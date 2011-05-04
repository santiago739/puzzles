#include <fstream>
#include <sstream>
#include <iostream>
#include <list>
#include <set>
#include <vector>
#include <iterator>
#include <map>

using namespace std;

struct Vertex;

typedef map<string, Vertex*, less<string> > vmap;

struct Edge
{
    Vertex* dest;   // Second vertex in edge

    Edge( Vertex* d = 0 )
        : dest( d ) { }
};

struct Vertex
{
    string        name;    // Vertex name
    vector<Edge>  adj;     // Adjacent vertices (and costs)

    Vertex( const string& nm ) 
        : name( nm ) { }
};

class Graph
{
public:
    Graph( ) { }
    ~Graph( );
    
    void addEdge( const string& sourceName, const string& destName );
    void printGraph( );
    const vmap& getVertexMap( );

private:
    vmap vertexMap;
    
    Vertex* getVertex( const string& vertexName );
    
    // Copy semantics are disabled; these make no sense.
    Graph( const Graph & rhs ) { }
    const Graph & operator= ( const Graph & rhs )
      { return *this; }

};

const vmap& Graph::getVertexMap( )
{
    return vertexMap;
}

void Graph::addEdge( const string& sourceName, const string& destName )
{
    Vertex* v = getVertex( sourceName );
    Vertex* w = getVertex( destName );
    v->adj.push_back( Edge( w ) );
}

Vertex* Graph::getVertex( const string& vertexName )
{
    vmap::iterator itr = vertexMap.find( vertexName );

    if ( itr == vertexMap.end( ) )
    {
        Vertex* newv = new Vertex( vertexName );
        vertexMap[ vertexName ] = newv;
        return newv;
    }

    return ( *itr ).second;
}

void Graph::printGraph( )
{
    cout << "=== Graph ===" << "\n";
    for ( vmap::iterator itr = vertexMap.begin( ); itr != vertexMap.end( ); ++itr )
    {
        cout << "Vertex: " << ( *itr ).first << " ";
        cout << "Edges: ";
        vector<Edge>::const_iterator adjItr = ( *itr ).second->adj.begin();
        
        for ( adjItr = ( *itr ).second->adj.begin(); adjItr != ( *itr ).second->adj.end(); ++adjItr )
        {
            cout << ( *adjItr ).dest->name << " ";
        }
        cout << "\n";
    }
}

Graph::~Graph( )
{
    for ( vmap::iterator itr = vertexMap.begin( ); itr != vertexMap.end( ); ++itr )
    {
        delete( *itr ).second;
    }
}

vector<string> & split( const string& s, char delim, vector<string>& elems )
{
    stringstream ss( s );
    string item;

    while ( getline( ss, item, delim ) )
    {
        elems.push_back( item );
    }

    return elems;
}

vector<string> split( const string& s, char delim )
{
    vector<string> elems;
    return split( s, delim, elems );
}

bool readInput( const char* fileName, Graph& g )
{
    ifstream inFile( fileName );
    string fileLine;
    vector<string> tokens;

    if ( !inFile )
    {
        cerr << "Cannot open " << fileName << endl;
        return false;
    }

    while ( getline( inFile, fileLine ) )
    {
        tokens = split( fileLine, '\t' );

        cout << tokens[1] << " " << tokens[2] << "\n";
        g.addEdge( tokens[1], tokens[2] );
    } 
    
    return true;
}

void bronKerbosch1( vmap r, vmap p, vmap x )
{
    if ( p.size() == 0 && x.size() == 0 )
    {
        cout << "Maximal clique" << "\n";
        return;
    }
    for ( vmap::iterator itr = p.begin( ); itr != p.end( ); ++itr )
    {
        r.insert( *itr );
        
//         bronKerbosch1( r );
    }
}

int main( int argc, char* argv[] )
{
    Graph g;
    vmap r, p, x;

    if ( argc != 2 || !readInput( argv[1], g ) )
    {
        return 1;
    }

    g.printGraph( );

    p = g.getVertexMap( );

    bronKerbosch1( r, p, x );

    return 0;
}
