import csv
import sys

def get_STR_repeats(dna_sequence, STR):
    """STRの最大反復回数を取得する"""
    STR_len = len(STR)

    max_repeats = 0

    for i in range(len(dna_sequence)):
        repeats = 0

        # N文字ずつ判定する
        if dna_sequence[i:i+STR_len] == STR:
             repeats += 1

            # 連続しているSTRが現れる限りrepeatsをインクリメントする
             while (dna_sequence[i : i + STR_len] == dna_sequence[i + STR_len : i + 2 * STR_len]):
                 repeats += 1
                 i += STR_len

        # max_repeatsの更新
        if repeats > max_repeats:
            max_repeats = repeats

    return max_repeats

def get_STR(csv_path):
    """STRのバリエーションを取得する"""
    with open(csv_path, newline='') as f:
        reader = csv.reader(f, delimiter=',')
        for row in reader:
            # 最初の行のnameを除いて読み込む
            return row[1:]

def read_database(csv_path, STR):
    """CSVデータベースを読み込み"""
    database = []
    with open(csv_path) as f:
        reader = csv.DictReader(f)

        for data in reader:

            for s in STR:
                # 型キャスト
                data[s] = int(data[s])

            database.append(data)

    return database

def check_dna(person, database, STR):
    """DNA配列の照合"""
    for data in database:
        # Initialize judgement array
        is_ok = [False] * len(STR)

        for i, s in enumerate(STR):
            if data[s] == person[s]:
                is_ok[i] = True

        if not False in is_ok:
            return data["name"]

    return "No match"

def main():
    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna_sequences.py data.csv sequence.txt")

    csv_path = sys.argv[1]
    txt_path = sys.argv[2]

    # Get STR variation
    STR = get_STR(csv_path)

    # Read csv file
    dna_database = read_database(csv_path, STR)

    # Read text file
    with open(txt_path) as f:
        sequence = f.read()

    person = {}
    for i in STR:
        person[i] = get_STR_repeats(sequence, i)

    result = check_dna(person, dna_database, STR)

    print(result)

if __name__ == "__main__":
    main()
