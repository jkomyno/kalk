package it.unipd.jkomyno.linearAlgebra;

import it.unipd.jkomyno.linearAlgebra.exceptions.IllegalDimensionsException;

public interface IMatrix<T> extends IContainer<T>, IMatrixIterator<T> {
    /**
     * Returns the number of rows of the matrix
     */
    int getRows();

    /**
     * Sets the number of rows of the matrix
     *
     * @param rows
     */
    void setRows(int rows);

    /**
     * Returns the number of columns of the matrix
     */
    int getColumns();

    /**
     * Sets the number of columns of the matrix
     *
     * @param columns
     */
    void setColumns(int columns);

    /**
     * Sets the new value of the current matrix at the specific getRow and getColumn
     *
     * @param row
     * @param column
     * @param value
     */
    void setAt(int row, int column, T value);

    /**
     * Returns the value of the current matrix at the specific getRow and getColumn
     *
     * @param row
     * @param column
     */
    T getAt(int row, int column);

    /**
     * Transposes the current matrix mutating it
     */
    void transpose();

    /**
     * Reshapes the current matrix mutating it
     */
    void reshape(int rows, int columns, int xStart, int yStart, T padValue) throws IllegalDimensionsException;

    void reshape(int rows, int columns);

    IMatrix<T> cloneFactory(IMatrix<T> obj, int newRows, int newColumns);

    IVector<T> getRowAt(int rowIndex);
}
