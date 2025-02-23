def main():
    text = input("Text: ").lower()
    L, S = counts(text)
    print(grade(L, S))


def counts(text):
    text_list = text.split()

    word_count = 0
    letter_count = 0
    sentence_count = 0
    for word in text_list:
        word_count += 1
        for letter in word:
            if letter in ['.', '?', '!']:
                sentence_count += 1
            if letter.isalpha():
                letter_count += 1

    L = (letter_count / word_count) * 100
    S = (sentence_count / word_count) * 100

    return L, S


def grade(L, S):
    index = 0.0588 * L - 0.296 * S - 15.8

    if index > 16:
        return "Grade 16+"
    elif index < 1:
        return "Before Grade 1"
    else:
        return f"Grade {round(index)}"


if __name__ == "__main__":
    main()
