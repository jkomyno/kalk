package it.unipd.jkomyno.linearAlgebra.exceptions;

public class IllegalDimensionsException extends RuntimeException {
    private static final String defaultMessage = "Illegal dimensions!";

    public IllegalDimensionsException() {
        super(defaultMessage);
    }

    public IllegalDimensionsException(final String message) {
        super(defaultMessage + " " + message);
    }
}

