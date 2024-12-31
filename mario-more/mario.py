ask = (input("Height: "))
while True:
    if ask.isdigit() == False:
        ask = (input("Height: "))
    elif int(ask) > 8 or int(ask) < 1:
        ask = (input("Height: "))
    else:
        break
ask = int(ask)
space = " "
hash = "#"
for x in range(1, int(ask)+1):
    print((space*(ask-x))+(hash*(x))+(space*2)+(hash*(x)))
