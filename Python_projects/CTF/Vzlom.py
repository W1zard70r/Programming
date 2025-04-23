import random
import time
import asyncio
from datetime import datetime

async def try_seed(seed_value, reader, writer):
    """Пытается угадать 100 чисел с заданным сидом."""
    random.seed(seed_value)
    guessed = 0

    for _ in range(1000):  # MAX_ATTEMPTS = 1000
        number = random.randint(0, 4294967294)
        writer.write(f"{number}\n".encode())
        await writer.drain()

        response = (await reader.read(1024)).decode()

        if "That's the right number" in response:
            guessed += 1
            if guessed >= 100:  # NEED_GUESSED = 100
                print(f"\n[+] Успех! Сид: {seed_value}")
                print("[+] Флаг:", response.split("Flag is ")[-1].strip())
                return True
        else:
            guessed = 0

    return False

async def exploit():
    while True:
        try:
            print("\n[+] Подключаемся к серверу...")
            reader, writer = await asyncio.open_connection("87.228.78.46", 9999)
            
            # Пропускаем приветственное сообщение
            await reader.read(1024)

            # Получаем первое число (отправляем неверное и получаем правильное)
            writer.write(b"0\n")
            await writer.drain()
            response = (await reader.read(1024)).decode()

            if "That's incorrect number" not in response:
                print("[-] Не удалось получить первое число. Ответ сервера:", response)
                continue

            correct_number = int(response.split("is ")[1].split("\n")[0])
            print(f"[+] Первое число: {correct_number}")

            # Текущее время для перебора
            now = int(time.time())
            
            # Перебираем сиды в диапазоне ±1 час (можно увеличить)
            for offset in range(-3600, 3601):
                seed_candidate = now + offset
                print(f"\r[?] Проверяем сид: {seed_candidate}", end="", flush=True)

                if await try_seed(seed_candidate, reader, writer):
                    return  # Успех

                # Пауза, чтобы не перегружать сервер
                await asyncio.sleep(0.05)

        except (ConnectionResetError, ConnectionAbortedError) as e:
            print(f"\n[-] Ошибка соединения: {e}. Переподключаемся...")
            await asyncio.sleep(1)
            continue

        except Exception as e:
            print(f"\n[-] Неизвестная ошибка: {e}")
            await asyncio.sleep(2)
            continue

        finally:
            if 'writer' in locals():
                writer.close()
                await writer.wait_closed()

asyncio.run(exploit())