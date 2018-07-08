package it.unipd.jkomyno.linearAlgebra;

import it.unipd.jkomyno.linearAlgebra.exceptions.MatrixStructureException;
import it.unipd.jkomyno.linearAlgebra.exceptions.IllegalDimensionsException;
import it.unipd.jkomyno.numberWrapper.NumberWrapper;

import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

import static it.unipd.jkomyno.linearAlgebra.utils.ListUtils.*;

interface ListChecker<T> {
    void check(List<List<T>> stream);
}

public abstract class AbstractDenseMatrix<WRAPPER extends NumberWrapper<T>, T extends Comparable> extends AbstractMatrix<WRAPPER, T> {
    private List<T> data;

    public AbstractDenseMatrix(WRAPPER numberWrapper, int rows, int columns) {
        super(numberWrapper, rows, columns);
        this.data = initArraySize(rows * columns, numberWrapper.zero());
    }

    public AbstractDenseMatrix(WRAPPER numberWrapper) {
        super(numberWrapper);
    }

    @SafeVarargs
    protected AbstractDenseMatrix(WRAPPER numberWrapper, int columns, Stream<T>... rows) {
        this(numberWrapper, (ListChecker<T>) stream -> {}, columns, rows);
    }

    @SafeVarargs
    protected AbstractDenseMatrix(WRAPPER numberWrapper, ListChecker checker, int columns, Stream<T>... rows) {
        /**
         * This constructor allows to populate the data for the matrix via a variadic number of numeric streams.
         * This allows the following declaration:
         *   new DenseSquareMatrix<>(
         *     numberWrapper,
         *     Stream.of(1, 1, 2),
         *     Stream.of(3, 5, 6),
         *     Stream.of(2, 2, 1)
         *   );
         * which is as similar as possible to Python's numpy equivalent declaration:
         *   np.array(([1, 1, 2], [3, 5, 6], [2, 2, 1]))
         *
         * Since a stream is readable only once, in order to validate it (the minimum requirement is that
         * each row must have the same amount of columns, but further checks may be provided by children of this class)
         * I must first save it in list of lists of T.
         * After having executed the sanity check, I can flatten that list in order to fill the internal data row-wise.
         * The functional approach implemented below is the clearest and most elegant solution that came to my mind.
         */
        super(numberWrapper, rows.length, columns);
        List<List<T>> streamToListOfLists = Stream
                .of(rows)
                .sequential()
                .map(row -> row.collect(Collectors.toList()))
                .collect(Collectors.toList());
        checker.check(streamToListOfLists); // this throws if the check gave bad results
        this.data = streamToListOfLists
                .stream()
                .sequential()
                .flatMap(List::stream)
                .collect(Collectors.toList());
    }

    @SafeVarargs
    public AbstractDenseMatrix(WRAPPER numberWrapper, int columns, List<T>... rows) {
        this(numberWrapper, (ListChecker<T>) rowList -> checkIsValidMatrix(rowList), columns, rows);
    }

    @SafeVarargs
    public AbstractDenseMatrix(WRAPPER numberWrapper, ListChecker checker, int columns, List<T>... rows) {
        super(numberWrapper, rows.length, columns);
        List<List<T>> streamToListOfLists = Stream
                .of(rows)
                .sequential()
                .collect(Collectors.toList());
        checker.check(streamToListOfLists);
        this.data = streamToListOfLists
                .stream()
                .flatMap(List::stream)
                .collect(Collectors.toList());
    }

    public AbstractDenseMatrix(AbstractDenseMatrix<WRAPPER, T> mat) {
        super(mat);
        this.data = copyList(mat.data);
    }

    protected AbstractDenseMatrix(AbstractDenseMatrix<WRAPPER, T> mat, int newRows, int newColumns) {
        super(mat, newRows, newColumns);
        this.data = initArraySize(newRows * newColumns, numberWrapper.zero());
    }

    /**
     * Returns the number of entries in the storage
     *
     * @return
     */
    @Override
    public int getDataSize() {
        return data.size();
    }

    /**
     * Returns true iff the container is equal to the current object
     *
     * @param container
     */
    @Override
    public boolean equals(IContainer<T> container) {
        if (!(container instanceof AbstractDenseMatrix)) {
            return false;
        }

        AbstractDenseMatrix<WRAPPER, T> mat = (AbstractDenseMatrix<WRAPPER, T>) container;
        return super.equals(mat) && data.equals(mat.data);
    }

    /**
     * Sets value of the current container at a specific index
     *
     * @param index
     * @param value
     */
    @Override
    public void setAt(int index, T value) {
        data.set(index, value);
    }

    /**
     * Retrieves the value of the current container at a specific index
     *
     * @param index
     * @return
     */
    @Override
    public T getAt(int index) {
        return data.get(index);
    }

    /**
     * Retrieves every internal value of the container as an ordered list
     *
     * @return
     */
    @Override
    public List<T> getData() {
        return data;
    }

    /**
     * Sorts the elements in ascending order
     */
    @Override
    public void sort() {
        sortList(data);
    }

    /**
     * Sets the new value of the current matrix at the specific getRow and getColumn
     *
     * @param row
     * @param column
     * @param value
     */
    @Override
    public void setAt(int row, int column, T value) {
        setAt(getIndex(row, column), value);
    }

    /**
     * Returns the value of the current matrix at the specific getRow and getColumn
     *
     * @param row
     * @param column
     */
    @Override
    public T getAt(int row, int column) {
        return getAt(getIndex(row, column));
    }

    /**
     * Reshapes the current matrix mutating it
     *
     * @param newRows
     * @param newColumns
     */
    @Override
    public void reshape(int newRows, int newColumns) {
        super.reshape(newRows, newColumns);
        int newSize = newRows * newColumns;
        int diff = newSize - getDataSize();
        if (diff > 0) {
            /**
             * I have to store more entries than earlier, so I should expand my container list
             */
            data.addAll(initArraySize(diff, numberWrapper.zero()));
        } else {
            /**
             * diff is < 0, since the (diff == 0) case is already handled by parent method.
             * I have to clear the tail of the list
             */
            // diff < 0, since diff == 0 case is already handled by parent method
            data.subList(data.size() + diff, data.size()).clear();
        }
        setRows(newRows);
        setColumns(newColumns);

        AbstractMatrix<WRAPPER, T> helper = (AbstractMatrix<WRAPPER, T>) cloneFactory(this);
        T valueAt;
        for (int row = 1; row <= newRows; row++) {
            for (int column = 1; column <= newColumns; column++) {
                if (column > getColumns() || row > getRows()) {
                    valueAt = numberWrapper.zero();
                } else {
                    valueAt = helper.getAt(row, column);
                }
                setAt(row, column, valueAt);
            }
        }
    }

    @Override
    public IVector<T> getRowAt(int rowIndex) {
        int listStart = getIndex(rowIndex, 1);
        int listEnd = getIndex(rowIndex, getColumns() + 1);
        List<T> rawData = data.subList(listStart, listEnd);
        return new DenseVector<>(numberWrapper, rawData);
    }

    /**
     * Reshapes the current matrix mutating it
     *
     * @param newRows
     * @param newColumns
     * @param xStart
     * @param yStart
     * @param padValue
     */
    @Override
    public void reshape(int newRows, int newColumns, int xStart, int yStart, T padValue) throws IllegalDimensionsException {
        super.reshape(newRows, newColumns, xStart, yStart, padValue);
    }

    protected int getIndex(int row, int column) {
        return getIndex(row, column, getColumns());
    }

    private static <T> void checkIsValidMatrix(List<List<T>> rows) {
        // each row must have the same amount of columns

        boolean eachRowHasTheSameAmountOfColumns = IntStream
                .range(0, rows.size()) // [0, rows.size())
                .filter(i -> i == 0 || rows.get(i - 1).size() == rows.get(i).size())
                .count() == rows.size() - 1;

        if (!eachRowHasTheSameAmountOfColumns) {
            throw new MatrixStructureException();
        }
    }
}
