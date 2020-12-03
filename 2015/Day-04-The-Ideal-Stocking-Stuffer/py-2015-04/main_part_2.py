### Source : https://adventofcode.com/2015/day/4#part2
### Author : liuyubobobo
### Time   : 2020-12-03

import hashlib

if __name__ == '__main__':

    # initializing string
    base = "ckczppom"

    index = 1
    while True:
        str2hash = base + str(index)
        # then sending to md5()
        result = hashlib.md5(str2hash.encode()).hexdigest()

        if result[0:6] == "000000":
            break

        index += 1

    print(index)
