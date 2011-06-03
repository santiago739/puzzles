#include <iostream>
#include "graph.h"

using namespace std;

Graph::Graph() { }

Graph::~Graph()
{
    for ( vmap::iterator i = vertexMap.begin( ); i != vertexMap.end( ); ++i )
    {
        delete( *i ).second;
    }
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


void Graph::addEdge( const string& sourceName, const string& destName )
{
    Vertex* v = getVertex( sourceName );
    Vertex* w = getVertex( destName );
    v->neighbours.insert( w );
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

void Graph::printGraph()
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

const vset& Graph::getVertexSet( )
{
    return vertexSet;
}


