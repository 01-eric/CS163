#include <iostream>
#include <cstddef>

private static void rcPrint(Node<int> node, String tabstop, boolean branch) {
    if (node == null) { // when printing out only left node
        System.out.println(tabstop + "|   ");
        return;
    } else System.out.println(tabstop + (branch ? "├── " : "└── ") + node.getValue());
    if (node.getLeft() == null && node.getRight() != null) rcPrint(node.getRight(), tabstop + (branch ? "|   " : "    "), false);
    else if (node.getLeft() != null) {
        rcPrint(node.getRight(), tabstop + (branch ? "|   " : "    "), true);
        rcPrint(node.getLeft(), tabstop + (branch ? "|   " : "    "), false);
    }
}

int main() {

}


