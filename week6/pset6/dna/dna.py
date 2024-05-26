import csv
import sys


def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py [file name].csv [file name].txt")
        sys.exit(-1)

    database = []
    csvheader = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        csvheader = reader.fieldnames
        for person in reader:
            x = dict()
            x['name'] = person['name']
            for key in csvheader[1:]:
                x[key] = int(person[key])
            database.append(x)

    dna = ""
    with open(sys.argv[2]) as file:
        seq = file.read()
        for base in seq:
            dna = dna + base

    genes_count = {}
    for gene in csvheader[1:]:
        genes_count[gene] = longest_match(dna, gene)

    match = "No match"
    ''' person is a dict() '''
    for person in database:
        matchfb = True
        for gene in csvheader[1:]:
            if genes_count[gene] != person[gene]:
                matchfb = False
                break
        if matchfb == True:
            match = person["name"]
            break

    print(match)
    sys.exit(0)


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence"""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
