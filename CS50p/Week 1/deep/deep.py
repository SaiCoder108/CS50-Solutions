ask = input("What is the Answer to the Great Question of Life, the Universe, and Everything? ").strip()
if ask.isdigit() and int(ask) == 42:
    print("Yes")
elif ask.lower() == "forty two" or ask.lower() == "forty-two":
    print("Yes")
else:
    print("No")
