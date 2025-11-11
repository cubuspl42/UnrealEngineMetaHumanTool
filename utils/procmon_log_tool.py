import argparse
import csv
import sys
import re

from enum import Enum

class LogField(Enum):
    TIME_OF_DAY = "Time of Day"
    PROCESS_NAME = "Process Name"
    PID = "PID"
    OPERATION = "Operation"
    PATH = "Path"
    RESULT = "Result"
    DETAIL = "Detail"

def main():
    parser = argparse.ArgumentParser(description="Extract specific field from Procmon CSV log.")
    parser.add_argument("logfile", help="Path to the Procmon CSV log file.")
    parser.add_argument("--extract", required=True, choices=[field.value for field in LogField],
                        help="The field to extract from the log entries.")
    parser.add_argument("--filter", help="Regex to filter the extracted field values.")
    
    args = parser.parse_args()
    
    regex = re.compile(args.filter) if args.filter else None

    try:
        with open(args.logfile, mode='r', newline='', encoding='utf-8') as csvfile:
            reader = csv.DictReader(csvfile)
            for row in reader:
                value = row[args.extract]
                if regex is None or regex.search(value):
                    print(value)
    except FileNotFoundError:
        print(f"Error: File '{args.logfile}' not found.", file=sys.stderr)
        sys.exit(1)
    except KeyError:
        print(f"Error: Field '{args.extract}' not found in the log file.", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()
