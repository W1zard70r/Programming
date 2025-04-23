nums = [i for i in range(10,30)] + [29]
k = 58

dik = {} #создание словаря с кол-вом вхождений
for i in nums:
  dik[i] = dik.get(i, 0) + 1

if k / 2 in dik and dik[k / 2] == 2: #обработка исключения
  print(k / 2, k / 2)
else:
  for i in dik: #основной алгоритм
    if k - i in dik and i != k - i:
      print(i, k - i)
      break
  else:
    print(None)
