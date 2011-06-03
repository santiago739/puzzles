#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

#include "graph.h"

bool readInput( const char *fname, Graph& g )
{
    FILE *fp;
    int r;
    //char date[255], node1[80], node2[80];
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


int main( int argc, char *argv[] )
{
    Graph g;
    vset setR, setP, setX;
    vector<vset> cliques;


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
    
    return 0;
}

