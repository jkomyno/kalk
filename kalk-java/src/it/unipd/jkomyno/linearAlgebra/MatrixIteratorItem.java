package it.unipd.jkomyno.linearAlgebra;

/**
 * Item returned by an iterator over a Matrix
 */
public interface MatrixIteratorItem<T> extends GeneralIteratorItem<T> {
    /**
     * Returns the current row index
     */
    int getRow();

    /**
     * Returns the current column index
     */
    int getColumn();
}
