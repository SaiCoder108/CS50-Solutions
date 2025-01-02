lst = []
done = []
while True:
    try:
        item = input()
        lst.append(item)

    except EOFError:
        lst.sort()
        for x in lst:
            if x in done:
                continue
            else:
                print(f"{lst.count(x)} {x.upper()}")
                done.append(x)

        print()
        break
