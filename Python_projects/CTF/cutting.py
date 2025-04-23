import cv2
import os

def crop_image_to_tiles(input_image_path, output_folder, tile_size=28):
    """
    Обрезает изображение на множество маленьких изображений заданного размера.
    
    Параметры:
        input_image_path (str): Путь к входному изображению.
        output_folder (str): Папка для сохранения маленьких изображений.
        tile_size (int): Размер маленьких изображений (по умолчанию 28x28).
    """
    # Создаем папку для выходных изображений, если её нет
    os.makedirs(output_folder, exist_ok=True)
    
    # Загружаем изображение
    img = cv2.imread(input_image_path)
    if img is None:
        print(f"Ошибка: Не удалось загрузить изображение {input_image_path}")
        return
    
    # Получаем размеры изображения
    height, width = img.shape[:2]
    
    # Вычисляем количество маленьких изображений по вертикали и горизонтали
    tiles_x = width // tile_size
    tiles_y = height // tile_size
    
    # Обрезаем изображение на тайлы
    count = 0
    for y in range(tiles_y):
        for x in range(tiles_x):
            # Вычисляем координаты текущего тайла
            x_start = x * tile_size
            y_start = y * tile_size
            x_end = x_start + tile_size
            y_end = y_start + tile_size
            
            # Обрезаем изображение
            tile = img[y_start:y_end, x_start:x_end]
            
            # Сохраняем тайл
            output_path = os.path.join(output_folder, f"tile_{count}.png")
            cv2.imwrite(output_path, tile)
            count += 1
    
    print(f"Создано {count} изображений 28x28 в папке {output_folder}")

# Пример использования
input_image = "handwritten-document.png"  # Замените на путь к вашему изображению
output_dir = "tiles_output"      # Папка для сохранения маленьких изображений

crop_image_to_tiles(input_image, output_dir)