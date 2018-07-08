package it.unipd.jkomyno.numberWrapper;

import it.unipd.jkomyno.linearAlgebra.exceptions.NumberOverflowException;

import java.util.Random;

public class IntegerWrapper implements NumberWrapper<Integer> {
    private static final int ZERO = 0;
    private static final int ONE = 1;
    private Random rand;

    /**
     * Adds two numbers and returns the result
     *
     * @param x
     * @param y
     * @return
     */
    @Override
    public Integer add(Integer x, Integer y) {
        return x + y;
    }

    @Override
    public Integer add(Object... args) {
        Integer result = zero();
        for (Object arg : args) {
            result += (Integer) arg;
        }

        return result;
    }

    /**
     * Subtracts two numbers and returns the result
     *
     * @param x
     * @param y
     * @return
     */
    @Override
    public Integer subtract(Integer x, Integer y) {
        return x - y;
    }

    @Override
    public Integer subtract(Object... args) {
        Integer result = zero();
        for (Object arg : args) {
            result -= (Integer) arg;
        }

        return result;
    }

    /**
     * Multiplies two numbers and returns the result
     *
     * @param x
     * @param y
     * @return
     */
    @Override
    public Integer multiply(Integer x, Integer y) {
        return x * y;
    }

    @SafeVarargs
    @Override
    public final Integer multiply(Object... args) {
        Integer result = one();
        for (Object arg : args) {
            result *= (Integer) arg;
        }
        return result;
    }

    /**
     * Changes the sign of a number and returns the result
     *
     * @param x
     * @return
     */
    @Override
    public Integer negate(Integer x) {
        return -x;
    }

    /**
     * Returns the zero value for the type of number T
     *
     * @return
     */
    @Override
    public Integer zero() {
        return ZERO;
    }

    /**
     * Returns the one value for the type T
     */
    @Override
    public Integer one() {
        return ONE;
    }

    /**
     * Returns the negative one value for the type T
     */
    @Override
    public Integer negativeOne() {
        return -ONE;
    }

    /**
     * Returns a random value for the type T, where min <= value <= max
     *
     * @param min
     * @param max
     * @return
     */
    @Override
    public Integer random(Integer min, Integer max) {
        if (rand == null) {
            rand = new Random();
        }

        return rand.nextInt((max - min) + 1) + min;
    }

    /**
     * Returns the lower bound of the number type.
     * For int, this would be –2,147,483,648
     */
    @Override
    public Integer minValue() {
        return Integer.MIN_VALUE;
    }

    /**
     * Returns the upper bound of the number type.
     * For int, this would be 2,147,483,647
     */
    @Override
    public Integer maxValue() {
        return Integer.MAX_VALUE;
    }

    /**
     * Adds two numbers and returns the result, while ensuring that no overflow gets unnoticed
     *
     * @param x
     * @param y
     */
    @Override
    public Integer safeAdd(Integer x, Integer y) throws NumberOverflowException {
        try {
            return Math.addExact(x, y);
        } catch (ArithmeticException e) {
            throw new NumberOverflowException();
        }
    }

    /**
     * Subtracts two numbers and returns the result, while ensuring that no overflow gets unnoticed
     *
     * @param x
     * @param y
     */
    @Override
    public Integer safeSubtract(Integer x, Integer y) throws NumberOverflowException {
        try {
            return Math.subtractExact(x, y);
        } catch (ArithmeticException e) {
            throw new NumberOverflowException();
        }
    }

    /**
     * Subtracts two numbers and returns the result, while ensuring that no overflow gets unnoticed
     *
     * @param x
     * @param y
     */
    @Override
    public Integer safeMultiply(Integer x, Integer y) throws NumberOverflowException {
        try {
            return Math.multiplyExact(x, y);
        } catch (ArithmeticException e) {
            throw new NumberOverflowException();
        }
    }
}