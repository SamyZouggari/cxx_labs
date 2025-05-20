import matplotlib.pyplot as plt
import numpy as np
x = np.linspace(1,2,1000)



y = [4*((1/r)**6)*(((1/r)**6) -1) for r  in x]

plt.plot(x,y)
plt.show()