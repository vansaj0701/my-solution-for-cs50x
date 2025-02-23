import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: dna.py ./csv ./textfile")

    # TODO: Read database file into a variable
    data = []
    STRs = {}
    with open(sys.argv[1]) as csvfile:
        csv_reader = csv.DictReader(csvfile)
        headers = csv_reader.fieldnames
        for row in csv_reader:
            data.append(row)

        for header in headers[1:]:
            STRs[header] = 0

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as textfile:
        contents = textfile.read()

    # TODO: Find longest match of each STR in DNA sequence
    for i in STRs:
        STRs[i] = longest_match(contents, i)

    # TODO: Check database for matching profiles
    for person in data:
        len_seq = 0
        match_found = False
        for seq in STRs:
            if int(person[seq]) == STRs[seq]:
                len_seq += 1
                if len_seq == len(STRs):
                    match_found = True
                    print(person['name'])
                    break
    if not match_found:
        print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

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
