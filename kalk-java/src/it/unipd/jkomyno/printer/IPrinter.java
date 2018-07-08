package it.unipd.jkomyno.printer;

import it.unipd.jkomyno.linearAlgebra.AbstractMatrix;
import it.unipd.jkomyno.linearAlgebra.IMatrix;
import it.unipd.jkomyno.numberWrapper.NumberWrapper;

import java.util.function.Consumer;

public interface IPrinter<WRAPPER extends NumberWrapper<T>, T extends Comparable, U> {
    void print(IMatrix<T> matrix, Consumer<U> printer);
}