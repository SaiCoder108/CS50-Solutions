ask = input("Enter: ")
if "gif" in ask.lower():
    print("image/gif")
elif "jpg" in ask.lower():
    print("image/jpeg")
elif "jpeg" in ask.lower():
    print("image/jpeg")
elif "png" in ask.lower():
    print("image/png")
elif "pdf" in ask.lower():
    print("application/pdf")
elif "txt" in ask.lower():
    print(f"text/{ask[:-4]}")
elif "zip" in ask.lower():
    print("application/zip")
else:
    print("application/octet-stream")
