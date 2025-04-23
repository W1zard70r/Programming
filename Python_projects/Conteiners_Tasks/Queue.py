def ticket_queue(queue: list[int], k: int) -> int:
    if k >= len(queue):
        raise ValueError

    time_to_wait = 0
    for i in range(0,len(queue)):
        if i<k:
            time_to_wait += min( a[k] , a[i] )
        elif i > k:
            time_to_wait += min( a[k] - 1, a[i] )
        else:
            time_to_wait += a[k]
    return time_to_wait


a = [4,3,2,5,1,1]
print(ticket_queue(a,2))