#include <fstream>
#include <sstream>

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>


#include "graph.h"

void printSet( const vset& s )
{
    vset::iterator i, j;
    
    cout << "{ ";
    for ( i = s.begin( ); i != s.end( ); ++i )
    {
        cout << ( *i )->name;
        j = i;
        ++j;
        if ( j != s.end( ) )
        {
            cout << ", ";
        }
    }
    cout << " }";
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

bool _readInput( const char *fname, Graph& g )
{
    FILE *fp;
    int r;
    char tokens[3][80];
    string node1, node2;
    
    fp = fopen( fname, "r" );
    if ( fp == NULL )
    {
        return false;
    }
    
    while ( !feof( fp ) )
    {
        r = fscanf( fp, "%[^\t]\t%[^\t]\t%[^\n]\n", tokens[0], tokens[1], tokens[2] );
#ifdef DEBUG
		printf( "date: %s, node1: %s, node2: %s\n", tokens[0], tokens[1], tokens[2] );
#endif
        string node1( tokens[1] ), node2( tokens[2] );
        
        if ( node1 == node2 )
        {
            continue;
        }
        
		g.addEdge( node1, node2 );

    }
    
    return true;
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

bool compVSet ( const Vertex* lhs, const Vertex* rhs )
{
    return lhs->name < rhs->name ;
}

string getSetAsString( vset& s )
{
    vset::iterator k;
    string result;
    vector<string> v;
    vector<string>::iterator i, j;
    
//    sort( s.begin( ), s.end( ), compVSet );

    for ( k = s.begin( ); k != s.end( ); ++k )
    {
        v.push_back( ( *k )->name );
    }
    sort( v.begin( ), v.end( ) );
    
    for ( i = v.begin( ); i != v.end( ); ++i )
    {
        result += *i;
        
//        std::cout << ( *i )->name;
        j = i; ++j;
        
        if ( j != v.end( ) )
        {
            result += ", ";
        }
    }
    return result;
}

void bronKerboschTwo( vset setR, vset setP, vset setX, vector<string>& cliques, int level = 0 )
{
    vset setNewR, setNewP, setNewX, setTmpP, neighboursV, neighboursU;
    vset::iterator k;
    Vertex* pivot;
    
    
//    int j = level;
//    while ( j > 0 )
//    {
//        cout << "  ";
//        j--;
//    }
//    cout << "=== bronKerboschTwo( ";
//    printSet( setR );
//    cout << ", ";
//    printSet( setP );
//    cout << ", ";
//    printSet( setX );
//    cout << " ) ===" << "\n";

//    printSet( setP );
    
    if ( ( setP.size() == 0 ) && ( setX.size() == 0 ) && ( setR.size() > 2 ) )
    {
//        cliques.push_back(setR);
        cliques.push_back( getSetAsString( setR ) );

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


int main( int argc, char *argv[] )
{
    Graph g;
    vset setR, setP, setX;
//    vector<vset> cliques;
    vector<string> cliques;


    if ( argc != 2 ) 
    {
        fprintf( stderr, "Usage: %s filename\n", argv[0] );
        exit( EXIT_FAILURE );
    }
    
    if ( !readInput( argv[1], g ) ) 
    {
        fprintf( stderr, "Can't open file %s\n", argv[1] );
        exit( EXIT_FAILURE );
    }
    
    g.makeNotOriented();
    setP = g.getVertexSet();
    
    bronKerboschTwo( setR, setP, setX, cliques );
    
    sort( cliques.begin( ), cliques.end( ) );
    for ( vector<string>::iterator i = cliques.begin( ); i != cliques.end( ); i++ )
    {
        //printSet( *i );
        cout << *i <<  "\n";
    }
    
    return 0;
}

