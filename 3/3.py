with open("words.txt", "r") as f:
    a = f.read()
wordList = a.split()
c = 0
minder = " "
for i in wordList:
    if len(i) > c:
        c = len(i)
        minder = i
print("Самое длинное слово: ", minder, ", его количество знаков равно", c)
for i in wordList:
    if len(i) == c:
        if i != minder:
            print("Ещё одно слово с похожим количеством символов: ", i)