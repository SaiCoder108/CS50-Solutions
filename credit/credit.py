credit = input("Number: ")
counter = 0
sum1 = 0

# Determine if the length is even or odd
if len(credit) % 2 == 0:
    counter = 0  # Start with the first digit being doubled
else:
    counter = 1  # Start with the second digit being doubled

for x in credit:
    digit = int(x)

    if counter % 2 == 0:  # Doubling every second digit from the right
        temp = digit * 2
        if temp > 9:
            sum1 += temp % 10 + temp // 10  # Sum the digits of the result
        else:
            sum1 += temp
    else:
        sum1 += digit  # Just add the digit as is

    counter += 1

# Validate checksum
if sum1 % 10 != 0:
    print("INVALID")
else:
    # Card type checks
    if len(credit) == 15 and (credit.startswith("34") or credit.startswith("37")):
        print("AMEX")
    elif len(credit) == 16 and (51 <= int(credit[:2]) <= 55):
        print("MASTERCARD")
    elif (len(credit) == 13 or len(credit) == 16) and credit.startswith("4"):
        print("VISA")
    else:
        print("INVALID")
