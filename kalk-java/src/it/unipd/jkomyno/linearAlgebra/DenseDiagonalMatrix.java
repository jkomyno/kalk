package it.unipd.jkomyno.linearAlgebra;

import it.unipd.jkomyno.linearAlgebra.exceptions.DiagonalMatrixException;
import it.unipd.jkomyno.numberWrapper.NumberWrapper;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class DenseDiagonalMatrix<WRAPPER extends NumberWrapper<T>, T extends Comparable> extends DenseSquareMatrix<WRAPPER, T> implements IDiagonalMatrix<T> {
    public DenseDiagonalMatrix(WRAPPER numberWrapper) {
        super(numberWrapper);
    }

    public DenseDiagonalMatrix(WRAPPER numberWrapper, int dimensions) {
        super(numberWrapper, dimensions);
    }

    public DenseDiagonalMatrix(DenseSquareMatrix<WRAPPER, T> mat) {
        super(mat);
        checkIsDiagonal();
    }

    protected DenseDiagonalMatrix(DenseSquareMatrix<WRAPPER, T> mat, int newDimensions) {
        super(mat, newDimensions);
        checkIsDiagonal();
    }

    public DenseDiagonalMatrix(WRAPPER numberWrapper, Stream<T>... rows) {
        super(numberWrapper, rows);
        checkIsDiagonal();
    }

    public DenseDiagonalMatrix(WRAPPER numberWrapper, List<T>... rows) {
        super(numberWrapper, rows);
        checkIsDiagonal();
    }

    /**
     * Computes and returns the determinant of the square matrix
     */
    @Override
    public T determinant() {
        // The determinant of a diagonal matrix is the product of its diagonal entries
        T determinant = numberWrapper.one();
        for (DiagonalMatrixIteratorItem<T> item : getDiagonalIterator()) {
            determinant = numberWrapper.safeMultiply(determinant, item.getValue());
        }
        return determinant;
    }

    /**
     * Moltiplies every element in the container by a scalar value
     *
     * @param scalar
     */
    @Override
    public void scale(T scalar) {
        // This is overridden to avoid performing useless multiplications
        // on the 0 elements
        if (scalar != numberWrapper.one()) {
            for (DiagonalMatrixIteratorItem<T> item : getDiagonalIterator()) {
                T value = numberWrapper.safeMultiply(scalar, item.getValue());
                item.setValue(value);
            }
        }
    }

    /**
     * Inverts the sign of every element in the container
     */
    @Override
    public void negate() {
        for (DiagonalMatrixIteratorItem<T> item : getDiagonalIterator()) {
            item.setValue(numberWrapper.negate(item.getValue()));
        }
    }

    /**
     * Every element in the container assumes a random value between min and max
     *
     * @param min
     * @param max
     */
    @Override
    public void random(T min, T max) {
        for (DiagonalMatrixIteratorItem<T> item : getDiagonalIterator()) {
            item.setValue(numberWrapper.random(min, max));
        }
    }

    /**
     * Transposes the current matrix mutating it
     */
    @Override
    public void transpose() {
        // the transpose of a diagonal matrix is again the same matrix
        return;
    }

    /**
     * Mutates the current diagonal matrix to an identity matrix, that is,
     * a diagonal matrix with a sequence of 1 in the diagonal
     */
    @Override
    public void toIdentity() {
        fillDiagonal(numberWrapper.one());
    }

    /**
     * Returns true if and only if the current diagonal matrix is an identity.
     * A digaonal matrix is defined as identity if all the values on its main diagonal are equal to 1
     */
    @Override
    public boolean isIdentity() {
        for (DiagonalMatrixIteratorItem<T> item : getDiagonalIterator()) {
            if (item.getValue() != numberWrapper.one()) {
                return false;
            }
        }
        return true;
    }

    @Override
    public IVector<T> getDiagonal() {
        List<T> rawData = this.diagonalStream()
                .map(item -> item.getValue())
                .collect(Collectors.toList());
        return new DenseVector<>(numberWrapper, rawData);
    }

    private void checkIsDiagonal() {
        for (MatrixIteratorItem<T> item : this) {
            if (item.getColumn() != item.getRow() && item.getValue() != numberWrapper.zero()) {
                throw new DiagonalMatrixException(); // The elements which are not on the main diagonal must be 0
            } else if (item.getRow() == item.getColumn() && item.getValue() == numberWrapper.zero()) {
                throw new DiagonalMatrixException(); // The elements on the main diagonal must be != 0
            }
        }
    }
}
