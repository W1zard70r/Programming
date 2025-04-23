import asyncio
import argparse
from prompt_toolkit import PromptSession
from prompt_toolkit.patch_stdout import patch_stdout

async def client(ip: str, port: int, username: str):
    # Подключаемся к серверу
    reader, writer = await asyncio.open_connection(ip, port)

    # Отправляем имя пользователя на сервер
    writer.write((username + '\n').encode())
    await writer.drain()

    # Создаем сессию для ввода сообщений
    session = PromptSession()

    # Флаг для завершения работы
    running = True

    # Запускаем задачу для чтения сообщений от сервера
    async def receive_messages():
        nonlocal running
        while running:
            try:
                data = await reader.readuntil(b'\n')
                print(data.decode().strip())  # Выводим сообщение в консоль
            except (asyncio.IncompleteReadError, ConnectionError):
                print("The connection to the server has been lost.")
                running = False
                break

    # Запускаем задачу для отправки сообщений на сервер
    async def send_messages():
        nonlocal running
        while running:
            try:
                with patch_stdout():
                    message = await session.prompt_async("> ")  # Читаем ввод пользователя
                writer.write((message + '\n').encode())
                await writer.drain()
            except (asyncio.CancelledError, KeyboardInterrupt):
                running = False
                break

    try:
        # Запускаем обе задачи параллельно
        await asyncio.gather(receive_messages(), send_messages())
    except (asyncio.CancelledError, KeyboardInterrupt):
        print("\nClient is shutting down...")
    finally:
        # Закрываем соединение
        running = False
        writer.close()
        await writer.wait_closed()

if __name__ == '__main__':
    # Настройка аргументов командной строки
    parser = argparse.ArgumentParser(description="Chat client for connecting to the server.")
    parser.add_argument('--ip', type=str, required=True, help="Server IP address")
    parser.add_argument('--port', type=int, required=True, help="Server port")
    parser.add_argument('--username', type=str, required=True, help="Username")

    # Парсинг аргументов
    args = parser.parse_args()

    try:
        # Запуск клиента
        asyncio.run(client(args.ip, args.port, args.username))
    except KeyboardInterrupt:
        print("Client shut down")
    except Exception as e:
        print(f"Error: {e}")