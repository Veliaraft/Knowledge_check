a = input("Пожалуйста, введите строку: ")
arr = ['a', 'e', 'y', 'u', 'i', 'o', 'e']
count = 0
for i in range(len(a)):
    if (a[i] in arr):
        count+=1
print("Гласных =", count, sep = ' ')
print("Согласных =", len(a) - count, sep = ' ')
