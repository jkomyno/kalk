package it.unipd.jkomyno.linearAlgebra;

import it.unipd.jkomyno.linearAlgebra.exceptions.SquareMatrixException;
import it.unipd.jkomyno.numberWrapper.NumberWrapper;

import java.util.*;
import java.util.stream.Stream;
import java.util.stream.StreamSupport;

public class DenseSquareMatrix<WRAPPER extends NumberWrapper<T>, T extends Comparable> extends DenseMatrix<WRAPPER, T> implements ISquareMatrix<T> {
    public DenseSquareMatrix(WRAPPER numberWrapper) {
        super(numberWrapper);
    }

    public DenseSquareMatrix(WRAPPER numberWrapper, int dimensions) {
        super(numberWrapper, dimensions, dimensions);
    }

    public DenseSquareMatrix(DenseMatrix<WRAPPER, T> mat) {
        super(mat);
    }

    protected DenseSquareMatrix(DenseSquareMatrix<WRAPPER, T> mat, int newDimensions) {
        super(mat, newDimensions, newDimensions);
    }

    public DenseSquareMatrix(WRAPPER numberWrapper, Stream<T>... rows) {
        super(numberWrapper, (ListChecker<T>) list -> checkIsSquareList(list), rows.length, rows);
    }

    public DenseSquareMatrix(WRAPPER numberWrapper, List<T>... rows) {
        super(numberWrapper, (ListChecker<T>) list -> checkIsSquareList(list), rows.length, rows);
    }

    /**
     * Returns the dimension of the square matrix, intended as the number of
     * rows or columns, which in a square matrix are the same
     */
    @Override
    public int getDimension() {
        return getRows();
    }

    /**
     * Computes and returns the trace of the square matrix
     */
    @Override
    public T trace() {
        T result = numberWrapper.zero();
        for (DiagonalMatrixIteratorItem<T> item : getDiagonalIterator()) {
            result = numberWrapper.add(result, item.getValue());
        }
        return result;
    }

    /**
     * Computes and returns the determinant of the square matrix
     */
    @Override
    public T determinant() {
        switch (getDimension()) {
            case 1:
                return determinant1x1();
            case 2:
                return determinant2x2();
            case 3:
                return determinant3x3();
            default:
                return determinantNxN();
        }
    }

    /**
     * The determinant of a scalar is the scalar itself
     */
    private T determinant1x1() {
        return getAt(1, 1);
    }

    /**
     * The determinant of a 2x2 square matrix is det(A) = ad - bc
     */
    protected T determinant2x2() {
        T mult1 = numberWrapper.multiply(getAt(1, 1), getAt(2, 2));
        T mult2 = numberWrapper.multiply(getAt(1, 2), getAt(2, 1));

        return numberWrapper.subtract(mult1, mult2);
    }

    /**
     * The determinant of a 3x3 square matrix is determined applying the Sarrus Rule
     * https://en.wikipedia.org/wiki/Rule_of_Sarrus
     */
    protected T determinant3x3() {
        T a11 = getAt(1, 1);
        T a12 = getAt(1, 2);
        T a13 = getAt(1, 3);
        T a21 = getAt(2, 1);
        T a22 = getAt(2, 2);
        T a23 = getAt(2, 3);
        T a31 = getAt(3, 1);
        T a32 = getAt(3, 2);
        T a33 = getAt(3, 3);
        
        T mult1 = numberWrapper.multiply(a11, a22, a33);
        T mult2 = numberWrapper.multiply(a12, a23, a31);
        T mult3 = numberWrapper.multiply(a13, a21, a32);

        T mult4 = numberWrapper.multiply(a31, a22, a13);
        T mult5 = numberWrapper.multiply(a32, a23, a11);
        T mult6 = numberWrapper.multiply(a33, a21, a12);

        T diff1 = numberWrapper.subtract(mult1, mult4);
        T diff2 = numberWrapper.subtract(mult2, mult5);
        T diff3 = numberWrapper.subtract(mult3, mult6);

        return numberWrapper.add(diff1, diff2, diff3);
    }

    /**
     * The determinant of a NxN square matrix is determined applying Laplace Expansion Rule
     */
    protected T determinantNxN() {
        T determinant = numberWrapper.zero();
        int dimension = getDimension();

        for (int i = 1; i <= dimension; i++) {
            DenseSquareMatrix<WRAPPER, T> mat = new DenseSquareMatrix<>(this, dimension - 1);
            for (int j = 2; j <= dimension; j++) {
                for (int k = 1; k <= dimension; k++) {
                    T value = this.getAt(j, k);
                    if (k < i) {
                        mat.setAt(j - 1, k, value);
                    } else if (k > i) {
                        mat.setAt(j - 1, k - 1, value);
                    }
                }
            }

            T sign = (i % 2 == 1) ?
                    numberWrapper.one() :
                    numberWrapper.negativeOne();

            T multiplier = numberWrapper.multiply(sign, this.getAt(1, i), mat.determinant());
            determinant = numberWrapper.add(determinant, multiplier);
        }

        return determinant;
    }

    public Iterable<DiagonalMatrixIteratorItem<T>> getDiagonalIterator() {
        return new DiagonalMatrixIterator();
    }

    class DiagonalMatrixIterator implements Iterator<DiagonalMatrixIteratorItem<T>>, Iterable<DiagonalMatrixIteratorItem<T>> {
        private int index = 1;

        final DiagonalMatrixIteratorItemImpl cursorItem = new DiagonalMatrixIteratorItemImpl();

        /**
         * Returns {@code true} if the iteration has more elements.
         * (In other words, returns {@code true} if {@link #next} would
         * return an element rather than throwing an exception.)
         *
         * @return {@code true} if the iteration has more elements
         */
        @Override
        public boolean hasNext() {
            return index <= getDimension();
        }

        /**
         * Returns the next element in the iteration.
         *
         * @return the next element in the iteration
         * @throws NoSuchElementException if the iteration has no more elements
         */
        @Override
        public DiagonalMatrixIteratorItem next() {
            cursorItem.changeIndex(index);
            index++;
            return cursorItem;
        }

        /**
         * Returns an iterator over elements of type {@code T}.
         *
         * @return an Iterator.
         */
        @Override
        public Iterator iterator() {
            return this;
        }
    }

    class DiagonalMatrixIteratorItemImpl implements DiagonalMatrixIteratorItem<T> {
        /**
         * Indexes of the current item pointed by the iterator
         */
        private int index = 1;

        public void changeIndex(int index) {
            this.index = index;
        }

        @Override
        public int getIndex() {
            return index;
        }

        /**
         * Returns the value at the current index
         */
        @Override
        public T getValue() {
            return getAt(index, index);
        }

        /**
         * Sets the value at the current index
         *
         * @param value
         */
        @Override
        public void setValue(T value) {
            setAt(index, index, value);
        }
    }

    protected Stream<DiagonalMatrixIteratorItem<T>> diagonalStream() {
        return StreamSupport.stream(this.getDiagonalIterator().spliterator(), false);
    }

    private static <T> void checkIsSquareList(List<List<T>> rows) {
        int columns = rows.size();
        boolean allRowsHaveSameSizeAsTheNumberOfRows = rows
                .stream()
                .filter(row -> row.size() == columns)
                .count() == columns;

        if (!allRowsHaveSameSizeAsTheNumberOfRows) {
            throw new SquareMatrixException();
        }
    }
}
