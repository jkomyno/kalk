package it.unipd.jkomyno.linearAlgebra.exceptions;

public class NumberOverflowException extends ArithmeticException {
    public NumberOverflowException() {
        super("Number overflow");
    }
}
