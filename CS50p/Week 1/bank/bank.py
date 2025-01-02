ask = input("Enter: ").strip()
test = list(ask.lower())
if "hello" in ask.lower():
    print("$0")
elif test[0] == "h":
    print("$20")
else:
    print("$100")