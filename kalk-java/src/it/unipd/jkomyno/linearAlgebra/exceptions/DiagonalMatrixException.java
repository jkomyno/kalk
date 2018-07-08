package it.unipd.jkomyno.linearAlgebra.exceptions;

public class DiagonalMatrixException extends RuntimeException {
    public DiagonalMatrixException() {
        super("The provided data violates the diagonal matrix property");
    }
}
