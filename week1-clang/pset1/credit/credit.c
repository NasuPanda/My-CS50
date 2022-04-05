#include <cs50.h>
#include <stdio.h>

// Note
// 数字を10のx乗で割った余りは下からx桁の値になる
// 123456789 % 100 => 89
// 数字を10のx乗で割ると下からx桁が切り捨てられる
// 123456789 / 100 => 1234567

// American Expressは15桁の数字を使い、
// MasterCardは16桁の数字を使い、
// Visaは13桁あるは16桁の数字を使っています。

// すべてのAmerican Expressの番号は34または37で始まり、
// ほとんどのMasterCardの番号は51、52、53、54、または55から始まります
// そして、すべてのVisaの番号は4から始まります。

int check_sum_first();
int check_sum_second();
bool validate_card();
int get_number_of_digits();
string judge_card_type();

int main(void)
{
    long card_number = get_long("Number: ");
    bool is_valid = validate_card(card_number);
    if (!is_valid)
    {
        printf("INVALID\n");
    }
    else
    {
        string card_type = judge_card_type(card_number);
        printf("%s\n", card_type);
    }
}

// 数字の最後から2番目の数字から始め、1桁おきに2を掛け、それらの数を合計する
int check_sum_first(long number)
{
    int digit;
    int sum = 0;

    while (number)
    {
        // %100で下から2桁、/10で下から1桁を切り捨て
        digit = (number % 100) / 10;
        // 二桁以上の場合は1桁ごとに分解して計算
        if (digit*2 > 10)
        {
            sum += (digit * 2 / 10);
            sum += (digit * 2 % 10);
        }
        else
        {
            sum += digit * 2;
        }
        number /= 100;
    }
    return sum;
}

// firstで乗算されなかった桁の数を合計する
int check_sum_second(long number)
{
    int digit;
    int sum = 0;

    while (number)
    {
        // %10で下から1桁
        digit = (number % 10);
        sum += digit;
        number /= 100;
    }
    return sum;
}

// luhn's algorithm による判定
bool validate_card(long card_number)
{
    // Initialize valid string
    bool is_valid;

    // Get result of calculation steps
    int first = check_sum_first(card_number);
    int second = check_sum_second(card_number);
    int check_sum_result = first + second;
    // Get card number of digits
    int digits = get_number_of_digits(card_number);

    // if last digit is 0 / number of digits is 13, 15, or 16.
    if (check_sum_result%10==0 || digits==13 || digits==15 || digits==16)
    {
        is_valid =  true;
    }
    else
    {
        is_valid =  false;
    }
    return is_valid;
}

// カードの桁数を返す
int get_number_of_digits(long card_number)
{
    int count = 0;
    while (card_number)
    {
        card_number /= 10;
        count++;
    }
    return count;
}

// カードのタイプを判定する
string judge_card_type(long card_number)
{
    int card_digits = get_number_of_digits(card_number);
    string card_type;

    // 上から二桁に変換する
    for(int i=1; i<=card_digits-2; i++)
    {
        card_number /= 10;
    }

    if (card_number==34 || card_number==37)
    {
        card_type = "AMEX";
    }
    else if (card_number==51 || card_number==52 || card_number==53 || card_number==54 || card_number==55)
    {
        card_type = "MASTERCARD";
    }
    else
    {
        card_number /= 10;
        if (card_number == 4)
        {
            card_type = "VISA";
        }
        else
        {
            card_type = "INVALID";
        }
    }

    return card_type;
}