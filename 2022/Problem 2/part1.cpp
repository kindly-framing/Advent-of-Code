#include <iostream>

/**
 * @brief Constants for rock, paper, and scissors following the guide given in
 * the problem.
 *
 */
enum rock_paper_scissors
{
    ROCK = 'A',
    PAPER = 'B',
    SCISSORS = 'C',
    LOSS = 0,
    DRAW = 3,
    WIN = 6
};

/**
 * @brief Calculates the score of the round of rock, paper, scissors following
 * formula given in the problem.
 *
 * (score = player selection + outcome of the round)
 * player selection: 1 for Rock, 2 for Paper, 3 for Scissors
 * outcome of the round: 0 for Loss, 3 for Draw, 6 for Win
 *
 * @param o Opponent's selection
 * @param p Player's selection
 * @return Calculated score for the round of rock, paper, scissors.
 */
int score_round(const char &o, const char &p)
{
    // adding player selection to score
    int score = (int)p - 87;

    // converting because the player uses different constants than opponent
    char player_to_opponent = char((int)p - 23);

    // adding outcome to score
    if (o == player_to_opponent)
    {
        return score + DRAW;
    }
    bool is_win = (o == ROCK && player_to_opponent == PAPER) ||
                  (o == PAPER && player_to_opponent == SCISSORS) ||
                  (o == SCISSORS && player_to_opponent == ROCK);
    return (is_win) ? score + WIN : score + LOSS;
}

int main()
{
    freopen("actual.txt", "r", stdin); // using test file as input

    // calculating the total score for rounds
    int total_score = 0;
    char opponent, player;
    while (scanf(" %c %c", &opponent, &player) != EOF)
    {
        total_score += score_round(opponent, player);
    }

    std::cout << std::boolalpha << (total_score == 9759) << std::endl;
    return 0;
}