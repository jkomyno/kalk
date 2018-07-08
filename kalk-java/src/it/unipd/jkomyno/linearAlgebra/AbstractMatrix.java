package it.unipd.jkomyno.linearAlgebra;

import it.unipd.jkomyno.linearAlgebra.exceptions.IllegalDimensionsException;
import it.unipd.jkomyno.numberWrapper.NumberWrapper;

import java.util.Iterator;
import java.util.NoSuchElementException;

public abstract class AbstractMatrix<WRAPPER extends NumberWrapper<T>, T extends Comparable> extends AbstractContainer<WRAPPER, T, MatrixIteratorItem<T>> implements IMatrix<T> {
    private int rows;
    private int columns;

    public AbstractMatrix(WRAPPER numberWrapper, int rows, int columns) {
        super(numberWrapper);
        this.rows = rows;
        this.columns = columns;
    }

    public AbstractMatrix(WRAPPER numberWrapper) {
        this(numberWrapper, 0, 0);
    }

    public AbstractMatrix(AbstractMatrix<WRAPPER, T> a) {
        super(a);
        this.rows = a.rows;
        this.columns = a.columns;
    }

    public AbstractMatrix(AbstractMatrix<WRAPPER, T> a, int newRows, int newColumns) {
        super(a);
        this.rows = newRows;
        this.columns = newColumns;
    }

    /**
     * Returns true iff the container is equal to the current object
     *
     * @param container
     */
    @Override
    public boolean equals(IContainer<T> container) {
        if (!AbstractMatrix.class.isAssignableFrom(container.getClass())) {
            return false;
        }

        AbstractMatrix<WRAPPER, T> mat = (AbstractMatrix<WRAPPER, T>) container;
        return (this == container) || (rows == mat.rows && columns == mat.columns);
    }

    /**
     * Computes the ||A||_infinity norm.
     * If it's applied to a matrix, it's the maximum absolute row sum of the matrix.
     *
     * @return
     */
    @Override
    public T normInfinity() {
        T maximum = numberWrapper.minValue();
        for (int rowIndex = 1; rowIndex <= rows; rowIndex++) {
            AbstractVector<WRAPPER, T> vec = (AbstractVector<WRAPPER, T>) this.getRowAt(rowIndex);
            T rowSum = vec.sumAbs();
            int rowSumCompare = rowSum.compareTo(maximum);
            if (rowSumCompare > 0) {
                // rowSumCompare > maximum
                maximum = rowSum;
            }
        }
        return maximum;
    }

    /**
     * Returns the number of rows of the matrix
     */
    @Override
    public int getRows() {
        return rows;
    }

    /**
     * Sets the number of rows of the matrix
     *
     * @param rows
     */
    @Override
    public void setRows(int rows) {
        this.rows = rows;
    }

    /**
     * Returns the number of columns of the matrix
     */
    @Override
    public int getColumns() {
        return columns;
    }

    /**
     * Sets the number of columns of the matrix
     *
     * @param columns
     */
    @Override
    public void setColumns(int columns) {
        this.columns = columns;
    }

    /**
     * a.add(b) returns a + b
     * This method is immutable
     * @param b
     * @return a + b
     */
    public AbstractMatrix<WRAPPER, T> add(AbstractMatrix<WRAPPER, T> b) throws IllegalDimensionsException {
        if (rows != b.rows || columns != b.columns) {
            throw new IllegalDimensionsException();
        }

        AbstractMatrix<WRAPPER, T> result = (AbstractMatrix<WRAPPER, T>) cloneFactory(this, rows, columns);

        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= columns; j++) {
                T value = numberWrapper.safeAdd(getAt(i, j), b.getAt(i, j));
                result.setAt(i, j, value);
            }
        }

        return result;
    }

    /**
     * a.add(b) returns a - b
     * This method is immutable
     * @param b
     * @return a - b
     */
    public AbstractMatrix<WRAPPER, T> subtract(AbstractMatrix<WRAPPER, T> b) throws IllegalDimensionsException {
        if (rows != b.rows || columns != b.columns) {
            throw new IllegalDimensionsException();
        }

        AbstractMatrix<WRAPPER, T> result = (AbstractMatrix<WRAPPER, T>) cloneFactory(this, rows, columns);

        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= columns; j++) {
                T value = numberWrapper.safeSubtract(getAt(i, j), b.getAt(i, j));
                result.setAt(i, j, value);
            }
        }

        return result;
    }

    /**
     * a.add(b) returns a * b
     * This method is immutable
     * @param b
     * @return a * b
     */
    public AbstractMatrix<WRAPPER, T> multiply(AbstractMatrix<WRAPPER, T> b) throws IllegalDimensionsException {
        if (columns != b.rows) {
            throw new IllegalDimensionsException();
        }

        AbstractMatrix<WRAPPER, T> result = (AbstractMatrix<WRAPPER, T>) cloneFactory(this, rows, b.columns);

        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= b.columns; j++) {
                for (int k = 1; k <= b.rows; k++) {
                    T partialProduct = numberWrapper.multiply(getAt(i, k), b.getAt(k, j));
                    T value = numberWrapper.add(result.getAt(i, j), partialProduct);
                    result.setAt(i, j, value);
                }
            }
        }

        return result;
    }

    /**
     * Transposes the current matrix mutating it
     */
    @Override
    public void transpose() {
        AbstractMatrix<WRAPPER, T> helper = (AbstractMatrix<WRAPPER, T>) cloneFactory(this);
        int newColumns = rows;
        rows = columns;
        columns = newColumns;
        for (int row = 1; row <= rows; row++) {
            for (int column = 1; column <= columns; column++) {
                setAt(row, column, helper.getAt(column, row));
            }
        }
    }

    /**
     * Reshapes the current matrix mutating it
     *
     * @param newRows
     * @param newColumns
     * @param xStart
     * @param yStart
     * @param padValue
     */
    @Override
    public void reshape(int newRows, int newColumns, int xStart, int yStart, T padValue) throws IllegalDimensionsException {
        if (rows == newRows && columns == getColumns()) {
            return;
        }

        if ((newRows == 0 || newColumns == 0) || (newRows - xStart == 0 || newColumns - yStart == 0)) {
            throw new IllegalDimensionsException();
        }
    }

    /**
     * Reshapes the current matrix mutating it
     *
     * @param rows
     * @param columns
     */
    @Override
    public void reshape(int rows, int columns) {
        reshape(rows, columns, 0, 0, numberWrapper.zero());
    }

    /**
     * Returns a row major iterator over elements of type {@code T}.
     *
     * @return an Iterator.
     */
    @Override
    public Iterator<MatrixIteratorItem<T>> iterator() {
        return new MatrixIterator();
    }

    /**
     * Class that provides a row major iterator to the matrix.
     */
    class MatrixIterator implements Iterator<MatrixIteratorItem<T>> {
        /**
         * Indexes of the current item pointed by the iterator
         */
        private int row = 1;
        private int column = 1;

        final MatrixIteratorItemImpl cursorItem = new MatrixIteratorItemImpl();

        /**
         * Returns the next element in the iteration.
         *
         * @return the next element in the iteration
         * @throws NoSuchElementException if the iteration has no more elements
         */
        @Override
        public MatrixIteratorItem next() {
            cursorItem.changeIndexes(row, column);

            if (column < columns) {
                column++;
            } else {
                row++;
                column = 1;
            }

            return cursorItem;
        }

        public boolean hasNext() {
            return (row <= rows) &&
                    (column <= columns);
        }
    }

    class MatrixIteratorItemImpl implements MatrixIteratorItem<T> {
        /**
         * Indexes of the current item pointed by the iterator
         */
        private int row = 1;
        private int column = 1;

        public void changeIndexes(int row, int column) {
            this.row = row;
            this.column = column;
        }

        /**
         * Returns the current row index
         */
        @Override
        public int getRow() {
            return row;
        }

        /**
         * Returns the current column index
         */
        @Override
        public int getColumn() {
            return column;
        }

        /**
         * Returns the value at the current index
         */
        @Override
        public T getValue() {
            return getAt(row, column);
        }

        /**
         * Sets the value at the current index
         *
         * @param value
         */
        @Override
        public void setValue(T value) {
            setAt(row, column, value);
        }
    }

    /**
     * In linear algebra, every matrix or vector is indexed starting from 1, and
     * not from 0
     *
     * @param row
     * @param column
     * @param columns
     */
    protected static int getIndex(int row, int column, int columns) {
        return (row - 1) * columns + (column - 1);
    }
}
