def convert(ask):
    ask = ask.split(" ")
    for x in ask:
        if x == ":)":
            ask[ask.index(x)] = "🙂"
        elif x == ":(":
            ask[ask.index(x)] = "🙁"
    return " ".join(ask)

def main():
    ask=input()
    print(convert(ask))

main()
