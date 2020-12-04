### Source : https://adventofcode.com/2016/day/5#part2
### Author : liuyubobobo
### Time   : 2020-12-04

import hashlib

if __name__ == '__main__':

    # initializing string
    base = "abbhdwsy"

    res = [' ' for _ in range(8)]
    index = 0
    p = 0
    while True:
        str2hash = base + str(index)
        # then sending to md5()
        result = hashlib.md5(str2hash.encode()).hexdigest()

        if result[0:5] == "00000" and '0' <= result[5] <= '7' and res[int(result[5])] == ' ':
            res[int(result[5])] = result[6]

            print(str(p) + " get!")
            p += 1
            if p == 8:
                break

        index += 1

    print(res)
