text = input("Text: ")
text = text.lower()

lst = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
       'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']

letters = 0
words = 0
sentences = 0

# Split the text into words
words = len(text.split())

for x in text:
    if x.isalpha():  # Count letters only
        letters += 1
    elif x in {'.', '!', '?'}:  # Count sentences
        sentences += 1

# Avoid division by zero
if words > 0:
    Lets = letters / words * 100
    Sent = sentences / words * 100
    score1 = 0.0588 * Lets - 0.296 * Sent - 15.8
    score1 = round(score1)

    if score1 > 16:
        print("Grade 16+")
    elif score1 < 1:
        print("Before Grade 1")
    else:
        print(f"Grade: {score1}")
else:
    print("No valid text entered.")
