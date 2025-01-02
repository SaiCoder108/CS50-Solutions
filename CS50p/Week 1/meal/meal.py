def main():
    ask = input("What time is it? ")
    time = convert(ask)
    if time-7 >= 0 and time-7 <= 1:
        print("breakfast time")
    elif time-12 >= 0 and time-12 <= 1:
        print("lunch time")
    elif time-18 >= 0 and time-18 <= 1:
        print("dinner time")


def convert(time):
    newtime = 0
    time = list(time)
    if len(time) == 4:
        newtime += int(time[0])
        newtime += (((float(time[2])*10) + float(time[3]))/60)

    elif len(time) == 5:
        newtime += ((int(time[0])*10)+int(time[1]))
        newtime += (((float(time[3])*10) + float(time[4]))/60)

    return newtime


if __name__ == "__main__":
    main()
