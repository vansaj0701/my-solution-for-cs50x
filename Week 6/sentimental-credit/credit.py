import re


def checksum(n):
    sum = 0

    for i in n[len(n)-2::-2]:
        i = int(i) * 2

        if i >= 10:
            while i != 0:
                rem = i % 10
                sum += rem
                i = i // 10
        else:
            sum += i

    for j in n[len(n)-1::-2]:
        sum += int(j)

    if sum % 10 == 0:
        return True

    return False


def credit(n):
    if len(n) == 15:
        amex_pattern = r"^3(4|7)"
        amex_match = re.search(amex_pattern, n)
        if amex_match:
            return "AMEX"

    if len(n) == 13 or len(n) == 16:
        mc_pattern = r"^5[12345]"
        mc_match = re.search(mc_pattern, n)
        if mc_match:
            return "MASTERCARD"

        if n.startswith("4"):
            return "VISA"

    return "INVALID"


def main():
    card_number = input("Number: ")

    if checksum(card_number):
        print(credit(card_number))
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
