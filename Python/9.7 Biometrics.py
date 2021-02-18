# TIE-02101 Ohjelmointi1
# Lari Lantonen, Lari.Lantonen@tuni.fi 283531
# Tehtävän 9.7. ratkaisu:
# Ohjelma, joka vertailee passikuvista saatuja biometrisiä tietoja
import math


def printing(registry, key):
    """search ja match toimintojen printtaus funktio."""

    string = ""
    biometric = registry[key][1]

    # name, passport, biometric
    print(registry[key][0], key, sep=";", end="")

    for number in biometric:
        number = format(number, ".2f")
        string += ";" + str(number)
    print(string)


def read_biometric_registry(filename):
    """avaa tiedostosta halutut tiedot dictionaryyn"""
    result = {}

    handled_passports = []

    try:
        with open(filename, "r") as file_object:

            for row in file_object:
                fields = row.rstrip().split(";")

                if len(fields) != 8:
                    print("Error: there is a wrong number of fields "
                          "in the file:")
                    print("'", row, "'", sep="")
                    return None

                name = fields[0] + ", " + fields[1]
                passport = fields[2]

                if passport in handled_passports:
                    print("Error: passport number", passport,
                          "found multiple times.")
                    return None
                else:
                    handled_passports.append(passport)

                biometrics = []

                for i in range(3, 8):
                    try:
                        id_value = float(fields[i])
                    except ValueError:
                        print("Error: there's a non-numeric value on the row:")
                        print("'", row, "'", sep="")
                        return None

                    if 0 <= id_value <= 3.0:
                        biometrics.append(id_value)
                    else:
                        print("Error: there is an erroneous value in the file:")
                        print("'", row, "'", sep="")
                        return None

                result[passport] = [name, biometrics]
                # save the read information in the result data structure
        return result

    except FileNotFoundError:
        print("Error: file", filename, "could not be opened.")
        return None


def euclidean_distance(x, y):
    """Laskee biometrisien tietojen perusteella onko kyseessä sama henkilö ja
    palauttaa lasketun euklidinen etäisyyden, jos se on alla 0.1"""

    add = (x[0] - y[0]) ** 2

    for i in range(1, len(x)):
        add += (x[i] - y[i]) ** 2
    distance = math.sqrt(add)

    if distance < 0.1:
        return distance
    else:
        return None


def execute_match(registry):
    """suorittaa syötetiedostosta luetuille tiedoille tarkistus, onko sama
    henkilö "soluttautunut" maahan usealla eri henkilöllisyydellä"""

    dont_check = []  # kaikki passit joita ei tarvitse enää käydä läpi
    passports = {}  # kerätään saman henkilön passit sanakirjaksi
    rest_of_registry = registry.copy()

    for passport in registry:  # passi kerrallaan rekisteristä
        if passport in dont_check:
            pass
        else:
            del rest_of_registry[passport]

            # käydään kaikki nykyisestä
            # passista eteenpäin läpi/ paitsi jo matchin saaneet passit
            for next_passport in rest_of_registry:
                biometric = registry[passport][1]
                match = euclidean_distance(biometric, registry[next_passport][1])

                if match is not None:

                    #  passien lisäys dictiin ja ei tarkistettaviin
                    if passport not in passports:
                        passports[passport] = []
                        passports[passport].append(next_passport)
                        dont_check.append(next_passport)
                    else:
                        passports[passport].append(next_passport)
                        dont_check.append(next_passport)

    if len(passports) != 0:

        for passport in passports:

            print("Probably the same person:")
            printing(registry, passport)

            for key in passports[passport]:
                printing(registry, key)
            print()
    else:
        print("No matching persons were found.")


def execute_search(registry):
    """search toiminto tarkistaa, kenelle syötetyt biometriset
    tunnusluvut kuuluvat"""

    suspect_found = False
    measurement_points = input("enter 5 measurement points "
                               "separated by semicolon: ").split(";")

    while len(measurement_points) != 5:
        print("Error: wrong number of measurements. Try again.")
        measurement_points = input("enter 5 measurement points "
                                   "separated by semicolon: ").split(";")

    try:
        for i in range(len(measurement_points)):
            measurement_points[i] = float(measurement_points[i])

        for key in registry:

            biometric = registry[key][1]
            distance = euclidean_distance(biometric, measurement_points)

            if distance is not None:
                if not suspect_found:
                    print("Suspects found:")
                suspect_found = True
                printing(registry, key)
            else:
                pass

        if not suspect_found:
            print("No suspects were found.")
        print()

    except ValueError:
        print("Error: enter floats only. Try again.")
        execute_search(registry)


def command_line_user_interface(registry):
    """komento funktio, jolla määritellään mitä haluaa käyttäjä haluaa tehdä"""

    while True:
        command = input("command [search/match/<enter>] ")

        if command == "":
            return
        elif command == "match":
            execute_match(registry)
        elif command == "search":
            execute_search(registry)
        else:
            print("Error: unknown command '", command,
                  "': try again.", sep="")


def main():
    registry_file = input("Enter the name of the registry file: ")

    biometric_registry = read_biometric_registry(registry_file)
    if biometric_registry is not None:
        command_line_user_interface(biometric_registry)


main()
