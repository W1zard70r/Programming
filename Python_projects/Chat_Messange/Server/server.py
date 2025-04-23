import json
import os
import asyncio
from typing import Optional, List
from collections import deque
import signal
import functools

class User:
    username: str
    reader: Optional[asyncio.StreamReader]
    writer: Optional[asyncio.StreamWriter]

    def __init__(self, username: str, reader: Optional[asyncio.StreamReader], writer: Optional[asyncio.StreamWriter]):
        self.username = username
        self.reader = reader
        self.writer = writer

class Cache:
    all_users: List[User]
    messages: deque[str]

    def __init__(self, all_users: List[User], messages: deque[str]):
        self.all_users = all_users
        self.messages = messages

    def get_user_names(self):
        return (x.username for x in self.all_users)

    def get_writers(self):
        return (x.writer for x in self.all_users if x.writer is not None)

def load_cache_from_file(filename: str = "cache.json") -> Cache:
    if os.path.exists(filename):
        with open(filename, "r", encoding="utf-8") as file:
            data = json.load(file)
            messages = deque(data["messages"], maxlen=50)
            return Cache([], messages)
    return Cache([], deque(maxlen=50))

def save_cache_to_file(cache: Cache, filename: str = "cache.json"):
    data = {
        "messages": list(cache.messages)
    }
    try:
        with open(filename, "w", encoding="utf-8") as file:
            json.dump(data, file, ensure_ascii=False, indent=4)
    except Exception as e:
        print(f"Failed to save cache: {e}")

cache = load_cache_from_file()

async def handle_client(reader: asyncio.StreamReader, writer: asyncio.StreamWriter):
    try:
        data = await reader.readuntil(b'\n')  # Читаем до символа новой строки
        username = data.decode().strip()
        if not username:
            return

        if username in cache.get_user_names():
            writer.write(b"Username already taken. Please choose another one.\n")
            await writer.drain()
            return

        user = User(username, reader, writer)
        cache.all_users.append(user)

        join_message = f'User {username} joined the chat\n'
        previous_messages = '\n'.join(cache.messages) + '\n'
        writer.write(previous_messages.encode())
        await writer.drain()

        await broadcast(join_message)
        cache.messages.append(join_message)

        while True:
            try:
                data = await reader.readuntil(b'\n')  # Читаем до символа новой строки
                message = data.decode().strip()
                if not message:
                    continue

                cache.messages.append(f'{username}: {message}')
                await broadcast(f'{username}: {message}\n')  # Добавляем символ новой строки
            except (ConnectionError, asyncio.CancelledError, asyncio.IncompleteReadError):
                break

    finally:
        exit_message = f'User {username} left the chat\n'
        cache.all_users = [u for u in cache.all_users if u.username != username]
        await broadcast(exit_message)
        cache.messages.append(exit_message)

        writer.close()
        await writer.wait_closed()




async def to_write(writer: Optional[asyncio.StreamWriter], new_message: str):
    if writer is not None and not writer.is_closing():
        writer.write(new_message.encode())
        await writer.drain()

async def broadcast(new_message: str):
    await asyncio.gather(*[to_write(writer, new_message) for writer in cache.get_writers()])

async def shutdown(server):
    print("Server shuts down...")
    save_cache_to_file(cache)

    # Закрываем все соединения
    for user in cache.all_users:
        if user.writer:
            user.writer.close()
            await user.writer.wait_closed()

    # Останавливаем сервер
    server.close()
    await server.wait_closed()

async def main():
    print(f'IP: 127.0.0.1, port: 8000')
    server = await asyncio.start_server(handle_client, '127.0.0.1', 8000)

    try:
        async with server:
            await server.serve_forever()
    except asyncio.CancelledError:
        await shutdown(server)

if __name__ == '__main__':
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("Server has been shut down.")


