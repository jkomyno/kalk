package it.unipd.jkomyno.linearAlgebra;

import it.unipd.jkomyno.numberWrapper.NumberWrapper;

public abstract class AbstractContainer<WRAPPER extends NumberWrapper<T>, T extends Comparable, IT extends GeneralIteratorItem<T>> implements IContainer<T>, IContainerIterator<T, IT> {
    protected WRAPPER numberWrapper;

    public AbstractContainer(WRAPPER numberWrapper) {
        this.numberWrapper = numberWrapper;
    }

    public AbstractContainer(AbstractContainer<WRAPPER, T, IT> a) {
        this(a.numberWrapper);
    }

    /**
     * Moltiplies every element in the container by a scalar value
     *
     * @param scalar
     */
    @Override
    public void scale(T scalar) {
        if (scalar != numberWrapper.one()) {
            for (IT item : this) {
                T value = numberWrapper.safeMultiply(scalar, item.getValue());
                item.setValue(value);
            }
        }
    }

    /**
     * Adds the values of scalar to every element in the container
     *
     * @param scalar
     */
    @Override
    public void increment(T scalar) {
        if (scalar != numberWrapper.zero()) {
            for (IT item : this) {
                T value = numberWrapper.safeAdd(scalar, item.getValue());
                item.setValue(value);
            }
        }
    }

    /**
     * Every element in the container assumes the value of scalar
     *
     * @param scalar
     */
    @Override
    public void fill(T scalar) {
        for (IT item : this) {
            item.setValue(scalar);
        }
    }

    /**
     * Zero-fills every element in the container
     */
    @Override
    public void zero() {
        for (IT item : this) {
            item.setValue(numberWrapper.zero());
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
        for (IT item : this) {
            item.setValue(numberWrapper.random(min, max));
        }
    }

    /**
     * Inverts the sign of every element in the container
     */
    @Override
    public void negate() {
        for (IT item : this) {
            item.setValue(numberWrapper.negate(item.getValue()));
        }
    }

    /**
     * Returns the maximum value stored in the storage
     */
    @Override
    public T max() {
        return maxHelper(false);
    }

    /**
     * Returns the minimum value stored in the storage
     */
    @Override
    public T min() {
        return minHelper(false);
    }

    /**
     * Returns the sum of every value stored in the storage
     */
    @Override
    public T sum() {
        return sumHelper(false);
    }

    /**
     * Returns the maximum absolute value stored in the storage
     */
    @Override
    public T maxAbs() {
        return maxHelper(true);
    }

    /**
     * Returns the minimum absolute value stored in the storage
     */
    @Override
    public T minAbs() {
        return minHelper(true);
    }

    /**
     * Returns the absolute sum of every value stored in the storage
     */
    @Override
    public T sumAbs() {
        return sumHelper(true);
    }

    private T maxHelper(boolean absolute) {
        T maximum = numberWrapper.minValue();
        for (IT item : this) {
            T currentValue = item.getValue();
            if (absolute) {
                currentValue = numberWrapper.absolute(currentValue);
            }
            int compareResult = maximum.compareTo(currentValue);
            if (compareResult < 0) {
                maximum = currentValue;
            }
        }
        return maximum;
    }

    private T minHelper(boolean absolute) {
        T minimum = numberWrapper.maxValue();
        for (IT item : this) {
            T currentValue = item.getValue();
            if (absolute) {
                currentValue = numberWrapper.absolute(currentValue);
            }
            int compareResult = currentValue.compareTo(minimum);
            if (compareResult < 0) {
                minimum = currentValue;
            }
        }
        return minimum;
    }

    private T sumHelper(boolean absolute) {
        T sum = numberWrapper.zero();
        for (IT item : this) {
            T currentValue = item.getValue();
            if (absolute) {
                currentValue = numberWrapper.absolute(currentValue);
            }
            sum = numberWrapper.add(sum, currentValue);
        }
        return sum;
    }
}
