ask = input("camelCase: ")
test = list(ask)
for x in ask:
    if x.isupper() == True and x != test[0]:
        ask = ask.replace(x,(f"_{x.lower()}"))
print(ask)
