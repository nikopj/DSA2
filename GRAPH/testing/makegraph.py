import random

N = 100000
with open('big_graph','w') as f:
  for n in range(N):
    #print(n)
    num_neighbors = random.randint(0,10)
    for m in range(num_neighbors):
      neighbor = random.randint(0,N-1)
      weight = random.randint(1,1000)
      f.write('v'+str(n) + ' ' + 'v'+str(neighbor) + ' ' + str(weight) + '\n')
  
