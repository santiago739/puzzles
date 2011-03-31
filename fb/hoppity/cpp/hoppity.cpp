/* http://www.facebook.com/careers/puzzles.php?puzzle_id=7 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

int main( int argc, char * argv[ ] )
{
    string line;
    int value = 0;
    ifstream inFile;
    
    if( argc != 2 )
    {
        exit( EXIT_FAILURE );
    }

    inFile.open( argv[ 1 ], ifstream::in );
    if( inFile.is_open( ) )
    {
        getline( inFile, line );
        value = atoi( line.c_str( ) );
//        cout << line << endl;
//        cout << value << endl;
    }
    inFile.close( );
    
    for( int i = 1; i <= value; i++)
    {
        if( ( i % 3 == 0 ) && ( i % 5 == 0 ) )
        {
            cout << "Hop" << endl;
        }
        else if( i % 3 == 0 )
        {
            cout << "Hoppity" << endl;
        }
        else if( i % 5 == 0 )
        {
            cout << "Hophop" << endl;
        }
    }
    
    exit( EXIT_SUCCESS );
}
