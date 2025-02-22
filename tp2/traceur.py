import matplotlib.pyplot as plt

# Dictionnaire pour stocker les données
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
        # Extraction du temps
        current_time = float(line.split('=')[1].strip())
        
    elif line in data:
        # Nouveau corps céleste
        current_body = line
        
    elif line.startswith('x = '):
        # Coordonnée x
        x = float(line.split('=')[1].strip())
        data[current_body]['x'].append(x)
        data[current_body]['times'].append(current_time)
        
    elif line.startswith('y = '):
        # Coordonnée y
        y = float(line.split('=')[1].strip())
        data[current_body]['y'].append(y)

# Création du graphique
plt.figure(figsize=(12, 8))

# Tracé des trajectoires pour chaque corps
colors = {'Soleil': 'gold', 'Terre': 'blue', 'Jupiter': 'orange', 'Haley': 'gray'}
markers = {'Soleil': 'o', 'Terre': '^', 'Jupiter': 's', 'Haley': '*'}

for body in data:
    if len(data[body]['x']) > 0:
        plt.scatter(
            data[body]['x'], 
            data[body]['y'], 
            c=data[body]['times'],
            label=body,
            cmap='viridis',
            marker=markers[body],
            s=50 if body != 'Soleil' else 100
        )

plt.colorbar(label='Temps')
plt.xlabel('Position X (UA)')
plt.ylabel('Position Y (UA)')
plt.title('Trajectoires des corps célestes')
plt.legend()

# Ajustement des échelles pour mieux voir les planètes intérieures
plt.figure(figsize=(10, 6))
for body in ['Soleil', 'Terre', 'Jupiter']:
    if len(data[body]['x']) > 0:
        plt.plot(
            data[body]['x'], 
            data[body]['y'], 
            marker=markers[body],
            linestyle='--',
            label=body,
            color=colors[body]
        )
plt.xlabel('Position X (UA)')
plt.ylabel('Position Y (UA)')
plt.title('Zoom sur le système solaire interne')
plt.legend()
plt.grid(True)

plt.show()