Серв включается в cmd командой python server.py, выдаётся его айпи и порт, подключение к нему осуществляется тоже через cmd с помощью команды вроде 
python client.py --ip 127.0.0.1 --port 8000 --username Superman2025, причём нужно активировать venv.
Выход клиента происходит, если 2 раза нажать Ctrl+C, сервер же отключается, если нажать 1 раз Ctrl+C.
Чат сохраняет 50 последних сообщений в папке cache.json.