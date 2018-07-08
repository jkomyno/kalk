package it.unipd.jkomyno.linearAlgebra;

public interface IDiagonalMatrix<T> extends ISquareMatrix<T> {
    /**
     * Mutates the current diagonal matrix to an identity matrix, that is,
     * a diagonal matrix with a sequence of 1 in the diagonal
     */
    void toIdentity();

    /**
     * Returns true if and only if the current diagonal matrix is an identity.
     * A digaonal matrix is defined as identity if all the values on its main diagonal are equal to 1
     */
    boolean isIdentity();

    IVector<T> getDiagonal();
}
