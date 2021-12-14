import collections

f = open('lorem.txt', 'r')
fs = f.read()
f.close()
c = collections.Counter(fs)
print(c.most_common(), sep="\n")
