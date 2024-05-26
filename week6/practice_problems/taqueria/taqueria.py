menu = {
    "Baja Taco": 4.00,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}


def main():
    price = 0.00
    while True:
        try:
            order = str(input("Item: "))
        except EOFError:
            print()
            return

        try:
            price += menu[order.title()]
            print(f"Total: ${price:.2f}")
        except KeyError:
            pass


main()
