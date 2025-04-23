import requests

# Creating comments
# for ch in 'affeeasdcx':
#     url = 'http://127.0.0.1:8000/add_comment'
#     body = {
#         'email': f'{ch}@mail.ru',
#         'comment': f'{ch}'
#     }

#     response = requests.post(url, data = body)
#     print(response.status_code) 

# Deleting comments
# for id_to_delete in range(100):
#     url = f'http://127.0.0.1:8000/delete_comment/{id_to_delete}'
#     body = {}
#     response = requests.post(url, data = body)
#     print(response.status_code) 
#     print(response.headers)