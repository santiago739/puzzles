/*
 * Position.h
 *
 *  Created on: Jan 19, 2011
 *      Author: santiago
 */

#ifndef POSITION_H_
#define POSITION_H_

#include "Matrix.h"

class Position
{
public:
    Position(int nMoves) :
        board_(nMoves, nMoves)
    {
    }

    Position(const Matrix<int> & rhs) :
        board_(rhs)
    {
    }

    bool operator<(const Position & rhs) const;

private:
    Matrix<int> board_;
};

#endif /* POSITION_H_ */
