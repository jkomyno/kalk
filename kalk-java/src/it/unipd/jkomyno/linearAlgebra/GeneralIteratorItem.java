package it.unipd.jkomyno.linearAlgebra;

public interface GeneralIteratorItem<T> {
    /**
     * Returns the value at the current index
     */
    T getValue();

    /**
     * Sets the value at the current index
     */
    void setValue(T value);
}
