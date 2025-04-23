import heapq

class Id_generator:
    def __init__(self):
        self.min_heap = []  # Куча на минимум
        self.next_min = 1  

    def give_min_id(self) -> int: 
        if self.min_heap:
            return heapq.heappop(self.min_heap)
        else:
            self.next_min += 1
            return self.next_min - 1

    def give_id_back(self, x: int):
        if x < self.next_min:
            heapq.heappush(self.min_heap, x)
