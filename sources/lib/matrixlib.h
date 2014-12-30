#ifndef MATRIXLIB_H
#define MATRIXLIB_H

#include "lib/calculables/matrix.h"
#include "lib/calculables/scalar.h"
#include "lib/calculable.h"

class Matrix;
class Scalar;

class MatrixLib
{
public:

    /**
     * @brief Create an identity matrix
     * @param n - Size of the matrix n*n
     * @return the identity matrix generated
     */
    static Matrix *identity(int n);

    /**
     * @brief Calculate matrix cofacteur
     * @param source - The source matrix
     * @param i - The line where the cofacteur is calculated (between 0 and M-1)
     * @param j - The column where the cofacteur is calculated (between 0 and N-1)
     * @return The cofacteur
     */
    static Scalar *cofactor(Matrix *source, int i, int j);


    /**
     * @brief Calculate determinant of a matrix
     * @param source - The source matrix
     * @return The determinant
     */
    static Scalar *determinant(Matrix *source);

    /**
     * @brief Transpose a matrix
     * @param source - The source matrix
     * @return The transposed matrix
     */
    static Matrix *transpose(Matrix *source);

    /**
     * @brief Find cofactor matrix of source
     * @param source - Source matrix
     * @return The cofactor matrix
     */
    static Matrix *coMatrix(Matrix *source);

    /**
     * @brief Find the inverse matrix of source if possible, rise excepetion if not possible.
     * @param source - Source matrix
     * @return The inverse matrix
     */
    static Matrix *inv(Matrix *source);

    /**
     * @brief Calculate trace of the matrix
     * @param source - Source matrix
     * @return The trace
     */
    static double trace(Matrix *source);

    /**
     * @brief Calculate norm of vertical or horizontal vector
     * @param source - Source column or line matrix
     * @return The norm
     */
    static double norm(Matrix *source);
};

#endif // MATRIXLIB_H
