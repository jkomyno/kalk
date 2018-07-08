package it.unipd.jkomyno.linearAlgebra;

import java.util.List;

public interface IContainer<T> {
    /**
     * Returns the number of entries in the storage
     *
     * @return
     */
    int getDataSize();

    /**
     * Returns true iff the container is equal to the current object
     *
     * @param container
     */
    boolean equals(IContainer<T> container);

    /**
     * Sets value of the current container at a specific index
     *
     * @param index
     * @param value
     */
    void setAt(int index, T value);

    /**
     * Returns the value of the current container at a specific index
     *
     * @param index
     */
    T getAt(int index);

    /**
     * Returns a copy of the container as an ordered list
     */
    List<T> getData();

    /**
     * Moltiplies every element in the container by a scalar value
     * @param scalar
     */
    void scale(T scalar);

    /**
     * Adds the selected scalar value to every element in the container
     *
     * @param scalar
     */
    void increment(T scalar);

    /**
     * Every element in the container assumes the value of scalar
     *
     * @param scalar
     */
    void fill(T scalar);

    /**
     * Zero-fills every element in the container
     */
    void zero();

    /**
     * Every element in the container assumes a random value between min and max
     */
    void random(T min, T max);

    /**
     * Inverts the sign of every element in the container
     */
    void negate();

    /**
     * Sorts the elements in ascending order
     */
    void sort();

    /**
     * Computes the ||A||_1 norm.
     * If it's applied to a matrix, it's the maximum absolute column sum of the matrix.
     * If it's applied to a vector, it's
     */
    //T norm1();

    /**
     * Computes the ||A||_infinity norm.
     * If it's applied to a matrix, it's the maximum absolute row sum of the matrix.
     * If it's applied to a vector, it's the maximum absolute value of the vector.
     */
    T normInfinity();

    /**
     * Returns the maximum value stored in the storage
     */
    T max();

    /**
     * Returns the minimum value stored in the storage
     */
    T min();

    /**
     * Returns the sum of every value stored in the storage
     */
    T sum();

    /**
     * Returns the maximum absolute value stored in the storage
     */
    T maxAbs();

    /**
     * Returns the minimum absolute value stored in the storage
     */
    T minAbs();

    /**
     * Returns the absolute sum of every value stored in the storage
     */
    T sumAbs();

    IContainer<T> cloneFactory(IContainer<T> obj);
}
