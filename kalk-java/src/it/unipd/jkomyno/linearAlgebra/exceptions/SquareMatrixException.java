package it.unipd.jkomyno.linearAlgebra.exceptions;

public class SquareMatrixException extends RuntimeException {
    public SquareMatrixException() {
        super("Each row should have the same size as each column");
    }
}
