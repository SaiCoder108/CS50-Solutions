months = [
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
]

while True:
    date = input("Date: ").strip()
    slash = None
    for x in date:
        if x.isalpha() == True:
            slash = False
            break
        else:
            slash = True
    if slash == False:
        if "," not in date:
            continue
        date = date.split(" ")
        if date[0].isdigit() == True or int((date[1])[:-1])>31 or months.index(date[0])>=12:
            continue
        else:
            newdate = ""
            newdate += f"{(date[2])}"
            if months.index(date[0])+1 < 10:
                newdate += f"-0{months.index(date[0])+1}"
            else:
                newdate += f"-{months.index(date[0])+1}"
            if len((date[1])[:-1]) == 1:
                newdate += f"-0{(date[1])[:-1]}"
            else:
                newdate += f"-{(date[1])[:-1]}"
            break
    elif slash == True:
        date = date.split("/")
        if int(date[1])>31 or int(date[0])>12:
            continue
        test = False
        for x in date:
            if x.isalpha() == True:
                test = True
        if test == True:
            continue
        else:
            newdate = ""
            if int(date[1]) < 10 and int(date[0]) < 10:
                newdate += f"{date[2]}-0{date[0]}-0{date[1]}"
            elif int(date[1]) >= 10 and int(date[0]) < 10:
                newdate += f"{date[2]}-0{date[0]}-{date[1]}"
            elif int(date[1]) < 10 and int(date[0]) >= 10:
                newdate += f"{date[2]}-{date[0]}-0{date[1]}"
            else:
                newdate += f"{date[2]}-{date[0]}-{date[1]}"
            break
print(newdate, end="")
