import os.path
import sys

def main(argv, arc):
    paths = ["../series.txt","../series.csv","../series.psv"]

    for path in paths:
        if os.path.exists(path):
            f=open(path,'r')
            print(f.read())
            f.close()
            break

if __name__ == '__main__':
    main(sys.argv, len(sys.argv))
