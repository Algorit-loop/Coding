class PuzzleNode:
    def __init__(self, state, path=None):
        self.state = state
        self.path = path if path is not None else []
        
    def __hash__(self):
        return hash(self.state)
    
    def __eq__(self, other):
        return isinstance(other, PuzzleNode) and self.state == other.state

def sliding_puzzle_dfs_recursive(current_node, goal_state, n, visited):
    if current_node.state == goal_state:
        return current_node.path, current_node.state

    visited.add(current_node.state)
    zero_index = current_node.state.index(0)
    x, y = divmod(zero_index, n)
    moves = []
    if x > 0:
        moves.append((-1, 0, 'Up'))
    if x < n - 1:
        moves.append((1, 0, 'Down'))
    if y > 0:
        moves.append((0, -1, 'Left'))
    if y < n - 1:
        moves.append((0, 1, 'Right'))

    for dx, dy, move in moves:
        newx, newy = x + dx, y + dy
        new_index = newx * n + newy

        new_state = list(current_node.state)

        new_state[zero_index], new_state[new_index] = new_state[new_index], new_state[zero_index]
        new_state = tuple(new_state)

        if new_state not in visited:
            new_node = PuzzleNode(new_state, current_node.path + [move])
            result_path, result_state = sliding_puzzle_dfs_recursive(new_node, goal_state, n, visited)
            if result_path is not None:
                return result_path, result_state

    return None, None

def sliding_puzzle_dfs(initial, goal, n):
    initial_state = tuple(initial)
    goal_state = tuple(goal)
    start_node = PuzzleNode(initial_state, [])

    visited = set()
    return sliding_puzzle_dfs_recursive(start_node, goal_state, n, visited)

initial = [1, 2, 3,
            4, 0, 5,
            6, 7, 8]
goal =    [1, 2, 3,
            4, 5, 0,
            6, 7, 8]

path, final_state = sliding_puzzle_dfs(initial, goal, 3)
if path is not None:
    print("DFS: Đã tìm được một lời giải:")
    print(path)
else:
    print("DFS: Không tìm thấy lời giải.")
