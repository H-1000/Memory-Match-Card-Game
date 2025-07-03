# Memory-Match-Card-Game
This project implements the core gameplay for a two-player Memory Match Card Game. Players take turns revealing pairs of cards from a shuffled 4x4 grid, aiming to match cards with the same number. Different card types — standard, bonus, and penalty — introduce unique scoring and gameplay mechanics:

Standard Cards: Matching them gives points.

Bonus Cards: Matching both can give extra points or an extra turn; revealing them individually also affects the score.

Penalty Cards: Matching both can subtract points or skip a turn; revealing them individually penalizes the player.

The game continues until all card pairs are matched and removed from the grid. At the end, the player with the highest score is declared the winner. If both players have the same score, the game results in a tie.

Features
Dynamic card grid with face-up and face-down states.

Turn-based gameplay supporting two players.

Custom scoring rules for standard, bonus, and penalty cards.

Automatic end-game detection and winner announcement.

Tracks game duration.

How to Play
Players alternate turns, choosing two cards by their coordinates.

If the cards match, special rules apply based on their type.

Scores update automatically, and matched cards are removed.

The game ends when the grid is empty.
