import random
import time
import math

def print_board(board):
    print("\n")
    print(f" {board[0]} | {board[1]} | {board[2]}     1 | 2 | 3")
    print("---|---|---   ---|---|---")
    print(f" {board[3]} | {board[4]} | {board[5]}     4 | 5 | 6")
    print("---|---|---   ---|---|---")
    print(f" {board[6]} | {board[7]} | {board[8]}     7 | 8 | 9")
    print("\n")

def check_winner(board):
    win_combinations = [
        (0, 1, 2), (3, 4, 5), (6, 7, 8), 
        (0, 3, 6), (1, 4, 7), (2, 5, 8), 
        (0, 4, 8), (2, 4, 6)            
    ]
    for combo in win_combinations:
        if board[combo[0]] == board[combo[1]] == board[combo[2]] and board[combo[0]] != ' ':
            return board[combo[0]]
    if ' ' not in board:
        return 'Empate'
    return None

def get_player_move(board):
    while True:
        try:
            move = int(input("Sua vez! Escolha uma posição (1-9): "))
            if move < 1 or move > 9:
                print("Posição inválida. Por favor, escolha um número entre 1 e 9.")
            elif board[move - 1] != ' ':
                print("Essa posição já está ocupada. Tente outra.")
            else:
                return move - 1 
        except ValueError:
            print("Entrada inválida. Por favor, digite um número.")

def minimax(board, depth, is_maximizing, computer_player, human_player):
    winner = check_winner(board)
    if winner == computer_player:
        return 10 - depth
    if winner == human_player:
        return depth - 10
    if winner == 'Empate':
        return 0

    if is_maximizing:
        best_score = -math.inf
        for i in range(9):
            if board[i] == ' ':
                board[i] = computer_player
                score = minimax(board, depth + 1, False, computer_player, human_player)
                board[i] = ' '
                best_score = max(score, best_score)
        return best_score
    else:
        best_score = math.inf
        for i in range(9):
            if board[i] == ' ':
                board[i] = human_player
                score = minimax(board, depth + 1, True, computer_player, human_player)
                board[i] = ' '
                best_score = min(score, best_score)
        return best_score

def get_computer_move(board, computer_player, human_player):
    best_score = -math.inf
    best_move = -1
    
    for i in range(9):
        if board[i] == ' ':
            board[i] = computer_player
            score = minimax(board, 0, False, computer_player, human_player)
            board[i] = ' '
            if score > best_score:
                best_score = score
                best_move = i
    
    return best_move

def play_game():
    board = [' '] * 9
    human_player = 'O'
    computer_player = 'X'
    current_player = human_player 

    print("Bem-vindo ao Jogo da Velha contra uma IA!")
    print("Você joga como 'O'. O computador é 'X'. Tente vencer se puder!")
    print_board(board)

    while True:
        if current_player == human_player:
            move = get_player_move(board)
            board[move] = human_player
        else:
            print("Vez do computador...")
            time.sleep(0.5)
            move = get_computer_move(board, computer_player, human_player)
            if move is not None:
                board[move] = computer_player
        
        print_board(board)
        
        winner = check_winner(board)
        if winner:
            if winner == 'Empate':
                print("O jogo empatou!")
            else:
                print(f"O jogador '{winner}' venceu!")
            break

        current_player = computer_player if current_player == human_player else human_player

if __name__ == "__main__":
    play_game()
    while True:
        again = input("\nDeseja jogar novamente? (s/n): ").lower()
        if again == 's':
            play_game()
        elif again == 'n':
            print("Obrigado por jogar!")
            break
        else:
            print("Opção inválida.")
