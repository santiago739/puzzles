/*
 * DanceBattle.cpp
 *
 *  Created on: Jan 18, 2011
 *      Author: santiago
 */

#include <iostream>

#include "DanceBattle.h"

using namespace std;

// Play a move. Return true if move is legal; return false otherwise.
bool DanceBattle::playTurn(Side s, int row, int col)
{
    if (board_[row][col] != EMPTY || board_[col][row] != EMPTY)
    {
        return false;
    }
    board_[row][col] = s;
    board_[col][row] = s;

    return true;
}

void DanceBattle::clearBoard()
{
    for (int row = 0; row < nMoves_; row++)
    {
        for (int col = 0; col < nMoves_; col++)
        {
            board_[row][col] = EMPTY;
        }
    }
}

// Return true if side s has valid turn. Return false otherwise.
bool DanceBattle::hasTurn(int lastMove) const
{
    for (int col = 0; col < nMoves_; col++)
    {
        if (squareIsEmpty(lastMove, col))
        {
            return true;
        }
    }
    return false;
}

// Return the static value of the current position.
int DanceBattle::positionValue(Side s, int lastMove) const
{
    bool result = hasTurn(lastMove);

    if (s == YOU && !result)
    {
        return OPPONENT_WIN;
    }
    else if (s == OPPONENT && !result)
    {
        return YOU_WIN;
    }
    return UNCLEAR;
}

// Routine to compute optimal turn.
int DanceBattle::chooseTurn(Side s, int bestRow, int & bestCol, int alpha,
                int beta, int depth)
{
    Side opp;
    int reply;
    int dc;
    int simpleEval;
    int value;
    bool isSetBestCol = false;
    //Position thisPosition = board_;

    if ((simpleEval = positionValue(s, bestRow)) != UNCLEAR)
    {
        bestCol = -1;
        return simpleEval;
    }

//    if (depth == 0)
//    {
//        transpositions = MapType(); // make empty transp. table
//    }
//    else if (depth >= MIN_DEPTH && depth <= MAX_DEPTH)
//    {
//        MapItr itr = transpositions.find(thisPosition);
//        if (itr != transpositions.end())
//            return (*itr).second;
//    }

    if (s == OPPONENT)
    {
        opp = YOU;
        value = alpha;
    }
    else
    {
        opp = OPPONENT;
        value = beta;
    }

    // Search for a move.
    for (int col = 0; col < nMoves_; col++)
    {
        if (squareIsEmpty(bestRow, col))
        {
            if (!isSetBestCol)
            {
                bestCol = col;
                isSetBestCol = true;
            }
            place(bestRow, col, s);
            reply = chooseTurn(opp, col, dc, alpha, beta, depth + 1);
            place(bestRow, col, EMPTY);

            // If s gets a better position; update
            if ((s == OPPONENT && reply > value) ||
                (s == YOU && reply < value))
            {
                if (s == OPPONENT)
                    alpha = value = reply;
                else
                    beta = value = reply;

                bestCol = col;

                if (alpha >= beta)
                {
//                    if (depth <= MAX_DEPTH)
//                        transpositions[thisPosition] = value;
                    return value;
                }
            }
        }
    }

    return value;
}

