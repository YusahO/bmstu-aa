def choose_next_loc_by_possibility(pk):
    posibility = random()
    choice = 0
    chosen_loc = 0
    while (choice < posibility) and (chosen_loc < len(pk)):
        choice += pk[chosen_loc]
        chosen_loc += 1
    return chosen_loc
