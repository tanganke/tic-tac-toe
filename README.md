
## Example

```bash
$ ./tic-tac-toe
```

output:

```shell
choose mode:
1. human vs human
2. human vs computer (Minimax)
3. computer (Minimax) vs human
4. computer (Minimax) vs computer (Minimax)
input: 4
Round 1:
 0.000056s wall, 0.000000s user + 0.000000s system = 0.000000s CPU (n/a%)
  0 1 2
0 _ _ _ 
1 _ _ _ 
2 X _ _ 

AI's choice is (1,1)
 0.042833s wall, 0.040000s user + 0.000000s system = 0.040000s CPU (93.4%)
  0 1 2
0 _ _ _ 
1 _ O _ 
2 X _ _ 

Round 2:
AI's choice is (0,0)
 0.004992s wall, 0.000000s user + 0.000000s system = 0.000000s CPU (n/a%)
  0 1 2
0 X _ _ 
1 _ O _ 
2 X _ _ 

AI's choice is (1,0)
 0.000742s wall, 0.010000s user + 0.000000s system = 0.010000s CPU (n/a%)
  0 1 2
0 X _ _ 
1 O O _ 
2 X _ _ 

Round 3:
AI's choice is (1,2)
 0.000165s wall, 0.000000s user + 0.000000s system = 0.000000s CPU (n/a%)
  0 1 2
0 X _ _ 
1 O O X 
2 X _ _ 

AI's choice is (0,1)
 0.000047s wall, 0.000000s user + 0.000000s system = 0.000000s CPU (n/a%)
  0 1 2
0 X O _ 
1 O O X 
2 X _ _ 

Round 4:
AI's choice is (2,1)
 0.000013s wall, 0.000000s user + 0.000000s system = 0.000000s CPU (n/a%)
  0 1 2
0 X O _ 
1 O O X 
2 X X _ 

AI's choice is (2,2)
 0.000006s wall, 0.000000s user + 0.000000s system = 0.000000s CPU (n/a%)
  0 1 2
0 X O _ 
1 O O X 
2 X X O 

Round 5:
AI's choice is (0,2)
 0.000003s wall, 0.000000s user + 0.000000s system = 0.000000s CPU (n/a%)
  0 1 2
0 X O X 
1 O O X 
2 X X O 

Game over. Tie.
final board state:
  0 1 2
0 X O X 
1 O O X 
2 X X O 
```

## reference

- https://github.com/Cledersonbc/tic-tac-toe-minimax
