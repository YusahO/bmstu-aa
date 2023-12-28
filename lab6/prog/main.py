#!venv/bin/python

import utils as u
from defines import *
from test import parametrization, testTime

def main():
    option = -1
    while option != EXIT:
        try:
            option = int(input(MESSAGE))
        except ValueError:
            option = -1
        if (option == BRUTE_FORCE):
            u.run_brute_force()
        elif (option == ANT_ALG):
            u.run_ant_algorithm()
        elif (option == ALG_ALL):
            u.run_all()
        elif (option == PARAMETRIC):
            parametrization(type = CSV)
        elif (option == TEST):
            testTime()
        elif (option == UPDATE_DATA):
            u.update_file()
        elif (option == SHOW_DATA):
            u.print_matrix()
        elif (option == EXIT):
            continue
        else:
            print("Повторите ввод")

if __name__ == "__main__":
    main()