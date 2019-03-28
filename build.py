import os
import sys
import glob

def get_make_file():
    directories = glob.glob('*/')
    return directories

def run_make_files(makefile_arguement):
    directories = get_make_file()

    for directory in directories:
        makefile_path = directory[:-1]
        print('Running the following makefile - ' + makefile_path)
        make_command = '(cd ' + makefile_path + ' && make ' + makefile_arguement + ')'
        os.system(make_command)


if __name__ == "__main__":
    makefile_arguement = sys.argv[1:2]

    if len(makefile_arguement) == 0:
        makefile_arguement = ''
    else:
        makefile_arguement = makefile_arguement[0]

    run_make_files(makefile_arguement)