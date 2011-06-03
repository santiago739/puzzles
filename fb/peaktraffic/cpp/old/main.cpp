#include <fstream>
#include <sstream>
#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <map>
#include <algorithm>
#include <ctime>

using namespace std;

struct Vertex;

typedef map<string, Vertex*, less<string> > vmap;
typedef set<Vertex*> vset;

struct Vertex
{
    string        name;
    vset          neighbours;

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
    const vset& getVertexSet( );
    void makeNotOriented( );

private:
    vmap vertexMap;
    vset vertexSet;
    
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

const vset& Graph::getVertexSet( )
{
    return vertexSet;
}

void Graph::addEdge( const string& sourceName, const string& destName )
{
    Vertex* v = getVertex( sourceName );
    Vertex* w = getVertex( destName );
    v->neighbours.insert( w );
}

Vertex* Graph::getVertex( const string& vertexName )
{
    vmap::iterator i = vertexMap.find( vertexName );

    if ( i == vertexMap.end( ) )
    {
        Vertex* newv = new Vertex( vertexName );
        vertexMap[ vertexName ] = newv;
        vertexSet.insert( newv );
        return newv;
    }

    return ( *i ).second;
}

void Graph::makeNotOriented( )
{
    for ( vmap::iterator i = vertexMap.begin( ); i != vertexMap.end( ); ++i )
    {
        vset::const_iterator j;
        for ( j = ( *i ).second->neighbours.begin(); j != ( *i ).second->neighbours.end(); ++j )
        {
            //cout << ( *j )->name << " ";
            vmap::iterator k = vertexMap.find( ( *j )->name );
            if ( k == vertexMap.end() )
            {
                ( *i ).second->neighbours.erase( j );
            }
        }
    }
}

void Graph::printGraph( )
{
    cout << "=== Graph ===" << "\n";
    for ( vmap::iterator i = vertexMap.begin( ); i != vertexMap.end( ); ++i )
    {
        cout << "Vertex: " << ( *i ).first << " ";
        cout << "Edges: ";
        vset::const_iterator j;
        
        for ( j = ( *i ).second->neighbours.begin(); j != ( *i ).second->neighbours.end(); ++j )
        {
            cout << ( *j )->name << " ";
        }
        cout << "\n";
    }
}

Graph::~Graph( )
{
    for ( vmap::iterator i = vertexMap.begin( ); i != vertexMap.end( ); ++i )
    {
        delete( *i ).second;
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

void printAsciiString( const string& s )
{
    for ( int i = 0; i < int( s.size() ); i++ )
    {
        cout << int( s[i] ) << " ";
    }
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
        fileLine.erase( remove( fileLine.begin(), fileLine.end(), '\n'), fileLine.end() );
        fileLine.erase( remove( fileLine.begin(), fileLine.end(), '\r'), fileLine.end() );
        
        tokens = split( fileLine, '\t' );

//         cout << tokens[1] << " " << tokens[2] << "\n";
        if ( tokens[1] == tokens[2] )
        {
            continue;
        }
//         cout << "\"" << tokens[1] << "\"" << " " << "\"" << tokens[2] << "\"" << endl;
//         cout << tokens[1].size() << " " << tokens[2].size() << endl;
//         cout << "s1: ";
//         printAsciiString(tokens[1]);
//         cout << " s2: ";
//         printAsciiString(tokens[2]);
//         cout << endl;
        
        g.addEdge( tokens[1], tokens[2] );
    } 
    
    return true;
}

void printSet( const vset& s )
{
//     cout << "{ ";
    for ( vset::iterator i = s.begin( ); i != s.end( ); i++ )
    {
        cout << ( *i )->name << " ";
    }
//     cout << "}" << endl;
}


void bronKerboschOne( vset setR, vset setP, vset setX, vector<vset>& cliques, int level = 0 )
{
    vset setNewR, setNewP, setNewX, setTmpP, neighbours;
    vset::iterator k;
    
    int j = level;
    while ( j > 0 )
    {
        cout << "  ";
        j--;
    }
    cout << "=== bronKerboschOne( ";
    printSet( setR );
    cout << ", ";
    printSet( setP );
    cout << ", ";
    printSet( setX );
    cout << " ) ===" << "\n";
    
//     printSet( setP );
    
    if ( setP.size() == 0 && setX.size() == 0 )
    {
//         cout << "Maximal clique: ";
//         printSet( setR );
//         cout << "\n";
        cliques.push_back(setR);
        return;
    }
    
    setTmpP = setP;
    for ( vset::iterator i = setTmpP.begin( ); i != setTmpP.end( ); i++ )
    {
        neighbours = ( *i )->neighbours;
        
//         cout << "=== Vertex ===" << "\n";
//         cout <<  ( *i )->name << "\n";
//         cout << "=== Neighbours ===" << "\n";
//         printSet( neighbours );
//         cout << "\n";
        
        //setNewR.clear();
        setNewR = setR;
        setNewR.insert( *i );
        
//         cout << "=== setNewR ===" << "\n";
//         printSet( setNewR );
        
        setNewP.clear();
        set_intersection( setP.begin(), setP.end(), 
                          neighbours.begin(), neighbours.end(), 
                          inserter( setNewP, setNewP.begin() ) );
        
        setNewX.clear();
        set_intersection( setX.begin(), setX.end(), 
                          neighbours.begin(), neighbours.end(), 
                          inserter( setNewX, setNewX.begin() ) );
        
//         cout << "=== setNewP ===" << "\n";
//         printSet( setNewP );
//         cout << "=== setNewX ===" << "\n";
//         printSet( setNewX );
//         cout << "\n";
        
//         r.insert( *itr );
//         n.insert( ( *itr ).adj.be )
        
        bronKerboschOne( setNewR, setNewP, setNewX, cliques, level + 1 );
        
        setX.insert( *i );
        setP.erase( *i );
    }
}

Vertex* getPivotOne( const vset& setP )
{
    if ( setP.size() > 0 )
    {
        vset::iterator i = setP.begin();
        return ( *i );
    }
    else
    {
        return NULL;
    }
}

Vertex* getPivotTwo( const vset& setP )
{
    Vertex* pivot = NULL;
    
    if ( setP.size() > 0 )
    {
        size_t n = 0;
        
        for ( vset::iterator i = setP.begin( ); i != setP.end( ); i++ )
        {
            if ( (*i)->neighbours.size() > n )
            {
                n = (*i)->neighbours.size();
                pivot = *i;
            }
        }
    }
    return pivot;
}

void bronKerboschTwo( vset setR, vset setP, vset setX, vector<vset>& cliques, int level = 0 )
{
    vset setNewR, setNewP, setNewX, setTmpP, neighboursV, neighboursU;
    vset::iterator k;
    Vertex* pivot;
    
    
//     int j = level;
//     while ( j > 0 )
//     {
//         cout << "  ";
//         j--;
//     }
//     cout << "=== bronKerboschTwo( ";
//     printSet( setR );
//     cout << ", ";
//     printSet( setP );
//     cout << ", ";
//     printSet( setX );
//     cout << " ) ===" << "\n";
    
//     printSet( setP );
    
    if ( setP.size() == 0 && setX.size() == 0 )
    {
        cliques.push_back(setR);
        return;
    }
    
    set_union( setP.begin(), setP.end(), setX.begin(), setX.end(), 
               inserter( setNewP, setNewP.begin() ) );
    
//     pivot = getPivotOne( setNewP );
    pivot = getPivotTwo( setNewP );
    
    if ( pivot != NULL )
    {
//         cout << "Pivot: " << pivot->name << "\n";
        neighboursU = pivot->neighbours;
        set_difference( setP.begin(), setP.end(), 
                        neighboursU.begin(), neighboursU.end(), 
                        inserter( setTmpP, setTmpP.begin() ) );
    }
    else
    {
        setTmpP = setP;
    }
    
        
    for ( vset::iterator i = setTmpP.begin( ); i != setTmpP.end( ); i++ )
    {
        neighboursV = ( *i )->neighbours;
        
//         cout << "=== Vertex ===" << "\n";
//         cout <<  ( *i )->name << "\n";
//         cout << "=== Neighbours ===" << "\n";
//         printSet( neighbours );
//         cout << "\n";
        
        //setNewR.clear();
        setNewR = setR;
        setNewR.insert( *i );
        
//         cout << "=== setNewR ===" << "\n";
//         printSet( setNewR );
        
        setNewP.clear();
        set_intersection( setP.begin(), setP.end(), 
                          neighboursV.begin(), neighboursV.end(), 
                          inserter( setNewP, setNewP.begin() ) );
        
        setNewX.clear();
        set_intersection( setX.begin(), setX.end(), 
                          neighboursV.begin(), neighboursV.end(), 
                          inserter( setNewX, setNewX.begin() ) );
        
//         cout << "=== setNewP ===" << "\n";
//         printSet( setNewP );
//         cout << "=== setNewX ===" << "\n";
//         printSet( setNewX );
//         cout << "\n";
        
//         r.insert( *itr );
//         n.insert( ( *itr ).adj.be )
        
        bronKerboschTwo( setNewR, setNewP, setNewX, cliques, level + 1 );
        
        setX.insert( *i );
        setP.erase( *i );
    }
}

int main( int argc, char* argv[] )
{
    Graph g;
    vset setR, setP, setX;
    vector<vset> cliques;

    if ( argc != 2 || !readInput( argv[1], g ) )
    {
        return 1;
    }
    
    g.makeNotOriented();
//     g.printGraph( );
    setP = g.getVertexSet( );
    
//     bronKerboschOne( setR, setP, setX, cliques );
    bronKerboschTwo( setR, setP, setX, cliques );
    
//     cout << "=== Maximal cliques ===\n";
    for ( vector<vset>::iterator i = cliques.begin( ); i != cliques.end( ); i++ )
    {
        printSet( *i );
        cout << "\n";
    }
    
    return 0;
}
