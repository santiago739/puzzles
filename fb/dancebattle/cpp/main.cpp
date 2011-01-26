#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "DanceBattle.h"

using namespace std;

typedef unsigned int uint;

struct Move
{
    int first;
    int second;
};

void printBoard(const DanceBattle& obj)
{
    const Matrix<int>& b = obj.getBoard();
    int nRows = b.getRowsNumber();
    int nCols = b.getColsNumber();

    cout << "- - -" << endl;
    for (int row = 0; row < nRows; row++)
    {
        for (int col = 0; col < nCols; col++)
        {
            if (b[row][col] == DanceBattle::OPPONENT)
            {
                cout << "C ";
            }
            else if (b[row][col] == DanceBattle::YOU)
            {
                cout << "H ";
            }
            else
            {
                cout << "  ";
            }
        }
        cout << endl;
    }
    cout << "- - -" << endl;
}

bool doTurn(DanceBattle::Side s, DanceBattle & t, int & lastMove)
{
    int bestRow, bestCol, value;

    bestRow = lastMove;
    value = t.chooseTurn(s, bestRow, bestCol);

    if (bestCol == -1 && s == DanceBattle::YOU)
    {
        cout << "Lose" << endl;
        return false;
    }
    else if (bestCol == -1 && s == DanceBattle::OPPONENT)
    {
        cout << "Win" << endl;
        return false;
    }

#ifdef DEBUG
    if (s == DanceBattle::OPPONENT)
        cout << "YOU plays:";
    else if (s == DanceBattle::YOU)
        cout << "OPPONENT plays:";
    cout << " LAST_MOVE = " << lastMove << " ROW = " << bestRow << " COL = "
                    << bestCol << endl;
#endif

    if (!t.playTurn(s, bestRow, bestCol))
    {
#ifdef DEBUG
        cerr << "Wrong turn: " << bestRow << " " << bestCol << endl;
#endif
        return false;
    }
    lastMove = bestCol;

    return true;
}

void playGame(vector<Move>& moves, int nMoves)
{
    DanceBattle t(nMoves);
    DanceBattle::Side s;
    vector<Move>::iterator iMoves;
    int lastMove = 0;
    bool result;

    // Make turns which were done
    s = DanceBattle::YOU;
    for (iMoves = moves.begin(); iMoves < moves.end(); ++iMoves)
    {
        result = t.playTurn(s, (*iMoves).first, (*iMoves).second);
        if (!result)
        {
#ifdef DEBUG
            cerr << "Wrong turn: ";
            cerr << (*iMoves).first << " " << (*iMoves).second << endl;
#endif
            return;
        }

        if (s == DanceBattle::YOU)
            s = DanceBattle::OPPONENT;
        else
            s = DanceBattle::YOU;

        lastMove = (*iMoves).second;
    }
    //	printBoard(t);

    // Simulate play game
    while (true)
    {
        result = doTurn(s, t, lastMove);
        if (!result)
        {
            return;
        }
        //		printBoard(t);

        if (s == DanceBattle::YOU)
            s = DanceBattle::OPPONENT;
        else
            s = DanceBattle::YOU;
    }
}

bool readInput(const char* fileName, vector<Move> & moves, int& nMoves)
{
    ifstream inFile(fileName);
    istringstream iss;
    string fileLine;
    int nMovesDone;
    Move tmpMove;

    if (!inFile)
    {
        cerr << "Cannot open " << fileName << endl;
        return false;
    }

    if (!getline(inFile, fileLine).eof())
    {
        iss.clear();
        iss.str(fileLine);
        iss >> nMoves;

#ifdef DEBUG
        cout << nMoves << endl;
#endif        
    }

    if (!getline(inFile, fileLine).eof())
    {
        iss.clear();
        iss.str(fileLine);
        iss >> nMovesDone;

#ifdef DEBUG
        cout << nMovesDone << endl;
#endif        
    }

    while (nMovesDone > 0 && !getline(inFile, fileLine).eof())
    {
        iss.clear();
        iss.str(fileLine);
        iss >> tmpMove.first >> tmpMove.second;
        moves.push_back(tmpMove);
        nMovesDone--;
    }

    return true;
}

int main(int argc, char *argv[])
{
    int nMoves;
    vector<Move> moves;
    vector<Move>::iterator iMoves;

    if (argc != 2 || !readInput(argv[1], moves, nMoves))
    {
        return 1;
    }

#ifdef DEBUG
    for (iMoves = moves.begin(); iMoves < moves.end(); ++iMoves)
    {
        cout << (*iMoves).first << " " << (*iMoves).second << endl;
    }
#endif

    playGame(moves, nMoves);

    return 0;
}
