"""
Lari Lantonen
Mölkky
"""


class Player:
    def __init__(self, name):
        self.__pts = 0
        self.__name = name
        self.__average = 0
        self.__turn_number = 0
        self.__hits = 0

    def add_points(self, pts):
        self.__turn_number += 1
        self.__pts += pts

        if pts != 0:
            self.__hits += 1

        if self.__pts > 50:
            self.__pts = 25
            print("{} gets penalty points!".format(self.__name))
        elif 40 <= self.__pts < 50:
            print("{} needs only {} points. It's better to "
                  "avoid knocking down the pins with "
                  "higher points.".format(self.__name, 50 - self.__pts))

    def calc_average(self, pts):

        self.__average += pts
        if pts > self.__average / self.__turn_number:
            return True
        return False

    def has_won(self):

        if self.__pts == 50:
            return True
        else:
            return False

    def get_hit_percentage(self):

        try:
            return float(self.__hits / self.__turn_number * 100)
        except ZeroDivisionError:
            return 0.0

    def get_name(self):
        return self.__name

    def get_points(self):
        return self.__pts


def main():
    # Here we define two variables which are the objects initiated from the
    # class Player. This is how the constructor of the class Player
    # (the method that is named __init__) is called!
    player1 = Player("Matti")
    player2 = Player("Teppo")
    throw = 1

    while True:

        if throw % 2 == 0:
            in_turn = player1
        else:
            in_turn = player2
        pts = int(input("Enter the score of player " + in_turn.get_name() +
                        " of throw " + str(throw) + ": "))

        in_turn.add_points(pts)

        if in_turn.calc_average(pts):
            print("Cheers {}!".format(in_turn.get_name()))

        if in_turn.has_won():
            print("Game over! The winner is " + in_turn.get_name() + "!")
            return

        print("")
        print("Scoreboard after throw " + str(throw) + ":")
        print(player1.get_name() + ":", player1.get_points(), "p,",
              "hit percentage {:.1f}".format(player1.get_hit_percentage()))
        print(player2.get_name() + ":", player2.get_points(), "p,",
              "hit percentage {:.1f}".format(player2.get_hit_percentage()))
        print("")
        throw += 1

main()
