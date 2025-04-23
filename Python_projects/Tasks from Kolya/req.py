import requests

url = "http://mercury.picoctf.net:38322/"
headers = {
    "Content-Type": "image/png",
    "Accept-Encoding": "gzip, deflate, br, zstd",
    "Accept": "*/*",
    "User-Agent": "picobrowser",
    'Accept-Language': 'RU',
    'Connection': 'keep-alive'
}
session = requests.Session() 
response = session.get(url, headers=headers)

print(response.status_code)
print(response.text)
