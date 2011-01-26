#ifndef EXCEPT_H_
#define EXCEPT_H_

#include <string>
using namespace std;


class DSException
{
  public:
    DSException( const string & msg = "" ) : message( msg )
      { }
    virtual ~DSException( )
      { }
    virtual string toString( ) const
#ifndef NO_RTTI
      { return "Exception " + string( typeid( *this ).name( ) ) + ": " + what( ); }
#else
      { return "Exception " + string( ": " ) + what( ); }
#endif
    virtual string what( ) const
      { return message; }

  private:
    string message;
};

class GraphException : public DSException 
{
  public:
    GraphException( const string & msg = "" ) : DSException( msg )
      { }
};

#endif
