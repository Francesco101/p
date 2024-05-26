import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):

    # DECLARE days14: (holds last 15 days)
    days14 = {}

    # ASSIGN days14:
    for row in reader:
        state = row["state"]
        # update days14
        if not (row["state"] in dict.keys(days14)):
            days14[row["state"]] = []
        if len(days14[state]) == 15:
            days14[state] = days14[state][1:]
        days14[state].append(int(row["cases"]))

    # INITIALIZE new_cases
    new_cases = {}
    for state in dict.keys(days14):
        temp = days14[state].copy()
        for i in range(1, 15):
            temp[i] = days14[state][i] - days14[state][i - 1]
        new_cases[state] = temp[1:]

    return new_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        # Get last week average
        last_avg = round(sum(new_cases[state][7:]) / 7)
        # Get before last week average
        before_avg = round(sum(new_cases[state][:7]) / 7)

        # Get percentage changes
        try:
            percentage = abs(round(100 * (last_avg - before_avg) / before_avg, 2))
        except ZeroDivisionError:
            percentage = f">100"

        if percentage == 100:
            percentage = ">100"

        if last_avg > before_avg:
            msg = "an increase"
        else:
            msg = "a decrease"

        print(f"{state} had a 7-day average of {last_avg} and {msg} of {percentage}%.")


main()
