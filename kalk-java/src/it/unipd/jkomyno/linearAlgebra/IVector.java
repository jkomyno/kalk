package it.unipd.jkomyno.linearAlgebra;

public interface IVector<T> extends IContainer<T>, IVectorIterator<T> {
    IVector<T> cloneFactory(IVector<T> obj, int newLength);
}
