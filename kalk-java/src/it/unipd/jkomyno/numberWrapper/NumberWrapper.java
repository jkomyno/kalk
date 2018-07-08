package it.unipd.jkomyno.numberWrapper;

import it.unipd.jkomyno.linearAlgebra.exceptions.NumberOverflowException;

public interface NumberWrapper<T extends Comparable> {
    /**
     * Adds two numbers and returns the result
     *
     * @param x
     * @param y
     */
    T add(T x, T y);
    T add(Object... args);

    /**
     * Subtracts two numbers and returns the result
     *
     * @param x
     * @param y
     */
    T subtract(T x, T y);
    T subtract(Object... args);

    /**
     * Multiplies two numbers and returns the result
     *
     * @param x
     * @param y
     */
    T multiply(T x, T y);
    T multiply(Object... args);

    /**
     * Changes the sign of a number and returns the result
     *
     * @param x
     */
    T negate(T x);

    /**
     * Returns the zero value for the type T
     */
    T zero();

    /**
     * Returns the one value for the type T
     */
    T one();

    /**
     * Returns the negative one value for the type T
     */
    T negativeOne();

    /**
     * Returns a random value for the type T, where min <= value <= max
     *
     * @param min
     * @param max
     */
    T random(T min, T max);

    /**
     * Returns the lower bound of the number type.
     * For int, this would be –2,147,483,648
     */
    T minValue();

    /**
     * Returns the upper bound of the number type.
     * For int, this would be 2,147,483,647
     */
    T maxValue();

    /**
     * Returns the absolute of value
     * @param value
     */
    default T absolute(T value) {
        int compareRes = value.compareTo(zero());
        if (compareRes < 0) {
            // value was negative
            return negate(value);
        } else {
            return value;
        }
    }

    // https://wiki.sei.cmu.edu/confluence/display/java/NUM00-J.+Detect+or+prevent+integer+overflow

    /**
     * Adds two numbers and returns the result, while ensuring that no overflow gets unnoticed
     * @param x
     * @param y
     */
    default T safeAdd(T x, T y) throws NumberOverflowException {
        int compareYWith0 = y.compareTo(zero());
        if (compareYWith0 > 0) {
            // y > 0
            int compareX = x.compareTo(subtract(maxValue(), y)); // (x > maxValue() - y) ?
            if (compareX > 0 ) {
                throw new NumberOverflowException();
            }
        } else {
            // y <= 0
            int compareX = x.compareTo(subtract(minValue(), y)); // (x < minValue() - y) ?
            if (compareX < 0 ) {
                throw new NumberOverflowException();
            }
        }

        return add(x, y);
    }

    /**
     * Subtracts two numbers and returns the result, while ensuring that no overflow gets unnoticed
     * @param x
     * @param y
     */
    default T safeSubtract(T x, T y) throws NumberOverflowException {
        int compareYWith0 = y.compareTo(zero());
        if (compareYWith0 > 0) {
            // y > 0
            int compareX = x.compareTo(add(minValue(), y)); // (x < minValue() - y) ?
            if (compareX < 0 ) {
                throw new NumberOverflowException();
            }
        } else {
            // y <= 0
            int compareX = x.compareTo(add(maxValue(), y)); // (x > maxValue() - y) ?
            if (compareX > 0 ) {
                throw new NumberOverflowException();
            }
        }

        return subtract(x, y);
    }

    /**
     * Subtracts two numbers and returns the result, while ensuring that no overflow gets unnoticed
     * @param x
     * @param y
     */
    default T safeMultiply(T x, T y) throws NumberOverflowException {
        return multiply(x, y);
    }
}