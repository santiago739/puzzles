/*
 * Matrix.h
 *
 *  Created on: Jan 18, 2011
 *      Author: santiago
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>

template<class T>
class Matrix
{
public:
    Matrix(int rows, int cols) :
        array(rows)
    {
        for (int i = 0; i < rows; i++)
            array[i].resize(cols);
    }

    Matrix(const Matrix & rhs) :
        array(rhs.array)
    {
    }

    const std::vector<T> & operator[](int row) const
    {
        return array[row];
    }

    std::vector<T> & operator[](int row)
    {
        return array[row];
    }

    int getRowsNumber() const
    {
        return array.size();
    }

    int getColsNumber() const
    {
        return getRowsNumber() > 0 ? array[0].size() : 0;
    }

private:
    std::vector<std::vector<T> > array;
};

#endif /* MATRIX_H_ */
