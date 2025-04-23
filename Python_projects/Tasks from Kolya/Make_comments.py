import requests
import time

url = "https://mychords.net/ru/comments-widget/create"

headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/132.0.0.0 Safari/537.36",
    "Referer": "https://mychords.net/ru/kukryniksy/79116-kukryniksy-vera.html",
    "Origin": "https://mychords.net",
    "Content-Type": "application/x-www-form-urlencoded",
    "X-Requested-With": "XMLHttpRequest",
}

comments = [
    "Отличная песня!", "Супер!", "Очень нравится!", "Топ!", "Класс!", "Шикарно!",
    "Любимая песня!", "Просто огонь!", "Восторг!", "Слова за душу берут!", 
    "Мелодия невероятная!", "Настоящий хит!", "Это шедевр!", "Браво исполнителю!",
    "Глубокий смысл!", "Сильная композиция!", "Не могу перестать слушать!",
    "Спасибо за аккорды!", "Прекрасный текст!", "Великолепно!"
]

for comment in comments:
    session = requests.Session()  # Создаем новую сессию для новых cookies
    session.get("https://mychords.net")  # Загружаем главную страницу для получения новых cookies
    
    data = {
        "page": "s",
        "page_id": "79116",
        "message": comment,
        "comment_id": "",
        "name": "Александр",
    }
    
    response = session.post(url, headers=headers, data=data, timeout=10)
    
    if response.status_code == 200:
        print(f"Комментарий '{comment}' успешно отправлен!")
    else:
        print(f"Ошибка при отправке '{comment}': {response.status_code}")
    
    time.sleep(5)  # Ждем 5 секунд, чтобы избежать блокировки
