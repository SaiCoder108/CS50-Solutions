ask = input("Input: ")
for x in ask:
    if x.lower() in ["a","e","i","o","u"]:
        ask = ask.replace(x,"")
print("Output:",ask)
