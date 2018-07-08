package it.unipd.jkomyno.linearAlgebra;

public interface ISquareMatrix<T> extends IMatrix<T> {
    /**
     * Returns the dimension of the square matrix, intended as the number of
     * rows or columns, which in a square matrix are the same
     */
    int getDimension();

    /**
     * Computes and returns the trace of the square matrix, which is defined by
     * the sum of the elements on the main diagonal
     */
    T trace();

    /**
     * Computes and returns the determinant of the square matrix
     */
    T determinant();

    Iterable<DiagonalMatrixIteratorItem<T>> getDiagonalIterator();

    /**
     * Mutates the current matrix setting scalar as the value for every item
     * in the matrix diagonal
     *
     * @param scalar
     */
    default void fillDiagonal(T scalar) {
        for (DiagonalMatrixIteratorItem<T> item : getDiagonalIterator()) {
            item.setValue(scalar);
        }
    }
}
