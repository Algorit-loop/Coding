from collections import deque

class PuzzleNode:
    def __init__(self, state, path=None):
        self.state = state
        self.path = path if path is not None else []

    def __hash__(self):
        return hash(self.state)

    def __eq__(self, other):
        if isinstance(other, PuzzleNode):
            return self.state == other.state
        return False

def sliding_puzzle_bfs(initial, goal, n):
    initial_state = tuple(initial)
    goal_state = tuple(goal)
    
    start_node = PuzzleNode(initial_state, [])
    queue = deque([start_node])
    visited = set([start_node.state])
    
    while queue:
        current_node = queue.popleft()
        
        if current_node.state == goal_state:
            return current_node.path, current_node.state
        
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
                visited.add(new_state)
                new_node = PuzzleNode(new_state, current_node.path + [move])
                queue.append(new_node)
                
    return None, None

initial = [1, 2, 3,
            4, 0, 5,
            6, 7, 8]
goal =    [1, 2, 3,
            4, 5, 0,
            6, 7, 8]

path, final_state = sliding_puzzle_bfs(initial, goal, 3)
if path is not None:
    print("BFS: Đã tìm được lời giải với các bước di chuyển:")
    print(path)
else:
    print("BFS: Không tìm được lời giải.")
