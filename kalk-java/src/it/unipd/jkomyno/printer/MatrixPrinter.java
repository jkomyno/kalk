package it.unipd.jkomyno.printer;

import it.unipd.jkomyno.linearAlgebra.AbstractMatrix;
import it.unipd.jkomyno.linearAlgebra.IMatrix;
import it.unipd.jkomyno.linearAlgebra.IVector;
import it.unipd.jkomyno.numberWrapper.NumberWrapper;

import java.util.List;
import java.util.function.Consumer;
import java.util.stream.IntStream;

public class MatrixPrinter<WRAPPER extends NumberWrapper<T>, T extends Comparable> implements IPrinter<WRAPPER, T, List<T>> {
    public Consumer<List<T>> squareDelimiter = (row) -> {
        System.out.print("[");
        row.forEach(el -> System.out.print("\t" + el + "\t"));
        System.out.println("]");
    };

    @Override
    public void print(IMatrix<T> mat, Consumer<List<T>> printer) {
        for (int i = 1; i <= mat.getRows(); i++) {
            IVector<T> row = mat.getRowAt(i);
            List<T> rawData = row.getData();
            printer.accept(rawData);
        }

        System.out.println();
    }
}
