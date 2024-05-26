
text = str(input("Text: "))

letters_count = 0
words_count = 1
sentences_count = 0

for char in text:
    if char == ' ':
        words_count += 1
    elif char in ['.', '!', '?']:
        sentences_count += 1
    elif char.isalpha():
        letters_count += 1

l = letters_count * 100 / words_count
s = sentences_count * 100 / words_count
Coleman_Liau = 0.0588 * l - 0.296 * s - 15.8

if Coleman_Liau < 1:
    print("Before Grade 1")
elif Coleman_Liau > 16:
    print("Grade 16+")

print(f"Grade {round(Coleman_Liau)}")
