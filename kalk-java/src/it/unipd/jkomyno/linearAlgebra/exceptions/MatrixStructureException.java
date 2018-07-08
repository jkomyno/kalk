package it.unipd.jkomyno.linearAlgebra.exceptions;

public class MatrixStructureException extends RuntimeException {
    public MatrixStructureException() {
        super("Each row must have the same amount of columns");
    }
}
