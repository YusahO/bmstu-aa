class Cout:
    def __lshift__(self, val):
        print(val)
        return self
    

cout = Cout()































cout << "skibidi"