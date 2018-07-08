package it.unipd.jkomyno.linearAlgebra;

import it.unipd.jkomyno.numberWrapper.NumberWrapper;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import static it.unipd.jkomyno.linearAlgebra.utils.ListUtils.copyList;
import static it.unipd.jkomyno.linearAlgebra.utils.ListUtils.initArraySize;
import static it.unipd.jkomyno.linearAlgebra.utils.ListUtils.sortList;

public abstract class AbstractDenseVector<WRAPPER extends NumberWrapper<T>, T extends Comparable> extends AbstractVector<WRAPPER, T> {
    private List<T> data;

    public AbstractDenseVector(WRAPPER numberWrapper, int length) {
        super(numberWrapper, length);
    }

    public AbstractDenseVector(WRAPPER numberWrapper) {
        super(numberWrapper);
    }

    public AbstractDenseVector(WRAPPER numberWrapper, Stream<T> vector) {
        super(numberWrapper, (int) vector.count());
        this.data = vector.collect(Collectors.toList());
    }

    public AbstractDenseVector(WRAPPER numberWrapper, List<T> vector) {
        super(numberWrapper, vector.size());
        this.data = vector.stream().collect(Collectors.toList());
    }

    public AbstractDenseVector(AbstractDenseVector<WRAPPER, T> vec) {
        super(vec);
        this.data = copyList(vec.data);
    }

    public AbstractDenseVector(AbstractDenseVector<WRAPPER, T> a, int newLength) {
        super(a, newLength);
        this.data = initArraySize(newLength, numberWrapper.zero());
    }

    /**
     * Returns the number of entries in the storage
     *
     * @return
     */
    @Override
    public int getDataSize() {
        return data.size();
    }

    /**
     * Returns true iff the container is equal to the current object
     *
     * @param container
     */
    @Override
    public boolean equals(IContainer<T> container) {
        if (!(container instanceof AbstractDenseVector)) {
            return false;
        }

        AbstractDenseVector<WRAPPER, T> vec = (AbstractDenseVector<WRAPPER, T>) container;
        return super.equals(vec) && data.equals(vec.data);
    }

    /**
     * Sets value of the current container at a specific index
     *
     * @param index
     * @param value
     */
    @Override
    public void setAt(int index, T value) {
        data.set(index - 1, value);
    }

    /**
     * Retrieves the value of the current container at a specific index
     *
     * @param index
     */
    @Override
    public T getAt(int index) {
        return data.get(index - 1);
    }

    /**
     * Retrieves every internal value of the container as an ordered list
     */
    @Override
    public List<T> getData() {
        return data;
    }

    /**
     * Sorts the elements in ascending order
     */
    @Override
    public void sort() {
        sortList(data);
    }
}
