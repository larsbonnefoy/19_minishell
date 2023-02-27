


from os import system
from time import sleep

def main():
    i = 0
    while (i < 1024):
        system(f"mkdir tmp && cd tmp")
        i += 1

if __name__ == "__main__":
    main()
