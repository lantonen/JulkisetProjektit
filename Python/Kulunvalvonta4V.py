# TIE-02100 Johdatus ohjelmointiin
# TIE-02106 Introduction to programming
# Task: accesscontrol, program code template
# Lari Lantonen


import csv

DOORCODES = {'TC114': ['TIE'], 'TC203': ['TIE'],
             'TC210': ['TIE', 'TST'],
             'TD201': ['TST'],
             'TE111': [], 'TE113': [], 'TE115': [], 'TE117': [],
             'TE102': ['TIE'],
             'TD203': ['TST'],
             'TA666': ['X'],
             'TC103': ['TIE', 'OPET', 'SGN'],
             'TC205': ['TIE', 'OPET', 'ELT'],
             'TB109': ['OPET', 'TST'], 'TB111': ['OPET', 'TST'],
             'TB103': ['OPET'], 'TB104': ['OPET'],
             'TB205': ['G'],
             'SM111': [], 'SM112': [], 'SM113': [], 'SM114': [],
             'S1': ['OPET'], 'S2': ['OPET'], 'S3': ['OPET'], 'S4': ['OPET'],
             'K1705': ['OPET'],
             'SB100': ['G'], 'SB202': ['G'],
             'SM220': ['ELT'], 'SM221': ['ELT'], 'SM222': ['ELT'],
             'secret_corridor_from_building_T_to_building_F': ['X', 'Y', 'Z'],
             'TA': ['G'], 'TB': ['G'], 'SA': ['G'], 'KA': ['G']}


class Accesscard:

    def __init__(self, id, name):
        """
        Constructor, creates a new object that has no access rights.
        :param id: card holders personal id (str)
        :param name: card holders name (str)
        """

        self.__id = id
        self.__name = name
        self.__access = []

    def read_access(self, permits):
        """
        When reading file, adds permits to this card
        :param permits: cards access rights.
        """

        self.__access = permits

    def get_access_info(self):
        """
        :return: Cards accesses
        """

        return self.__access

    def info(self):
        """
        The method has no return value. It prints the information related to
        the access card in the format:
        id, name, access: a1,a2,...,aN
        for example:  777, Thelma Teacher, access: OPET, TE113, TIE
        Uses function list_to_string to change list of accesses to correct form
        """

        accesses = list_to_string(self.__access)
        print("{}, {}, access: {}".format(self.__id, self.__name,
                                          accesses))

    def get_name(self):
        """
        :return: Returns the name of the access card holder.
        """

        return self.__name

    def add_access(self, new_access_code):
        """
        The method adds a new access code into the access card.
        Uses function del_useless_permits for deleting door codes that are
        already in area code.
        :param new_access_code: The access code to be added in the card.
        """

        access_codes = self.__access
        if new_access_code not in access_codes:
            access_codes.append(new_access_code)
            self.del_useless_permits()

    def check_access(self, door):
        """
        Checks if the access card allows access to a certain door.
        With separate function separates door codes and area codes.

        :param door: the door code of the door that is being accessed.
        :return: True: The door opens for this access card.
                 False: The door does not open for this access card.
        """

        areas, doors = separate(self.__access)
        if door in doors:
            return True
        else:
            for area in areas:
                if area in DOORCODES[door]:
                    return True
        return False

    def merge(self, card):
        """
        Merges the access codes from another access card to this access card.
        :param card: The access card whose access rights are added to this card.
        """
        for code in card.__access:
            self.add_access(code)

    def del_useless_permits(self):
        """
        Deletes useless accesses. Uses separate function.
        Checks if there is overlapped accesses example:
            if card has access to door TC114 but also access to TIE area,
            this function will remove the door code.
        In the end it sorts access codes.
        """

        permit_list = self.__access
        area_permits, door_permits = separate(permit_list)

        for door_code in door_permits:
            for area_code in area_permits:
                if area_code in DOORCODES[door_code]:
                    permit_list.remove(door_code)
        self.__access = sorted(permit_list)


def separate(permit_list):
    """
    Separates areas and doors accesses.
    :param permit_list: list of permits.
    :return area_permits: a.k.a areas codes
            door_permits: a.k.a door codes
    """

    area_permits = []
    door_permits = []

    for permit in permit_list:
        if permit not in DOORCODES:
            area_permits.append(permit)
        else:
            door_permits.append(permit)
    return area_permits, door_permits


def list_to_string(code_list):
    """
    transfers list to correct string for printing
    :param code_list: list of codes to print
    :return access_string: String that is in correct form for printing.
    """

    access_string = ""
    for code in code_list:
        access_string += code + ", "
    access_string = access_string.strip(", ")
    return access_string


def reading_and_sorting():
    """
    Reads accessinfo.txt and transfers it into
    dictionary with identifier as key value. Permits are moved into Accescards
    as method read_access.
    With del_useless_permits() simplifies permits and sorts them.
    :return True: Read file successfully.
            if False: there was error reading the file.
    """

    try:
        access_cards = {}
        with open("accessinfo.txt") as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=";")
            for row in csv_reader:
                card_id = row[0]
                access_cards[card_id] = Accesscard(row[0], row[1])
                access_cards[card_id].read_access(row[2].split(","))
                access_cards[card_id].del_useless_permits()
        csv_file.close()

    except Exception:
        print("Error: file cannot be read.")
        return False

    return True, access_cards


def get_all_codes(dictionary):
    """
    :param dictionary:
    :return: list of all keys and values from dictionary
    """

    all_list = []
    keys = dictionary.keys()

    for key in keys:
        all_list.append(key)
        area_list = dictionary[key]
        for area in area_list:
            if area not in all_list:
                all_list.append(area)
    return all_list


def only_errors(strings, ALL_CODES, access_cards):
    """
    Checking every possible error in operating function so it isn't
    as messy as it could be.
    If error is raised, prints correct error.

    :param strings: Has 3 information we need, command, card_id and
    in some cases access code.
    :param ALL_CODES: list of all codes, area and door codes.
    :param access_cards: dictionary that has every Accesscard
    :return card: If no errors are raised returns correct card
            None: If error is raised. In operating value will be checked.
    """
    command = strings[0]
    card_id = strings[1]

    error = True
    if card_id not in access_cards:
        string = "id"
    else:
        card = access_cards[card_id]

        if len(strings) > 2:
            code_or_id = strings[2]

            if command == "access" and code_or_id not in DOORCODES:
                string = "doorcode"

            elif command == "add" and code_or_id not in ALL_CODES:
                string = "accesscode"

            elif command == "merge" and code_or_id not in access_cards:
                string = "id"

            else:
                error = False
        else:
            error = False

    if error:
        print("Error: unknown {}.".format(string))
        return None
    else:
        return card


def operating(ALL_CODES, access_cards):
    """
    Operating system for software. All commands are done from this function.
    :param ALL_CODES: list of all codes, area and door codes.
    :param access_cards: dictionary that has every Accesscard.
    """

    while True:
        line = input("command> ")

        if line == "":
            break
        strings = line.split()
        command = strings[0]

        if len(strings) >= 2:
            card_id = strings[1]
            card = only_errors(strings, ALL_CODES, access_cards)

            if card is None:  # card is None only when error is raised.
                continue

        if command == "list" and len(strings) == 1:
            card_ids = sorted(access_cards.keys())
            for card_id in card_ids:
                card = access_cards[card_id]
                card.info()

        elif command == "info" and len(strings) == 2:
            card.info()

        elif command == "access" and len(strings) == 3:
            door_id = strings[2]
            access = card.check_access(door_id)
            if access:
                access = "access"
            else:
                access = "no access"

            print("Card {} ( {} ) has {} to "
                  "door {}".format(card_id, card.get_name(),
                                   access, door_id))

        elif command == "add" and len(strings) == 3:
            access_code = strings[2]
            card.add_access(access_code)

        elif command == "merge" and len(strings) == 3:
            card_id_from = strings[2]
            card.merge(access_cards[card_id_from])

        elif command == "quit":
            print("Bye!")
            return
        else:
            print("Error: unknown command.")


def main():

    reading_ok, access_cards = reading_and_sorting()
    ALL_CODES = get_all_codes(DOORCODES)

    if reading_ok:  # stops the program if something went wrong.
        operating(ALL_CODES, access_cards)


main()
