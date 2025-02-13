from collections import deque

def bfs_shortest_path(graph, start, goal):
    queue = deque()
    queue.append((start, [start]))
    visited = set()
    
    while queue:
        current, path = queue.popleft()
        
        if current == goal:
            return path

        if current in visited:
            continue
        visited.add(current)
        
        for neighbor in graph.get(current, []):
            if neighbor not in visited:
                queue.append((neighbor, path + [neighbor]))
    
    return None

graph = {
    0: [1, 2],
    1: [0, 3, 4],
    2: [0, 5],
    3: [1],
    4: [1, 5],
    5: [2, 4]
}
start_node = 0
goal_node = 5

path = bfs_shortest_path(graph, start_node, goal_node)
if path is not None:
    print(f"Đường đi ngắn nhất từ {start_node} đến {goal_node} là: {path}")
else:
    print(f"Không có đường đi từ {start_node} đến {goal_node}.")
