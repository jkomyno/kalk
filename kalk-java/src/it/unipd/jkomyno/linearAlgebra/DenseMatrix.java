package it.unipd.jkomyno.linearAlgebra;

import it.unipd.jkomyno.numberWrapper.NumberWrapper;

import java.util.List;
import java.util.stream.Stream;

public class DenseMatrix<WRAPPER extends NumberWrapper<T>, T extends Comparable> extends AbstractDenseMatrix<WRAPPER, T> {

    public DenseMatrix(WRAPPER numberWrapper) {
        super(numberWrapper);
    }

    public DenseMatrix(WRAPPER numberWrapper, int rows, int columns) {
        super(numberWrapper, rows, columns);
    }

    public DenseMatrix(DenseMatrix<WRAPPER, T> mat) {
        super(mat);
    }

    protected DenseMatrix(DenseMatrix<WRAPPER, T> mat, int newRows, int newColumns) {
        super(mat, newRows, newColumns);
    }

    @SafeVarargs
    public DenseMatrix(WRAPPER numberWrapper, int columns, Stream<T>... rows) {
        super(numberWrapper, columns, rows);
    }

    @SafeVarargs
    protected DenseMatrix(WRAPPER numberWrapper, ListChecker checker, int columns, Stream<T>... rows) {
        super(numberWrapper, checker, columns, rows);
    }

    @SafeVarargs
    protected DenseMatrix(WRAPPER numberWrapper, ListChecker checker, int columns, List<T>... rows) {
        super(numberWrapper, checker, columns, rows);
    }

    @SafeVarargs
    public DenseMatrix(WRAPPER numberWrapper, int columns, List<T>... rows) {
        super(numberWrapper, columns, rows);
    }

    @Override
    public AbstractMatrix<WRAPPER, T> cloneFactory(IContainer<T> obj) {
        return new DenseMatrix<>((DenseMatrix<WRAPPER, T>) obj);
    }

    @Override
    public DenseMatrix<WRAPPER, T> cloneFactory(IMatrix<T> obj, int newRows, int newColumns) {
        return new DenseMatrix<>((DenseMatrix<WRAPPER, T>) obj, newRows, newColumns);
    }
}
