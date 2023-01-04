#include <iostream>

enum rps
{
    ROCK = 'A',
    PAPER = 'B',
    SCISSORS = 'C',
    LOSS = 0,
    DRAW = 3,
    WIN = 6
};

int shape_value(const int &c) { return c - 64; }

int score_round(char &opp, char &result)
{
    // adding the result value to score
    int score = 3 * ((int)result - 88);

    // selecting shape that would win the round
    if (score == WIN)
    {
        switch (opp)
        {
        case ROCK: return score + shape_value(PAPER);
        case PAPER: return score + shape_value(SCISSORS);
        default: return score + shape_value(ROCK);
        }
    }

    // selecting shape that would lose the round
    if (score == LOSS)
    {
        switch (opp)
        {
        case ROCK: return score + shape_value(SCISSORS);
        case PAPER: return score + shape_value(ROCK);
        default: return score + shape_value(PAPER);
        }
    }

    // selecting same shape as opponent
    return score + shape_value(opp);
}

int main()
{
    freopen("actual.txt", "r", stdin);

    // calculating the total score for rounds
    int total_score = 0;
    char opponent, result;
    while (scanf(" %c %c", &opponent, &result) != EOF)
    {
        total_score += score_round(opponent, result);
    }

    std::cout << std::boolalpha << (total_score == 12429) << std::endl;
    return 0;
}