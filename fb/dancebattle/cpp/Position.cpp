/*
 * Position.cpp
 *
 *  Created on: Jan 19, 2011
 *      Author: santiago
 */

#include "Position.h"

// Comparison operator, guarantees a total order.
bool Position::operator<(const Position & rhs) const
{
    int nRows = rhs.board_.getRowsNumber();
//    int nRows = 3;

    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nRows; j++)
            if (board_[i][j] != rhs.board_[i][j])
                return board_[i][j] < rhs.board_[i][j];

    return false;
}
