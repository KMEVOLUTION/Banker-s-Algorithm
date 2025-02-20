# Test
pluralization.Enter allocate size: 3\
Enter resource size: 3

Enter total units of each resource:\
Resource 1: 8\
Resource 2: 4\
Resource 3: 4

Enter allocation of process 1:\
Resource 1: 3\
Resource 2: 0\
Resource 3: 2

Enter allocation of process 2:\
Resource 1: 3\
Resource 2: 0\
Resource 3: 2

Enter allocation of process 3:\
Resource 1: 0\
Resource 2: 1\
Resource 3: 0

Enter max of process 1:\
Resource 1: 3\
Resource 2: 2\
Resource 3: 2

Enter max of process 2:\
Resource 1: 8\
Resource 2: 0\
Resource 3: 2

Enter max of process 3:\
Resource 1: 7\
Resource 2: 4\
Resource 3: 3


## Result

| Process | Alloc      | Max        | Need       | Avail      | State |
|---------|-----------|-----------|-----------|-----------|-------|
|         | A  B  C   | A  B  C   | A  B  C   | A  B  C   |       |
| P1      | 3  0  2   | 3  2  2   | 0  2  0   | 2  3  0   | SAFE  |
| P2      | 3  0  2   | 8  0  2   | 5  0  0   | 5  3  2   | SAFE  |
| P3      | 0  1  0   | 7  4  3   | 7  3  3   | 8  3  4   | SAFE  |

System is in a SAFE state. Safe sequence: P1 → P2 → P3  


