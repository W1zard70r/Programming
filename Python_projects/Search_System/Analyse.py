import os
import xml.etree.ElementTree as ET

from Treap import Treap, insert, print_tree

def analyse(file_location: str) -> str: 

    #содание списка кортежей [(путь, вес файла)...]
    all_items = os.listdir(file_location)
    list_of_all_files = get_files(file_location)

    #Создание Treap 
    treap = Treap()
    for link, weight in list_of_all_files:
        file_name = os.path.basename(link)
        insert(treap, file_name, weight, link)

    #вывод структуры дерева 
    #print_tree(treap.root)

    # Сериализация в XML
    root_xml = ET.Element("treap")
    treap_to_xml(treap.root, root_xml)
    tree = ET.ElementTree(root_xml)

    # Получаем текущую директорию программы
    current_directory = os.path.dirname(os.path.abspath(__file__))
    
    # Создаем путь к папке
    folder_path = os.path.join(current_directory, 'analysed_folders')
    
    # Создаем папку, если она не существует
    if not os.path.exists(folder_path):
        os.makedirs(folder_path)
    
    # Создаём файл XML в этой папке
    xml_file_path = os.path.join(folder_path, f"{os.path.basename(file_location)}.xml")
    tree.write(xml_file_path, encoding="utf-8", xml_declaration=True)

    return current_directory + f'\\analysed_folders\\{os.path.basename(file_location)}.xml'

#рекурсивный обход всех папок и получение всех файлов и путей к ним
def get_files(file_location: str) -> list[tuple[str, int]]:

    all_items = os.listdir(file_location)
    result = list()
    
    #обход содержимого папки
    for item in all_items:
    
        item = os.path.join(file_location, item)
    
        #вход во вложенную папку
        if os.path.isdir(item):
            result.extend(get_files(item))
    
        else:
            result.append((item, os.path.getsize(item)))
    
    return result

#преобразует Treap в формат XML
def treap_to_xml(node, parent):

    if node is None:
        return

    # Создаем элемент для текущего узла
    node_element = ET.SubElement(parent, "node", key=node.key, priority=str(node.priority), link=node.link)

    # Добавляем левое поддерево (если существует)
    if node.left is not None:
        left_element = ET.SubElement(node_element, "left")
        treap_to_xml(node.left, left_element)

    # Добавляем правое поддерево (если существует)
    if node.right is not None:
        right_element = ET.SubElement(node_element, "right")
        treap_to_xml(node.right, right_element)
