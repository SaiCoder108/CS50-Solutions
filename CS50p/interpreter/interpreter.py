ask = input("Expression: ").split(" ")
x = float(ask[0])
y = ask[1]
z = float(ask[2])

if y == "+":
    print(x+z)
elif y == "-":
    print(x-z)
elif y == "*":
    print(x*z)
elif y == "/":
    print(x/z)
