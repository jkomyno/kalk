package it.unipd.jkomyno.linearAlgebra.utils;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;

public class ListUtils {
    private ListUtils() {

    }

    public static <U> List<U> initArraySize(int size, U scalar) {
        return new ArrayList<>(Collections.nCopies(size, scalar));
    }

    public static <U> List<U> copyList(List<U> list) {
        return list.stream().collect(Collectors.toList());
    }

    public static <U extends Comparable> void sortList(List<U> list) {
        Collections.sort(list);
    }
}
