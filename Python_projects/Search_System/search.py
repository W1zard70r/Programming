from sys import stdin, stdout, stderr

import argparse

from Analyse import analyse
from Finder import search
from Treap import TreapNode

def main():
    # Настройка парсера аргументов
    parser = argparse.ArgumentParser(description="A program to perform analysis.")
    parser.add_argument("command", help="analyse / search", default= None)
    parser.add_argument("location", help="file / folder", default= None)
    args = parser.parse_args()

    # Проверка аргумента и вызов нужной функции
    if args.command == 'analyse':
        if args.location != None:
            xml_file = analyse(args.location)
            stdout.write(f'There\'s analyse in {xml_file}')
        else:
            stderr.write("Location is not correct")
    elif args.command == 'search':
        if args.location != None:
            target_file = stdin.readline().rstrip()
            if target_file:
                result = search(args.location, target_file)
                if result:
                    stdout.write(result.link)
                else:
                    stdout.write("There's no file in directory")
            else:
                stdout.write("There's no file to search")
        else:
            stderr.write("Location is not correct")
    else:
        print("Unknown command. Please use 'analyse / search'.")



if __name__ == "__main__":
    main()