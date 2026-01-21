"""
See https://adventofcode.com/2025/day/5
"""

class Database:
    def __init__(self, input_data):
        split_input_data = input_data.split("\n\n")
        self.id_range, self.id = [elem for elem in split_input_data]

        self.id_range = self.id_range.split()
        self.id = [int(a) for a in self.id.split()]
        self.id_set = {(int(a), int(b)) for a, b in (r.split("-") for r in self.id_range)}


    def is_ingredient_fresh(self, ingredient_id):
        """
        Determines if the ingredient is fresh if the ingredient_id is within any fresh_ingredients_id_range, inclusively.
        :param ingredient_id: The ingredient id to check if fresh
        :return: Returns True if the ingredient is fresh, otherwise returns False
        """
        for r in self.id_set:
            if r[1] >= ingredient_id >= r[0]:
                return True
        return False

    @property
    def check_ingredient_list(self):
        """
        :return: The total number of fresh ingredients
        """
        count  = 0
        for i in self.id:
            if self.is_ingredient_fresh(i):
                count += 1
        return count

    @property
    def check_ingredient_range(self):
        """
        Returns the total number within all ingredient ranges
        :return: The total number within all ingredient range, inclusively.
        """

        set_of_id = [i for r in self.id_set for i in range(r[0], r[1] + 1)]
        set_of_id = set(set_of_id)

        return len(set_of_id)


def test_function():
    input_test = (  "3-5\n"
                    "10-14\n"
                    "16-20\n"
                    "12-18\n"
                    "\n"
                    "1\n"
                    "5\n"
                    "8\n"
                    "11\n"
                    "17\n"
                    "32\n")

    test_database = Database(input_test)

    assert(test_database.is_ingredient_fresh(1) == False)
    assert(test_database.is_ingredient_fresh(5) == True)
    assert(test_database.is_ingredient_fresh(8) == False)
    assert(test_database.is_ingredient_fresh(11) == True)
    assert(test_database.is_ingredient_fresh(17) == True)
    assert(test_database.is_ingredient_fresh(32) == False)

    assert(test_database.check_ingredient_list == 3)
    assert(test_database.check_ingredient_range == 14)
    print("-- All Tests Passed --")

    return True

def main():
    test_function()

    filename = "in.txt"
    with open(filename, "r") as file:
        import time
        start = time.time()
        input_database = Database(file.read())
        print(input_database.check_ingredient_list)
        end = time.time()
        print(end - start)

        print(input_database.check_ingredient_range)




if __name__ == "__main__":
    main()

