from cs50 import get_string

# prompt user for a text
users_text = get_string("Text: ")

num_of_letters = 0
num_of_words = 1
num_of_sent = 0

# count letters, words and sents
for c in users_text:
    if c.isalpha():
        num_of_letters += 1
    if c.isspace():
        num_of_words += 1
    if c == '!' or c == '.' or c == '?':
        num_of_sent += 1

# calculate the index and round it
L = (num_of_letters / num_of_words) * 100
S = (num_of_sent / num_of_words) * 100
index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
