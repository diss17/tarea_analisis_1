import pandas as pd
import matplotlib.pyplot as plt

# Abrir el archivo CSV
df = pd.read_csv('bruteF.csv')

# Graficar la media de tiempo (t_mean) como una línea
plt.plot(df['n'], df['t_mean'], label='Brute Force', marker='o', linestyle='-')

# Etiquetas de los ejes
plt.xlabel('Input size (n)')
plt.ylabel('Running time (nanoseconds)')

# Escala logarítmica en el eje y
plt.yscale('log')

# Título del gráfico
plt.title('Running Time vs Input Size')

# Mostrar leyenda
plt.legend()

# Guardar el gráfico en un archivo
plt.savefig('plot.png')

# Mostrar el gráfico
plt.show()