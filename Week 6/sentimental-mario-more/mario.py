def pyramid(n):
    # loop that geos from 1 to height
    for i in range(n):
        print(" " * (n - (i+1)), end="")
        print("#" * (i+1), end="  ")
        print("#" * (i+1))


def main():
    while True:
        try:
            # Ask user for height
            height = int(input("Height: "))

            # Checking whether height is within specified range or not
            # Range: 1 to 8 (inclusive)
            # if not re-prompt user for the height
            if (1 <= height <= 8):
                # Calling pyramid function
                pyramid(height)
                break
            else:
                continue
        except ValueError:
            continue


if __name__ == "__main__":
    main()
