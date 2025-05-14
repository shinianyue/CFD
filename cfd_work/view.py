import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data = pd.read_csv("./output/flow_10000.csv")
x = data["x"]
y = data["y"]
u = data["u"]
v = data["v"]
print("u max:", u.max())
print("v max:", v.max())
print("v min:", v.min())
plt.figure(figsize=(6, 6))
plt.quiver(x, y, u, v, scale=5)
plt.title("Velocity Field (u, v)")
plt.xlabel("x")
plt.ylabel("y")
plt.axis("equal")
plt.grid()
plt.show()