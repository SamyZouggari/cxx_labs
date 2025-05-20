import matplotlib.pyplot as plt

# Initialisation des données
data = {
    'Soleil': {'times': [], 'x': [], 'y': []},
    'Terre': {'times': [], 'x': [], 'y': []},
    'Jupiter': {'times': [], 'x': [], 'y': []},
    'Haley': {'times': [], 'x': [], 'y': []}
}

# Lecture du fichier
with open('data.txt', 'r') as f:
    lines = f.readlines()

current_time = None
current_body = None

for line in lines:
    line = line.strip()
    if line.startswith('t = '):
        current_time = float(line.split('=')[1].strip())
    elif line in data:
        current_body = line
    elif line.startswith('x = '):
        x = float(line.split('=')[1].strip())
        data[current_body]['x'].append(x)
        data[current_body]['times'].append(current_time)
    elif line.startswith('y = '):
        y = float(line.split('=')[1].strip())
        data[current_body]['y'].append(y)

# Paramètres d'affichage
colors = {'Soleil': 'gold', 'Terre': 'blue', 'Jupiter': 'darkorange', 'Haley': 'gray'}
linestyles = {'Soleil': '-', 'Terre': '-', 'Jupiter': '-', 'Haley': '--'}
markers = {'Soleil': 'o', 'Terre': None, 'Jupiter': None, 'Haley': None}

# === FIGURE 1 : Vue globale ===
plt.figure(figsize=(12, 8))
for body in data:
    x = data[body]['x']
    y = data[body]['y']
    if x and y:
        plt.plot(x, y, label=body, color=colors[body], linestyle=linestyles[body], linewidth=2)
        # Marqueur de position finale
        plt.plot(x[-1], y[-1], marker='o', color=colors[body], markersize=6)

plt.title("Trajectoires complètes des corps célestes", fontsize=16)
plt.xlabel("Position X (UA)")
plt.ylabel("Position Y (UA)")
plt.legend()
plt.grid(True)
plt.axis("equal")

# === FIGURE 2 : Zoom sur le système interne ===
plt.figure(figsize=(10, 6))
for body in ['Soleil', 'Terre', 'Jupiter']:
    x = data[body]['x']
    y = data[body]['y']
    if x and y:
        plt.plot(x, y, label=body, color=colors[body], linestyle='-', linewidth=2)
        plt.plot(x[-1], y[-1], marker='o', color=colors[body], markersize=6)

plt.title("Zoom sur le système solaire interne", fontsize=14)
plt.xlabel("Position X (UA)")
plt.ylabel("Position Y (UA)")
plt.legend()
plt.grid(True)
plt.axis("equal")

plt.tight_layout()
plt.show()
