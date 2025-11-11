import argparse
import sys

def main():
    parser = argparse.ArgumentParser(description="Build a semicolon-separated enviroment variable")
    parser.add_argument("listfile", help="Path to a text file containing one entry per line.")
    
    args = parser.parse_args()
    
    try:
        with open(args.listfile, mode='r', encoding='utf-8') as file:
            entries = [line.strip() for line in file if line.strip()]
            env_var_value = ';'.join(entries)
            print(env_var_value)
    except FileNotFoundError:
        print(f"Error: File '{args.listfile}' not found.", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()
