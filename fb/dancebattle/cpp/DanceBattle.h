/*
 * DanceBattle.h
 *
 *  Created on: Jan 18, 2011
 *      Author: santiago
 */

#ifndef DANCEBATTLE_H_
#define DANCEBATTLE_H_

#include <map>
#include <vector>
#include <functional>

#include "Matrix.h"
#include "Position.h"

typedef std::map<Position, int, std::less<Position> > MapType;
typedef MapType::const_iterator MapItr;

static const int MIN_DEPTH = 3; // Min depth placed in Trans. table
static const int MAX_DEPTH = 6; // Max depth placed in Trans. table

class DanceBattle
{
public:
    enum Side
    {
        YOU, OPPONENT, EMPTY
    };

    enum PositionVal
    {
        YOU_WIN, UNCLEAR, OPPONENT_WIN
    };

    DanceBattle(int nMoves) :
        nMoves_(nMoves), board_(nMoves, nMoves)
    {
        clearBoard();
    }

    // Find optimal turn.
    int chooseTurn(Side d, int bestRow, int & bestColumn,
                    int alpha = YOU_WIN, int beta = OPPONENT_WIN,
                    int depth = 0);

    // Play turn, including checking legality
    bool playTurn(Side s, int row, int column);

    void clearBoard();

    bool hasTurn(int lastMove) const;

    const Matrix<int>& getBoard() const
    {
        return board_;
    }

    int getNumberMoves() const
    {
        return nMoves_;
    }

private:
    int nMoves_;
    Matrix<int> board_;
    MapType transpositions;

    // Play a turn, possibly clearing a square. No checks.
    void place(int row, int col, int piece = EMPTY)
    {
        board_[row][col] = piece;
        board_[col][row] = piece;
    }

    // Test if a square is empty.
    bool squareIsEmpty(int row, int col) const
    {
        if (board_[row][col] == EMPTY && board_[col][row] == EMPTY)
        {
            return true;
        }
        return false;
    }

    // Compute static value of position.
    int positionValue(Side s, int lastMove) const;
};

#endif /* DANCEBATTLE_H_ */
