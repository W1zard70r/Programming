from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_v1_5
from Crypto.Hash import MD2
import binascii

# 🔹 Загрузи закрытый ключ
with open("private_key.pem", "rb") as f:
    private_key = RSA.import_key(f.read())

cipher_rsa = PKCS1_v1_5.new(private_key)

# 🔹 Hex-данные из твоего сообщения
hex_data = """07:6a:5d:61:32:c1:9e:05:bd:eb:77:f3:aa:fb:bb:83:
82:eb:9e:a2:93:af:0c:2f:3a:e2:1a:e9:74:6b:9b:82:
d8:ef:fe:1a:c8:b2:98:7b:16:dc:4c:d8:1e:2b:92:4c:
80:78:85:7b:d3:cc:b7:d4:72:29:94:22:eb:bb:11:5d:
b2:9a:af:7c:6b:cb:b0:2c:a7:91:87:ec:63:bd:22:e8:
8f:dd:38:0e:a5:e1:0a:bf:35:d9:a4:3c:3c:7b:79:da:
8e:4f:fc:ca:e2:38:67:45:a7:de:6e:a2:6e:71:71:47:
f0:09:3e:1b:a0:12:35:15:a1:29:f1:59:25:35:a3:e4:
2a:32:4c:c2:2e:b4:b5:3d:94:38:93:5e:78:37:ac:35:
35:06:15:e0:d3:87:a2:d6:3b:c0:7f:45:2b:b6:97:8e:
03:a8:d4:c9:e0:8b:68:a0:c5:45:ba:ce:9b:7e:71:23:
bf:6b:db:cc:8e:f2:78:35:50:0c:d3:45:c9:6f:90:e4:
6d:6f:c2:cc:c7:0e:de:fa:f7:48:9e:d0:46:a9:fe:d3:
db:93:cb:9f:f3:32:70:63:cf:bc:d5:f2:22:c4:f3:be:
f6:3f:31:75:c9:1e:70:2a:a4:8e:43:96:ac:33:6d:11:
f3:ab:5e:bf:4b:55:8b:bf:38:38:3e:c1:25:9a:fd:5f""".replace(":\n", "").replace(":", "")

# 🔹 Декодируем hex → bytes
encrypted_bytes = binascii.unhexlify(hex_data)

# 🔹 Расшифровка RSA
decrypted = cipher_rsa.decrypt(encrypted_bytes, None)
print("Расшифрованные данные:", decrypted.hex())

# 🔹 Проверяем MD2-хеш
md2_hash = MD2.new(decrypted).hexdigest()
print("MD2 хеш:", md2_hash)
