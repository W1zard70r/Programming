import socket
import struct
import random
url = input()

sock = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.getprotobyname("icmp"))

host = socket.gethostbyname(url)

packet_id = random.randint(0, 65535)

def checksum(data: bytes) -> int:
    if len(data) % 2:
        data += b"\x00"

    words = [int.from_bytes(data[i:i+2], "big") for i in range(0, len(data), 2)]
    checksum = sum(words)

    while checksum > 0xFFFF:
        checksum = (checksum & 0xFFFF) + (checksum >> 16)

    return ~checksum & 0xFFFF

def create_packet(id: int) -> bytes:
    header = struct.pack("bbHHh", 8, 0, 0, id, 1)  
    data = b"hello world"

    check = checksum(header + data)
    header = struct.pack("bbHHh", 8, 0, socket.htons(check), id, 1)

    return header + data

packet = create_packet(packet_id)
sock.sendto(packet, (host, 0))

sock.settimeout(2) 

try:
    pass
except socket.timeout:
    print(f"DOWN")
except Exception as e:
    print(f"Произошла ошибка: {e}")
finally:
    sock.close()