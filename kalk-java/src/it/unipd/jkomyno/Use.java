package it.unipd.jkomyno;

import it.unipd.jkomyno.linearAlgebra.*;
import it.unipd.jkomyno.numberWrapper.IntegerWrapper;
import it.unipd.jkomyno.numberWrapper.NumberWrapper;
import it.unipd.jkomyno.printer.MatrixPrinter;

import java.util.stream.Stream;

public class Use {

    public static void main(String[] args) {
        MatrixPrinter<IntegerWrapper, Integer> printer = new MatrixPrinter<IntegerWrapper, Integer>();
        IntegerWrapper numberWrapper = new IntegerWrapper();

        System.out.println("Initial dense matrix mat1:");
        AbstractMatrix<IntegerWrapper, Integer> mat1 = new DenseMatrix<>(
                numberWrapper,
                4,
                Stream.of(1, 1, 2, 2),
                Stream.of(2, 2, 4, 4),
                Stream.of(3, 3, 6, 6)
        );
        printer.print(mat1, printer.squareDelimiter);

        System.out.println("mat1 after increment(5):");
        mat1.increment(5);
        printer.print(mat1, printer.squareDelimiter);

        System.out.println("mat1 after scale(2):");
        mat1.scale(2);
        printer.print(mat1, printer.squareDelimiter);

        System.out.println("mat1 after sort():");
        mat1.sort();
        printer.print(mat1, printer.squareDelimiter);

        System.out.println("mat1 after negate():");
        mat1.negate();
        printer.print(mat1, printer.squareDelimiter);

        System.out.println("mat1 after random(-5, 5):");
        mat1.random(-5, 5);
        printer.print(mat1, printer.squareDelimiter);

        System.out.println("mat1 stats:");
        System.out.println("norm infinity " + mat1.normInfinity());
        System.out.println("max " + mat1.max());
        System.out.println("min " + mat1.min());
        System.out.println("sum " + mat1.sum());
        System.out.println("max absolute " + mat1.maxAbs());
        System.out.println("min absolute " + mat1.minAbs());
        System.out.println("sum absolute " + mat1.sumAbs());

        AbstractVector<IntegerWrapper, Integer> vec1 = (AbstractVector<IntegerWrapper, Integer>) mat1.getRowAt(2);
        System.out.print("\nmat1's 2nd row (vec1): ");
        for (VectorIteratorItem<Integer> item : vec1) {
            System.out.print(item.getValue() + " ");
        }

        System.out.println("vec1 stats:");
        System.out.println("norm infinity " + vec1.normInfinity());
        System.out.println("max " + vec1.max());
        System.out.println("min " + vec1.min());
        System.out.println("sum " + vec1.sum());
        System.out.println("max absolute " + vec1.maxAbs());
        System.out.println("min absolute " + vec1.minAbs());
        System.out.println("sum absolute " + vec1.sumAbs());

        System.out.println("\nClone of mat1, called mat2");
        AbstractMatrix<IntegerWrapper, Integer> mat2 = ((DenseMatrix<IntegerWrapper, Integer>) mat1).cloneFactory(mat1);
        printer.print(mat2, printer.squareDelimiter);

        System.out.println("\nmat1 after transpose");
        mat1.transpose();
        printer.print(mat1, printer.squareDelimiter);

        System.out.println("\nmat3 = mat1 * mat2");
        AbstractMatrix<IntegerWrapper, Integer> mat3 = mat1.multiply(mat2);
        printer.print(mat3, printer.squareDelimiter);

        System.out.println("\nmat3 after reshape to 4x3");
        mat3.reshape(4, 3);
        printer.print(mat3, printer.squareDelimiter);

        System.out.println("\nmat2 = mat3 + mat1");
        mat2 = mat3.add(mat1);
        printer.print(mat2, printer.squareDelimiter);

        System.out.println("\nmat2 = mat3 - mat1");
        mat2 = mat3.subtract(mat1);
        printer.print(mat2, printer.squareDelimiter);

        System.out.println("\nInitial square dense matrix sq1:");
        ISquareMatrix<Integer> sq1 = new DenseSquareMatrix<IntegerWrapper, Integer>(
                numberWrapper,
                Stream.of(1, 1, 5, 3),
                Stream.of(3, 5, 0, 1),
                Stream.of(1, 2, 5, 2),
                Stream.of(3, 0, 1, 1)
        );

        System.out.println("\nsq1 after fillDiagonal(2)");
        sq1.fillDiagonal(2);
        printer.print(sq1, printer.squareDelimiter);

        System.out.println("sq1 stats:");
        System.out.println("norm infinity " + sq1.normInfinity());
        System.out.println("max " + sq1.max());
        System.out.println("min " + sq1.min());
        System.out.println("sum " + sq1.sum());
        System.out.println("max absolute " + sq1.maxAbs());
        System.out.println("min absolute " + sq1.minAbs());
        System.out.println("sum absolute " + sq1.sumAbs());
        System.out.println("trace " + sq1.trace());
        System.out.println("determinant " + sq1.determinant());

        System.out.println("\nInitial diagonal matrix diag1:");
        IDiagonalMatrix<Integer> diag1 = new DenseDiagonalMatrix<IntegerWrapper, Integer>(
                numberWrapper,
                Stream.of(1, 0, 0),
                Stream.of(0, 5, 0),
                Stream.of(0, 0, 2)
        );
        printer.print(diag1, printer.squareDelimiter);

        System.out.println("diag1 stats:");
        System.out.println("norm infinity " + diag1.normInfinity());
        System.out.println("max " + diag1.max());
        System.out.println("min " + diag1.min());
        System.out.println("sum " + diag1.sum());
        System.out.println("max absolute " + diag1.maxAbs());
        System.out.println("min absolute " + diag1.minAbs());
        System.out.println("sum absolute " + diag1.sumAbs());
        System.out.println("trace " + diag1.trace());
        System.out.println("determinant " + diag1.determinant());
        System.out.println("is identity " + diag1.isIdentity());

        System.out.println("\ndiag1 after toIdentity()");
        diag1.toIdentity();
        printer.print(diag1, printer.squareDelimiter);

        System.out.println("is identity " + diag1.isIdentity());

        System.out.println("\ndiag1 after random(-5,5)");
        diag1.random(-5, 5);
        printer.print(diag1, printer.squareDelimiter);

        AbstractVector<IntegerWrapper, Integer> vec2 = (AbstractVector<IntegerWrapper, Integer>) mat1.getRowAt(2);
        System.out.print("\ndiag1 diagonal (vec2)): ");
        for (VectorIteratorItem<Integer> item : vec2) {
            System.out.print(item.getValue() + " ");
        }

        System.out.println("vec2 stats:");
        System.out.println("norm infinity " + vec2.normInfinity());
        System.out.println("max " + vec2.max());
        System.out.println("min " + vec2.min());
        System.out.println("sum " + vec2.sum());
        System.out.println("max absolute " + vec2.maxAbs());
        System.out.println("min absolute " + vec2.minAbs());
        System.out.println("sum absolute " + vec2.sumAbs());
    }
}
