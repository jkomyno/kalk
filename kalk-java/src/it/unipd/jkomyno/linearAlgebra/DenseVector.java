package it.unipd.jkomyno.linearAlgebra;

import it.unipd.jkomyno.numberWrapper.NumberWrapper;

import java.util.List;
import java.util.stream.Stream;

public class DenseVector<WRAPPER extends NumberWrapper<T>, T extends Comparable> extends AbstractDenseVector<WRAPPER, T> {
    public DenseVector(WRAPPER numberWrapper) {
        super(numberWrapper);
    }

    public DenseVector(WRAPPER numberWrapper, int length) {
        super(numberWrapper, length);
    }

    public DenseVector(DenseVector<WRAPPER, T> vec) {
        super(vec);
    }

    public DenseVector(DenseVector<WRAPPER, T> a, int newLength) {
        super(a, newLength);
    }

    public DenseVector(WRAPPER numberWrapper, Stream<T> vector) {
        super(numberWrapper, vector);
    }

    public DenseVector(WRAPPER numberWrapper, List<T> vector) {
        super(numberWrapper, vector);
    }

    @Override
    public DenseVector<WRAPPER, T> cloneFactory(IContainer<T> obj) {
        return new DenseVector<>((DenseVector<WRAPPER, T>) obj);
    }

    @Override
    public DenseVector<WRAPPER, T> cloneFactory(IVector<T> obj, int newLength) {
        return new DenseVector<>((DenseVector<WRAPPER, T>) obj, newLength);
    }
}
