#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Jogo da Velha (usuário vs programa) com:
1) Criação de um grafo de todos os estados possíveis.
2) Heurística baseada em "forks" e vitórias forçadas a favor do programa (O).
3) Busca A* aplicada em um grafo comprimido (nós nas jogadas do programa),
   onde a resposta do oponente é escolhida como a pior para o programa (melhor para o usuário).
Execute este arquivo diretamente para jogar no terminal.
"""

from collections import deque, defaultdict
from dataclasses import dataclass
from typing import Dict, List, Optional, Tuple, Set
import math
import sys

# Convenções
# - Usuário joga com 'X' (humano), Programa joga com 'O' (IA).
# - O usuário começa (padrão mais comum). Você pode mudar USER_FIRST para False se quiser.
USER = 'X'
AI = 'O'
EMPTY = ' '
USER_FIRST = True

# Todas as linhas vencedoras do tabuleiro 3x3
LINES = [
    (0, 1, 2),
    (3, 4, 5),
    (6, 7, 8),
    (0, 3, 6),
    (1, 4, 7),
    (2, 5, 8),
    (0, 4, 8),
    (2, 4, 6),
]

Board = Tuple[str, ...]  # tupla de 9 posições

@dataclass(frozen=True)
class Node:
    board: Board
    turn: str  # de quem é a vez: 'X' ou 'O'

def print_board(b: Board) -> None:
    def sym(i):
        return b[i] if b[i] != EMPTY else str(i + 1)
    print(f" {sym(0)} | {sym(1)} | {sym(2)} ")
    print("---|---|---")
    print(f" {sym(3)} | {sym(4)} | {sym(5)} ")
    print("---|---|---")
    print(f" {sym(6)} | {sym(7)} | {sym(8)} ")

def winner(b: Board) -> Optional[str]:
    for a, c, d in LINES:
        if b[a] != EMPTY and b[a] == b[c] == b[d]:
            return b[a]
    return None

def is_full(b: Board) -> bool:
    return all(x != EMPTY for x in b)

def is_terminal(b: Board) -> bool:
    return winner(b) is not None or is_full(b)

def next_player(b: Board) -> str:
    x = sum(1 for v in b if v == USER)
    o = sum(1 for v in b if v == AI)
    return USER if x == o else AI

def legal_moves(b: Board) -> List[int]:
    return [i for i, v in enumerate(b) if v == EMPTY]

def place(b: Board, i: int, p: str) -> Board:
    lst = list(b)
    lst[i] = p
    return tuple(lst)

def immediate_winning_moves(b: Board, p: str) -> List[int]:
    res = []
    for i in legal_moves(b):
        nb = place(b, i, p)
        if winner(nb) == p:
            res.append(i)
    return res

def count_forks(b: Board, p: str) -> int:
    """Conta jogadas que criam 2+ vitórias imediatas no próximo lance de p."""
    forks = 0
    for i in legal_moves(b):
        nb = place(b, i, p)
        wins = len(immediate_winning_moves(nb, p))
        if wins >= 2:
            forks += 1
    return forks

def heuristic(b: Board) -> float:
    """
    Heurística (menor é melhor para o programa/O) baseada em:
    - Vitória imediata de O => valor muito baixo
    - Derrota imediata (X pode ganhar) => penalização alta
    - Diferença de forks (O - X) com peso
    - Leve preferência por centro/cantos quando nada crítico
    Observação: admissibilidade perfeita não é necessária aqui; é uma heurística preferencial.
    """
    if winner(b) == AI:
        return -1000.0
    if winner(b) == USER:
        return 1000.0
    # Se X tem vitória imediata disponível, grande penalidade
    x_wins_now = len(immediate_winning_moves(b, USER))
    if x_wins_now > 0:
        return 500.0 + 50.0 * (x_wins_now - 1)
    # Se O tem vitória imediata, grande bônus
    o_wins_now = len(immediate_winning_moves(b, AI))
    if o_wins_now > 0:
        return -500.0 - 50.0 * (o_wins_now - 1)

    o_forks = count_forks(b, AI)
    x_forks = count_forks(b, USER)

    h = 0.0
    h += 50.0 * (x_forks)   # penalizar forks do oponente
    h += -60.0 * (o_forks)  # favorecer nossos forks (peso levemente maior)

    # bônus suave por ocupar o centro/cantos (estratégico em 3x3)
    center = 4
    corners = [0, 2, 6, 8]
    if b[center] == AI:
        h -= 3.0
    for c in corners:
        if b[c] == AI:
            h -= 1.0
    return h

# -------- Criação do grafo completo --------
def build_full_graph() -> Dict[Node, List[Node]]:
    """
    Gera o grafo de TODOS os estados possíveis a partir do tabuleiro vazio,
    alternando turnos legalmente. Cada Node inclui o tabuleiro e o jogador da vez.
    """
    start_board: Board = tuple([EMPTY] * 9)
    start_node = Node(start_board, USER if USER_FIRST else AI)
    graph: Dict[Node, List[Node]] = defaultdict(list)
    visited: Set[Node] = set()
    q = deque([start_node])

    while q:
        node = q.popleft()
        if node in visited:
            continue
        visited.add(node)

        b, p = node.board, node.turn
        if is_terminal(b):
            graph[node] = []
            continue

        for i in legal_moves(b):
            nb = place(b, i, p)
            np = USER if p == AI else AI
            child = Node(nb, np)
            graph[node].append(child)
            if child not in visited:
                q.append(child)

    return graph

# -------- Modelo adversário: melhor resposta do usuário --------
def opponent_best_response(b: Board) -> Board:
    """
    Dado um tabuleiro onde é a vez do usuário (X), retorna o tabuleiro após
    a resposta 'pessimista' (melhor para X). Estratégia por prioridades:
    1) Se X pode ganhar agora, faça.
    2) Se O tem vitória imediata, bloqueie.
    3) Crie fork se possível.
    4) Bloqueie fork de O se surgir claro.
    5) Centro, depois cantos, depois laterais.
    """
    # 1) vencer agora
    wins_now = immediate_winning_moves(b, USER)
    if wins_now:
        return place(b, wins_now[0], USER)

    # 2) bloquear vitória imediata de O
    block = immediate_winning_moves(b, AI)
    if block:
        return place(b, block[0], USER)

    # 3) criar fork
    forks = []
    for i in legal_moves(b):
        nb = place(b, i, USER)
        if len(immediate_winning_moves(nb, USER)) >= 2:
            forks.append(i)
    if forks:
        return place(b, forks[0], USER)

    # 4) bloquear fork de O (heurística simples)
    o_forks_cells = []
    for i in legal_moves(b):
        nb = place(b, i, AI)
        if len(immediate_winning_moves(nb, AI)) >= 2:
            o_forks_cells.append(i)
    if o_forks_cells:
        # bloquear ocupando a célula que criaria fork para O
        return place(b, o_forks_cells[0], USER)

    # 5) preferência posicional básica
    preference = [4, 0, 2, 6, 8, 1, 3, 5, 7]
    for i in preference:
        if b[i] == EMPTY:
            return place(b, i, USER)

    return b  # sem mudança (deveria não ocorrer)

# -------- Busca A* "comprimida" (turnos apenas do programa) --------
@dataclass(order=True)
class PQItem:
    f: float
    g: float
    board: Board

def astar_best_move(current: Board) -> int:
    """
    Escolhe a melhor jogada para O a partir do tabuleiro atual.
    A* percorre somente estados nas jogadas de O.
    Entre nossas jogadas, a resposta de X é simulada por opponent_best_response,
    reduzindo o grafo a uma cadeia determinística entre turnos de O.
    """
    if is_terminal(current):
        return -1

    # Se houver vitória imediata, faça
    wins_now = immediate_winning_moves(current, AI)
    if wins_now:
        return wins_now[0]

    # Abrir A*: nó inicial é o estado atual (jogada é de O? se não for, simula resposta de X primeiro)
    start = current
    if next_player(current) == USER:
        # Não é nossa vez; simular a resposta pessimista do usuário e começar do próximo estado
        start = opponent_best_response(current)

    # Estruturas da A*
    import heapq
    openpq: List[PQItem] = []
    came_from: Dict[Board, Optional[Board]] = {start: None}
    best_g: Dict[Board, float] = {start: 0.0}

    start_h = heuristic(start)
    heapq.heappush(openpq, PQItem(f=start_h, g=0.0, board=start))

    goal: Optional[Board] = None

    expanded_limit = 10000  # segurança
    expanded = 0

    while openpq and expanded < expanded_limit:
        current_item = heapq.heappop(openpq)
        s = current_item.board
        g = current_item.g
        expanded += 1

        if winner(s) == AI:
            goal = s
            break
        if is_full(s) and winner(s) is None:
            # empate: aceitar como objetivo se não houver vitória possível
            if goal is None:
                goal = s  # manter como fallback
            # continua para ver se acha vitória
        # Expandir sucessores: é a vez de O neste nó comprimido
        if next_player(s) != AI:
            # Se por algum motivo não for nossa vez (deveria ser), corrige simulando X
            s_after_x = opponent_best_response(s)
            if s_after_x not in came_from:
                came_from[s_after_x] = s
                new_g = g + 1.0
                best_g[s_after_x] = new_g
                heapq.heappush(openpq, PQItem(f=new_g + heuristic(s_after_x), g=new_g, board=s_after_x))
            continue

        for i in legal_moves(s):
            nb = place(s, i, AI)
            # Simular a resposta do usuário (comportamento pessimista)
            if not is_terminal(nb):
                nb = opponent_best_response(nb)
            new_g = g + 1.0
            if nb not in best_g or new_g < best_g[nb]:
                best_g[nb] = new_g
                came_from[nb] = s
                f = new_g + heuristic(nb)
                heapq.heappush(openpq, PQItem(f=f, g=new_g, board=nb))

    # Se não encontramos um "goal" melhor, escolher primeira jogada que minimize a heurística
    if goal is None:
        moves = legal_moves(current)
        best_i = None
        best_val = math.inf
        for i in moves:
            nb = place(current, i, AI)
            if not is_terminal(nb):
                nb = opponent_best_response(nb)
            val = heuristic(nb)
            if val < best_val:
                best_val = val
                best_i = i
        return best_i if best_i is not None else moves[0]

    # Reconstruir a trilha para obter a primeira jogada a partir do estado atual
    # Precisamos mapear "start" (após possível resposta de X) de volta ao "current".
    path: List[Board] = []
    s = goal
    while s is not None:
        path.append(s)
        s = came_from.get(s, None)
    path.reverse()

    # Se current era nossa vez, a primeira transição é o nosso movimento.
    # Se era vez do usuário, já simulamos uma jogada dele, então precisamos calcular a ação a partir de "current".
    def first_ai_move_from(curr: Board, nxt: Board) -> int:
        for i in range(9):
            if curr[i] == EMPTY and nxt[i] == AI:
                return i
        # Se curr não é nossa vez, primeiro simulamos X:
        sim_x = opponent_best_response(curr) if next_player(curr) == USER else curr
        for i in range(9):
            if sim_x[i] == EMPTY and path[0][i] == AI:
                return i
        return -1

    # Determinar o próximo estado após nossa jogada a partir de 'current'
    if next_player(current) == AI:
        # nossa jogada leva a path[0] (ou path[1] dependendo do caso); encontrar índice
        target = path[0]
        return first_ai_move_from(current, target)
    else:
        # era vez do usuário; o estado start = opponent_best_response(current)
        # nossa jogada leva de 'start' a 'path[0]' ou 'path[1]'
        if len(path) == 0:
            # fallback
            moves = legal_moves(current)
            return moves[0] if moves else -1
        target = path[0]
        # Se target == start, então o próximo depois é path[1] (se existir)
        if target == opponent_best_response(current) and len(path) >= 2:
            target = path[1]
        return first_ai_move_from(current, target)

# -------- Jogo interativo --------
def play() -> None:
    print("\n=== Jogo da Velha: Usuário (X) vs Programa (O) ===\n")
    b: Board = tuple([EMPTY] * 9)
    current_turn = USER if USER_FIRST else AI

    # (Opcional) construir o grafo completo antes de jogar, conforme solicitado
    print("Construindo grafo completo de estados... (isso é feito uma vez)")
    full_graph = build_full_graph()
    total_nodes = len(full_graph)
    total_edges = sum(len(v) for v in full_graph.values())
    print(f"Grafo criado: {total_nodes} nós, {total_edges} arestas.\n")

    while True:
        print_board(b)
        w = winner(b)
        if w == USER:
            print("\nVocê venceu! Parabéns!")
            break
        elif w == AI:
            print("\nO programa venceu!")
            break
        elif is_full(b):
            print("\nEmpate!")
            break

        if current_turn == USER:
            # Entrada do usuário
            while True:
                try:
                    raw = input("Sua jogada (1-9): ").strip()
                    if raw.lower() in {"q", "quit", "sair"}:
                        print("Saindo do jogo.")
                        return
                    i = int(raw) - 1
                    if i < 0 or i > 8:
                        raise ValueError
                    if b[i] != EMPTY:
                        print("Casa ocupada. Tente outra.")
                        continue
                    b = place(b, i, USER)
                    current_turn = AI
                    break
                except ValueError:
                    print("Entrada inválida. Digite um número de 1 a 9, ou 'q' para sair.")
        else:
            print("\nPrograma pensando (A*)...")
            mv = astar_best_move(b)
            if mv == -1:
                # sem movimento (terminal)
                current_turn = USER
                continue
            b = place(b, mv, AI)
            print(f"Programa jogou na casa {mv + 1}.")
            current_turn = USER

    print_board(b)
    print("\nFim do jogo.")

if __name__ == "__main__":
    try:
        play()
    except KeyboardInterrupt:
        print("\nInterrompido pelo usuário.")    
