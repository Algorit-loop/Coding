import heapq

class PuzzleNode:
    def __init__(self, state, path=None, g=0, h=0):
        self.state = state
        self.path = path if path is not None else []
        self.g = g
        self.h = h

    def __lt__(self, other):
        return (self.g + self.h) < (other.g + other.h)

    def __hash__(self):
        return hash(self.state)

    def __eq__(self, other):
        return isinstance(other, PuzzleNode) and self.state == other.state

def manhattan_distance(state, goal, n):
    goal_positions = {val: (idx // n, idx % n) for idx, val in enumerate(goal) if val != 0}
    return sum(abs(x - goal_positions[val][0]) + abs(y - goal_positions[val][1])
               for idx, val in enumerate(state) if val != 0 and val in goal_positions
               for x, y in [(idx // n, idx % n)])

def sliding_puzzle_astar(initial, goal, n):
    initial_state, goal_state = tuple(initial), tuple(goal)
    start_h = manhattan_distance(initial_state, goal_state, n)
    start_node = PuzzleNode(initial_state, [], 0, start_h)
    
    open_set = []
    heapq.heappush(open_set, start_node)
    visited = {start_node.state: start_node.g}
    
    while open_set:
        current_node = heapq.heappop(open_set)
        
        if current_node.state == goal_state:
            return current_node.path, current_node.state
        
        zero_index = current_node.state.index(0)
        x, y = divmod(zero_index, n)
        moves = [(-1, 0, 'Up'), (1, 0, 'Down'), (0, -1, 'Left'), (0, 1, 'Right')]
        
        for dx, dy, move in moves:
            newx, newy = x + dx, y + dy
            if 0 <= newx < n and 0 <= newy < n:
                new_index = newx * n + newy
                new_state = list(current_node.state)
                new_state[zero_index], new_state[new_index] = new_state[new_index], new_state[zero_index]
                new_state = tuple(new_state)
                new_g = current_node.g + 1
                new_h = manhattan_distance(new_state, goal_state, n)
                
                if new_state not in visited or new_g < visited[new_state]:
                    visited[new_state] = new_g
                    heapq.heappush(open_set, PuzzleNode(new_state, current_node.path + [move], new_g, new_h))
    
    return None, None


initial = [1, 2, 3,
           4, 0, 5,
           6, 7, 8]
goal =    [1, 2, 3,
           4, 5, 6,
           7, 8, 0]
path, _ = sliding_puzzle_astar(initial, goal, 3)
print("A*:", path if path else "Không tìm được lời giải.")
