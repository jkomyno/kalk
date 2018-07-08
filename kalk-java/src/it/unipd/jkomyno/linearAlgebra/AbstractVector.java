package it.unipd.jkomyno.linearAlgebra;

import it.unipd.jkomyno.numberWrapper.NumberWrapper;

import java.util.Iterator;
import java.util.NoSuchElementException;

public abstract class AbstractVector<WRAPPER extends NumberWrapper<T>, T extends Comparable> extends AbstractContainer<WRAPPER, T, VectorIteratorItem<T>> implements IVector<T> {
    private int length;

    public AbstractVector(WRAPPER numberWrapper, int length) {
        super(numberWrapper);
        this.length = length;
    }

    public AbstractVector(WRAPPER numberWrapper) {
        this(numberWrapper, 0);
    }

    public AbstractVector(AbstractVector<WRAPPER, T> a) {
        this(a.numberWrapper, a.length);
    }

    public AbstractVector(AbstractVector<WRAPPER, T> a, int newLength) {
        this(a.numberWrapper, newLength);
    }

    /**
     * Returns a row major iterator over elements of type {@code T}.
     *
     * @return an Iterator.
     */
    @Override
    public Iterator<VectorIteratorItem<T>> iterator() {
        return new VectorIterator();
    }

    /**
     * Returns true iff the container is equal to the current object
     *
     * @param container
     */
    @Override
    public boolean equals(IContainer<T> container) {
        if (!AbstractVector.class.isAssignableFrom(container.getClass())) {
            return false;
        }

        AbstractVector<WRAPPER, T> vec = (AbstractVector<WRAPPER, T>) container;
        return (this == container) || (length == vec.length);
    }

    /**
     * Computes the ||A||_infinity norm.
     * If it's applied to a vector, it's the maximum absolute value of that vector.
     *
     * @return
     */
    @Override
    public T normInfinity() {
        return maxAbs();
    }

    /**
     * Class that provides an iterator to the vector.
     */
    class VectorIterator implements Iterator<VectorIteratorItem<T>> {
        /**
         * Indexes of the current item pointed by the iterator
         */
        private int index = 1;

        final VectorIteratorItemImpl cursorItem = new VectorIteratorItemImpl();

        /**
         * Returns the next element in the iteration.
         *
         * @return the next element in the iteration
         * @throws NoSuchElementException if the iteration has no more elements
         */
        @Override
        public VectorIteratorItem next() {
            cursorItem.changeIndex(index);
            index++;
            return cursorItem;
        }

        public boolean hasNext() {
            return index <= length;
        }
    }

    class VectorIteratorItemImpl implements VectorIteratorItem<T> {
        /**
         * Indexes of the current item pointed by the iterator
         */
        private int index = 1;

        public void changeIndex(int index) {
            this.index = index;
        }

        /**
         * Returns the current row index
         */
        @Override
        public int getIndex() {
            return index;
        }

        /**
         * Returns the value at the current index
         */
        @Override
        public T getValue() {
            return getAt(index);
        }

        /**
         * Sets the value at the current index
         *
         * @param value
         */
        @Override
        public void setValue(T value) {
            setAt(index, value);
        }
    }
}
