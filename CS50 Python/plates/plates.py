def main():
    plate = input("Plate: ")
    if is_valid(plate):
        print("Valid")
    else:
        print("Invalid")


def is_valid(s):
    check = list(s)
    if len(check)<=6 and len(check)>=2:
        pass
    else:
        return False
    if check[0].isalpha() and check[1].isalpha():
        pass
    else:
        return False
    test = ["blank"]
    for x in range(len(check)):
        if check[x].isdigit() == True:
            test = check[x-1:]
    if test == ["blank"]:
        pass
    else:
        for y in test:
            if y.isalpha() == True:
                return False
        if int(test[0]) == 0:
            return False
    for x in check:
        if x in ["."," ","!","?"]:
            return False
    return True


main()
