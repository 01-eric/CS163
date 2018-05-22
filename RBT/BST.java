import java.util.*;

public class BST {

	public static void main(String[] args) {
		/* BinarySearchTree<String> bst = new BinarySearchTree<String>();
		bst.insert("Ike");
		bst.insert("Kirby");
		bst.insert("Wolf");
		bst.insert("Lucas");
		bst.insert("Jigglypuff");
		bst.insert("Ganondorf");
		bst.insert("Captain Falcon");
		bst.insert("Ice Climbers");
		bst.insert("Olimar");
		bst.insert("Zelda");
		bst.insert("Ike");
		bst.insert("Marth");
		bst.print();
		
		RedBlackTree<String> rbt = new RedBlackTree<String>();
		rbt.insert("Ike");
		rbt.insert("Kirby");
		rbt.insert("Wolf");
		rbt.insert("Lucas");
		rbt.insert("Jigglypuff");
		rbt.insert("Ganondorf");
		rbt.insert("Captain Falcon");
		rbt.insert("Ice Climbers");
		rbt.insert("Olimar");
		rbt.insert("Zelda");
		rbt.insert("Ike");
		rbt.insert("Marth");
		rbt.print(); */
		
		RedBlackTree<Integer> rbt2 = new RedBlackTree<Integer>();
		rbt2.insert(11);
		rbt2.insert(12);
		rbt2.insert(13);
		rbt2.insert(24);
		rbt2.insert(25);
		rbt2.insert(26);
		rbt2.insert(27);
		rbt2.insert(14);
		rbt2.insert(15);
		rbt2.insert(17);
		rbt2.insert(16);
		rbt2.print();
		rbt2.delete(11);
		rbt2.delete(13);
		rbt2.print();
		rbt2.delete(12);
		rbt2.print();
		rbt2.insert(28);
		rbt2.insert(29);
		rbt2.insert(30);
		rbt2.print();
		rbt2.delete(28);
		rbt2.print();
		rbt2.delete(29);
		rbt2.delete(30);
		rbt2.print();
		rbt2.delete(27);
		rbt2.print();
		rbt2.delete(14);
		rbt2.delete(15);
		rbt2.print();
		rbt2.delete(17);
		rbt2.delete(16);
		rbt2.print();
		rbt2.delete(25);
		rbt2.delete(26);
		rbt2.print();
		rbt2.delete(24);
		rbt2.print();
		
		RedBlackTree<Integer> rbt3 = new RedBlackTree<Integer>();
		rbt3.insert(27);
		rbt3.insert(26);
		rbt3.insert(25);
		rbt3.insert(20);
		rbt3.insert(19);
		rbt3.insert(18);
		rbt3.insert(17);
		rbt3.insert(24);
		rbt3.insert(23);
		rbt3.insert(21);
		rbt3.insert(22);
		rbt3.print();
		rbt3.delete(27);
		rbt3.delete(25);
		rbt3.print();
		rbt3.delete(26);
		rbt3.print();
		rbt3.insert(16);
		rbt3.insert(15);
		rbt3.insert(14);
		rbt3.print();
		rbt3.delete(16);
		rbt3.delete(15);
		rbt3.delete(14);
		rbt3.delete(17);
		rbt3.print();
		rbt3.delete(24);
		rbt3.delete(23);
		rbt3.print();
		rbt3.delete(21);
		rbt3.delete(22);
		rbt3.print();
		rbt3.delete(19);
		rbt3.delete(20);
		rbt3.delete(18);
		rbt3.print();
		/* Scanner scanner = new Scanner(System.in);
		RedBlackTree<Integer> rbt = new RedBlackTree<Integer>();
		while (true) {
			rbt.insert(Integer.parseInt(scanner.nextLine()));
			rbt.print();
		} */
	}
}

class BinaryNode<T> {
	
	private T value;
	private BinaryNode<T> left, right, parent;
	
	BinaryNode(T value) {
		left = right = null;
		setValue(value);
	}
	
	void setValue(T value) {
		this.value = value;
	}
	
	void setLeft(BinaryNode<T> left) {
		this.left = left;
	}
	
	void setParent(BinaryNode<T> parent) {
		this.parent = parent;
	}
	
	void setRight(BinaryNode<T> right) {
		this.right = right;
	}
	
	T getValue() {
		return value;
	}
	
	BinaryNode<T> getLeft() {
		return left;
	}
	
	BinaryNode<T> getParent() {
		return parent;
	}
	
	BinaryNode<T> getRight() {
		return right;
	}
	
}

class BinarySearchTree<T extends Comparable<T>> {
	
	/*private*/ BinaryNode<T> root;
	
	BinarySearchTree() {
		root = null;
	}
	
	// deletes occurrence of key with least depth
	public boolean delete(T key) {
		BinaryNode<T> toDelete = rcSearch(root, key);
		if (toDelete == null) return false; // key not found
		if (toDelete.getLeft() != null && toDelete.getRight() != null) { // two children, find successor in right subtree, copy fields of successor into toDelete
			// then delete successor after values are copied because the successor has at most one child
			BinaryNode<T> successor = toDelete.getRight();
			while (successor.getLeft() != null) successor = successor.getLeft(); // move to leftmost of right subtree
			toDelete.setValue(successor.getValue()); // copy value of successor over
			toDelete = successor; // sets successor to be deleted in next few lines
		} if (toDelete.getLeft() == null && toDelete.getRight() == null) replaceNode(toDelete, null); // no children
		else if (toDelete.getLeft() == null) replaceNode(toDelete, toDelete.getRight()); // left child exists
		else if (toDelete.getRight() == null) replaceNode(toDelete, toDelete.getLeft()); // right child exists
		return true;
	}
	
	public BinaryNode<T> insert(T element) {
		// assignment of root because the assignment in rcInsert modifies wrong pointer
		BinaryNode<T> newNode = new BinaryNode<T>(element);
		root = rcInsert(root, newNode);
		return newNode; // used in Red Black Tree when needed to refer back to child for balancing
	}
	
	public void print() {
		if (root == null) System.out.println("Tree is empty.");
		else rcPrint(root, "", false);
	}
	
	private BinaryNode<T> rcSearch(BinaryNode<T> node, T key) {
		if (node == null || key.equals(node.getValue())) return node;
		else if (key.compareTo(node.getValue()) < 0) return rcSearch(node.getLeft(), key);
		else return rcSearch(node.getRight(), key);
	}
	
	private BinaryNode<T> rcInsert(BinaryNode<T> node, BinaryNode<T> element) {
		if (node == null) node = element; // if node doesn't exist return the new node element
		else if (element.getValue().compareTo(node.getValue()) <= 0) {
			node.setLeft(rcInsert(node.getLeft(), element));
			node.getLeft().setParent(node);
		} else {
			node.setRight(rcInsert(node.getRight(), element));
			node.getRight().setParent(node);
		} return node;
	}
	
	private void rcPrint(BinaryNode<T> node, String tabstop, boolean branch) {
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
	
	private void replaceNode(BinaryNode<T> toReplace, BinaryNode<T> newNode) { // attach subtree of newNode in place of toReplace
		if (toReplace.getParent() == null) root = newNode; // if no parent, replace the root with newNode
		else if (toReplace == toReplace.getParent().getLeft()) toReplace.getParent().setLeft(newNode); // if left child of parent, replace left child of parent with newNode
		else toReplace.getParent().setRight(newNode); // if right child of parent, replace right child of parent with newNode
		if (newNode != null) newNode.setParent(toReplace.getParent()); // newNode's parent is now the parent of the replaced node
	}
	
}

class RedBlackNode<T extends Comparable<T>>  {
	
	private T value;
	private RedBlackNode<T> left, right, parent;
	public static enum Color {NULL, RED, BLACK};
	private Color color;
	
	RedBlackNode() {
		this(null, Color.NULL);
	}
	
	RedBlackNode(T value, Color color) {
		setValue(value);
		setColor(color);
	}
	
	void setValue(T value) {
		this.value = value;
	}
	
	void setLeft(RedBlackNode<T> left) {
		this.left = left;
	}
	
	void setParent(RedBlackNode<T> parent) {
		this.parent = parent;
	}
	
	void setRight(RedBlackNode<T> right) {
		this.right = right;
	}
	
	T getValue() {
		return value;
	}
	
	RedBlackNode<T> getLeft() {
		return left;
	}
	
	RedBlackNode<T> getRight() {
		return right;
	}
	
	RedBlackNode<T> getParent() {
		return parent;
	}
	
	RedBlackNode<T> getGrandparent() { // returns null if no parent or no grandparent
		if (getParent() == null) return null;
		else return getParent().getParent();
	}
	
	RedBlackNode<T> getSibling() { // returns null if no parent or no sibling
		if (getParent() == null) return null;
		else if (this == getParent().getLeft()) return getParent().getRight();
		else return getParent().getLeft();
	}
	
	// returns null if no grandparent, but if grandparent exists uncle must exist because tree is balanced
	RedBlackNode<T> getUncle() {
		if (getGrandparent() == null) return null;
		else return getParent().getSibling();
	}
	
	public void setColor(Color color) {
		this.color = color;
	}
	
	public boolean isRed() {
		return color == Color.RED;
	}
	
}

class RedBlackTree<T extends Comparable<T>> {
	
	private RedBlackNode<T> root;
	
	RedBlackTree() {
		root = null;
	}
	

	public boolean contains(T key) {
		return rcSearch(root, key).getValue() != null;
	}
	
	public boolean delete(T key) {
		RedBlackNode<T> toDelete = rcSearch(root, key);
		if (toDelete.getValue() == null) return false; // key not in tree
		if (toDelete.getLeft().getValue() != null && toDelete.getRight().getValue() != null) { // two children, find successor in right subtree, copy fields of successor into toDelete
			// then delete successor after values are copied because the successor has at most one child
			RedBlackNode<T> successor = toDelete.getRight(); // find successor as leftmost node of right subtree
			while (successor.getLeft().getValue() != null) successor = successor.getLeft();
			toDelete.setValue(successor.getValue()); // copy just the value of successor
			toDelete = successor; // set successor to be deleted with upcoming code since it has 1 or 0 non-leaf children
		} if (toDelete.isRed()) replaceNode(toDelete, toDelete.getLeft()); // replace with leaf node, in C++ should deallocate right leaf node
		else if (toDelete.getLeft().getValue() != null) { // black node with red left child
			toDelete.getLeft().setColor(RedBlackNode.Color.BLACK);
			replaceNode(toDelete, toDelete.getLeft());
		} else if (toDelete.getRight().getValue() != null) { // black node with red right child
			toDelete.getRight().setColor(RedBlackNode.Color.BLACK);
			replaceNode(toDelete, toDelete.getRight());
		} else { // black node with no children
			RedBlackNode<T> child = toDelete.getLeft();
			replaceNode(toDelete, child); // deallocate right node in c++
			repairTreeDelete(child);
			if (root.getValue() == null) root = null; // deallocate null node in c++
		} return true; // successfully deleted
	}
	
	public RedBlackNode<T> insert(T element) {
		// assignment of root because the assignment in rcInsert modifies wrong pointer
		RedBlackNode<T> newNode = new RedBlackNode<T>(element, RedBlackNode.Color.RED); // cannot change black length of tree
		root = rcInsert(root, newNode);
		newNode.setLeft(new RedBlackNode<T>());
		newNode.getLeft().setParent(newNode);
		newNode.setRight(new RedBlackNode<T>());
		newNode.getRight().setParent(newNode);
		repairTreeInsert(newNode);
		return newNode;
	}
	
	public void print() {
		if (root == null) System.out.println("Tree is empty.");
		else rcPrint(root, "", false);
	}
	
	private RedBlackNode<T> rcSearch(RedBlackNode<T> node, T key) {
		if (node.getValue() == null || key.equals(node.getValue())) return node;
		else if (key.compareTo(node.getValue()) < 0) return rcSearch(node.getLeft(), key);
		else return rcSearch(node.getRight(), key);
	}
	
	private RedBlackNode<T> rcInsert(RedBlackNode<T> node, RedBlackNode<T> element) {
		if (node == null || node.getValue() == null) node = element; // if node doesn't exist return the new node element
		else if (element.getValue().compareTo(node.getValue()) <= 0) {
			node.setLeft(rcInsert(node.getLeft(), element));
			node.getLeft().setParent(node);
		} else {
			node.setRight(rcInsert(node.getRight(), element));
			node.getRight().setParent(node);
		} return node;
	}
	
	private void rcPrint(RedBlackNode<T> node, String tabstop, boolean branch) {
		if (node.getValue() == null) { // when printing out just left node and right node contains null
			System.out.println(tabstop + "|   ");
			return;
		} else System.out.println(tabstop + (branch ? "├── " : "└── ") + node.getValue() + "(" + (node.isRed() ? "R" : "B") + ")");
		if (node.getLeft().getValue() == null && node.getRight().getValue() != null) rcPrint(node.getRight(), tabstop + (branch ? "|   " : "    "), false);
		else if (node.getLeft().getValue() != null) {
			rcPrint(node.getRight(), tabstop + (branch ? "|   " : "    "), true);
			rcPrint(node.getLeft(), tabstop + (branch ? "|   " : "    "), false);
		}
	}
	
	private void repairTreeDelete(RedBlackNode<T> node) { // subtree of "node" has reduced black length. goal is to balance this reduced length
		if (node.getParent() == null) return; // case 1: repair called on root, no need because that means entire tree black depth reduced
		// case 2: sibling is red (thus parent is black)
		if (node.getSibling().isRed()) { // transfer red from sibling to parent, rotate parent towards node's side
			// node still has reduced black height but now has black sibling which can be resolved with next case
			node.getParent().setColor(RedBlackNode.Color.RED);
			node.getSibling().setColor(RedBlackNode.Color.BLACK);
			if (node == node.getParent().getLeft()) rotateLeft(node.getParent());
			else rotateRight(node.getParent());
		} // case 3/4: sibling is black, both children are black
		if (!node.getSibling().getLeft().isRed() && !node.getSibling().getRight().isRed()) {
			if (!node.getParent().isRed()) { // case 3: parent is black
				node.getSibling().setColor(RedBlackNode.Color.RED); // now all paths from parent are reduced in black length
				repairTreeDelete(node.getParent()); // thus recur on parent
			} else { // case 4: parent is red
				node.getParent().setColor(RedBlackNode.Color.BLACK); // exchange colors of sibling and parent
				node.getSibling().setColor(RedBlackNode.Color.RED); // increases black length of path to current node w/o changing others, thus balanced
			}
		} else { 
			// case 5: right-left/left-right case, sibling on right and red child on left only, or sibling on left and red child on right only
			if (node == node.getParent().getLeft() && !node.getSibling().getRight().isRed() && node.getSibling().getLeft().isRed()) { // right left
				node.getSibling().setColor(RedBlackNode.Color.RED); // repaint sibling as red
				node.getSibling().getLeft().setColor(RedBlackNode.Color.BLACK); // repaint sibling's red child as black
				rotateRight(node.getSibling()); // rotate now-red sibling to the right so it turns into right-right case
			} else if (node == node.getParent().getRight() && !node.getSibling().getLeft().isRed() && node.getSibling().getRight().isRed()) {
				node.getSibling().setColor(RedBlackNode.Color.RED); // same idea as right-left case
				node.getSibling().getRight().setColor(RedBlackNode.Color.BLACK);
				rotateLeft(node.getSibling());
			} // case 6: right-right/left-left case, sibling on right and right child is red, or sibling on left and left child is red
			node.getSibling().setColor(node.getParent().isRed() ? RedBlackNode.Color.RED : RedBlackNode.Color.BLACK); // sibling and parent swap colors
			node.getParent().setColor(RedBlackNode.Color.BLACK); // sibling is black since code reached here
			if (node == node.getParent().getLeft()) { // right right
				node.getSibling().getRight().setColor(RedBlackNode.Color.BLACK); // color red child to be black
				rotateLeft(node.getParent()); // rotate black parent towards node, so node gains black length. now balanced.
			} else { // left left
				node.getSibling().getLeft().setColor(RedBlackNode.Color.BLACK);
				rotateRight(node.getParent());
			}
		}
	}
	
	private void repairTreeInsert(RedBlackNode<T> node) { // fix violated red black tree properties
		if (node.getParent() == null) node.setColor(RedBlackNode.Color.BLACK); // root is always black
		else if (node.getParent().isRed()) { // if parent is not black then must repair tree, also uncle must exist because parent is not root
			if (node.getUncle().isRed()) { // swap colors of grandparent and parent, black length maintained
				node.getParent().setColor(RedBlackNode.Color.BLACK);
				node.getUncle().setColor(RedBlackNode.Color.BLACK);
				node.getGrandparent().setColor(RedBlackNode.Color.RED); // grandparent must have been black
				repairTreeInsert(node.getGrandparent()); // recursively repair tree from grandparent because now it is red
			} else { // uncle is black
				if (node == node.getGrandparent().getLeft().getRight()) { // rotate into left left case
					rotateLeft(node.getParent()); // node takes parent position and parent takes left child position
					node = node.getLeft(); // left left case on old parent (now left child)
				} else if (node == node.getGrandparent().getRight().getLeft()) { // rotate into right right case
					rotateRight(node.getParent()); // node takes parent position and parent takes right child position
					node = node.getRight(); // right right case on old parent (now right child)
				} RedBlackNode<T> grandparent = node.getGrandparent(); // need to recolor grandparent later
				if (node == node.getParent().getLeft()) rotateRight(grandparent); // step 2: left left case
				else rotateLeft(grandparent); // step 2: right right case
				node.getParent().setColor(RedBlackNode.Color.BLACK); // parent has rotated into grandparent position, recolor to black
				grandparent.setColor(RedBlackNode.Color.RED); // grandparent has rotated into uncle position, recolor to red
				// black length maintained because previously to get to node and parent (red) must pass through grandparent (black)
				// now to get to grandparent or node (red) must pass through parent (black)
			}
		}
	}
	
	private void replaceNode(RedBlackNode<T> toReplace, RedBlackNode<T> newNode) { // attach subtree of newNode in place of toReplace
		if (toReplace.getParent() == null) root = newNode; // if no parent, replace the root with newNode
		else if (toReplace == toReplace.getParent().getLeft()) toReplace.getParent().setLeft(newNode); // if left child of parent, replace left child of parent with newNode
		else toReplace.getParent().setRight(newNode); // if right child of parent, replace right child of parent with newNode
		if (newNode != null) newNode.setParent(toReplace.getParent()); // newNode's parent is now the parent of the replaced node
	}
	
	// node.right takes node's position, node moves left to become left child of node.right
	// node.right's left child becomes node's right child
	private void rotateLeft(RedBlackNode<T> node) {
		RedBlackNode<T> rightNode = node.getRight();
		node.setRight(rightNode.getLeft());
		node.getRight().setParent(node);
		rightNode.setLeft(node);
		rightNode.setParent(node.getParent());
		node.setParent(rightNode);
		if (rightNode.getParent() != null) { // if rightNode did not take the root position set parent's child to rightNode
			if (node == rightNode.getParent().getLeft()) rightNode.getParent().setLeft(rightNode);
			else rightNode.getParent().setRight(rightNode);
		} else root = rightNode; // otherwise rightNode is now root
	}
	
	private void rotateRight(RedBlackNode<T> node) {
		RedBlackNode<T> leftNode = node.getLeft();
		node.setLeft(leftNode.getRight());
		node.getLeft().setParent(node);
		leftNode.setRight(node);
		leftNode.setParent(node.getParent());
		node.setParent(leftNode);
		if (leftNode.getParent() != null) {
			if (node == leftNode.getParent().getLeft()) leftNode.getParent().setLeft(leftNode);
			else leftNode.getParent().setRight(leftNode);
		} else root = leftNode;
	}
	
// 16 17 15 14 27 26 25 24 13 2 1
/* 
11
12
13
24
25
26
27
14
15
17
16
 */
	
}
