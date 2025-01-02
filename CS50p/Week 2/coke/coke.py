due = 50
while True:
    print(f"Amount Due: {due}")
    ask = int(input("Insert Coin: "))
    if ask not in [25,10,5]:
        continue
    else:
        due=due-ask
        if due<=0:
            break
print(f"Change Owed: {(-1)*due}")
