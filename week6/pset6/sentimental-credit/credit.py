from cs50 import get_int
import math
import sys


def main():
    number = get_int("Number: ")

    if number < 0:
        print("INVALID")
        sys.exit(-1)

    if not luhns_algorithm(str(number)):
        print("INVALID")
        sys.exit(-2)

    ''' Print cart type '''
    c_type = card_type(str(number))
    print(c_type)


def luhns_algorithm(num):  # num is string-type
    sum = 0
    for i in range(1, len(num) + 1):
        if i % 2 != 0:
            sum += int(num[-i])
        else:
            d = int(num[-i]) * 2
            if d < 10:
                sum += d
            else:
                ''' add the sum of the two digits of d to sum '''
                sum += math.floor(d / 10) + (d % 10)
    if sum % 10 == 0:
        return True
    return False


def card_type(num):  # num is string-type
    if len(num) == 15:
        if num[0:2] == "34" or num[0:2] == "37":
            return "AMEX"
        return "INVALID"
    elif len(num) == 13 and num[0] == "4":
        return "VISA"
    elif len(num) == 16:
        if num[0] == "4":
            return "VISA"
        elif 50 < int(num[0:2]) and int(num[0:2]) < 56:
            return "MASTERCARD"
        return "INVALID"
    return "INVALID"


if __name__ == "__main__":
    main()
    sys.exit(0)
