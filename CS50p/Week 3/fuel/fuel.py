while True:
    ask = input("Fraction: ")
    if "/" not in ask:
        continue

    else:

        try:
            ask = ask.split("/")
            if int(ask[0])/int(ask[1]) > 1:
                continue
            else:
                x = int(ask[0])
                y = int(ask[1])

                if x/y <= 0.01 and x/y >= 0.00:
                    print("E")
                elif x/y >= 0.99 and x/y <= 1.00:
                    print("F")
                else:
                    test = round(((x/y))*100)
                    print(f"{test}%")
                break

        except (ZeroDivisionError,ValueError):
            pass



