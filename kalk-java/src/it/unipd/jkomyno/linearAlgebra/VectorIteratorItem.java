package it.unipd.jkomyno.linearAlgebra;

/**
 * Item returned by an iterator over a Vector
 */
public interface VectorIteratorItem<T> extends GeneralIteratorItem<T> {
    /**
     * Returns the current index
     */
    int getIndex();
}
