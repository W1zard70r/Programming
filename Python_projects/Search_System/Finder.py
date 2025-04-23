from Treap import TreapNode, Treap, search_treap, print_tree
import xml.etree.ElementTree as ET

def search(treap_file: str, target_file: str):
    #получение дерева из xml
    treap = deserialize_treap_from_xml(treap_file)
    
    #вывод дерева
    #print_tree(treap.root)

    # Поиск файла в Treap
    result = search_treap(treap, target_file)

    return result

# Проходимся по XML, делаем узлы и связываем их
def deserialize_node(node_element):

    if node_element is None:
        return None
    
    # Извлекаем атрибуты узла
    key = node_element.get("key")
    priority = int(node_element.get("priority"))
    link = node_element.get("link")

    # Создаем узел
    new_node = TreapNode(key, priority, link)
    
    # Восстанавливаем левое поддерево
    left_element = node_element.find("left")
    if left_element is not None and len(left_element) > 0:
        new_node.left = deserialize_node(left_element[0])
    
    # Восстанавливаем правое поддерево
    right_element = node_element.find("right")
    if right_element is not None and len(right_element) > 0:
        new_node.right = deserialize_node(right_element[0])
    
    return new_node
    
# Получем полноценное дерево Treap
def deserialize_treap_from_xml(file_path):

    # читаем XML и получаем корень, к которому позже всё нужное привяжем
    tree = ET.parse(file_path)
    root_element = tree.getroot().find("node")
    
    # создаем класс дерева и присвиваем его корню связанные node
    treap = Treap()
    treap.root = deserialize_node(root_element)

    return treap