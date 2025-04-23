import requests
k = 0
# Creating comments
for ch in range(100):
    url = 'http://127.0.0.1:8080/?new_message={%22email%22:%22aboba@mail.ru%22,%22content%22:%22%E4%BD%A0%E5%A5%BD%EF%BC%8C%E6%88%91%E6%98%AF%E4%BD%A0%E5%94%AF%E4%B8%80%E7%9A%84%E7%94%A8%E6%88%B6%22}'
    body = {}
    response = requests.post(url, data = body)
    # print(response.status_code)
    # print(response.text) 
    if response.status_code == 200:
        k += 1
        print(k)

# for ch in range(30):
#     url = 'http://127.0.0.1:8080/?search='
#     body = {}
#     response = requests.get(url, data = body)
#     print(response.status_code)
#     # print(response.text) 
#     if response.status_code == 200:
#         k += 1
#         print(k)

# Deleting comments
# for id_to_delete in range(100):
#     url = f'http://127.0.0.1:8000/delete_comment/{id_to_delete}'
#     body = {}
#     response = requests.post(url, data = body)
#     print(response.status_code) 
#     print(response.headers)