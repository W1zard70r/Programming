class TreapNode:
    def __init__(self, key, priority, link):
        self.key = key  # Ключ для BST
        self.priority = priority  # Приоритет для Heap
        self.link = link # Полный путь до файла
        self.left = None  # Левое поддерево
        self.right = None  # Правое поддерево

class Treap:
    def __init__(self):
        self.root = None  # Корень Treap

def split(root, key):
    """
    Разделяет Treap на два поддерева по ключу.
    """
    if root is None:
        return (None, None)
    if root.key <= key:
        left, right = split(root.right, key)
        root.right = left
        return (root, right)
    else:
        left, right = split(root.left, key)
        root.left = right
        return (left, root)

def merge(left, right):
    """
    Объединяет два Treap в один.
    """
    if left is None:
        return right
    if right is None:
        return left
    if left.priority > right.priority:
        left.right = merge(left.right, right)
        return left
    else:
        right.left = merge(left, right.left)
        return right

def insert(treap, key, priority, link):
    
    """
    Вставляет новый узел в Treap.
    Если приоритет не указан, он генерируется случайно.
    """

    new_node = TreapNode(key, priority, link)

    if treap.root is None:
        treap.root = new_node
        return
    
    left, right = split(treap.root, key)
    treap.root = merge(merge(left, new_node), right)

def search_treap(treap, key):
    """
    Поиск узла по ключу.
    Возвращает True, если ключ найден, иначе False.
    """
    return _search(treap.root, key)

def _search(root, key):
    """
    Вспомогательная функция для поиска.
    """
    if root is None:
        return None
    if root.key == key:
        return root
    if key < root.key:
        return _search(root.left, key)
    else:
        return _search(root.right, key)

def inorder(treap):
    """
    Обход дерева в порядке in-order (для вывода элементов).
    """
    _inorder(treap.root)

def _inorder(root):
    """
    Вспомогательная функция для обхода in-order.
    """
    if root:
        _inorder(root.left)
        print(f"Key: {root.key}, Priority: {root.priority}")
        _inorder(root.right)

def print_tree(node, prefix="", is_left=True):
    """
    Рекурсивно выводит дерево в консоль.
    :param node: Текущий узел.
    :param prefix: Префикс для отступов.
    :param is_left: Флаг, указывающий, является ли узел левым потомком.
    """
    if node is not None:
        print_tree(node.right, prefix + ("│   " if is_left else "    "), False)
        print(prefix + ("└── " if is_left else "┌── ") + f"Key: {node.key}, Priority: {node.priority}")
        print_tree(node.left, prefix + ("    " if is_left else "│   "), True)

