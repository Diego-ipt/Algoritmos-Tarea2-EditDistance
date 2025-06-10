import pandas as pd
import matplotlib
import matplotlib.pyplot as plt

# open a csv file
df = pd.read_csv('recursivo.csv')
#df2 = pd.read_csv('Memo.csv')
#df3 = pd.read_csv('dp.csv')
#df4 = pd.read_csv('dpOP.csv')

# graphic each line
plt.plot(df['n'], df['t_mean'], label='Programa recursivo', marker='o')
#plt.plot(df2['n'], df2['t_mean'], label='Programa recursivo con Memoización', marker='s')
#plt.plot(df3['n'], df3['t_mean'], label='Programación dinámica', marker='v')
#plt.plot(df4['n'], df4['t_mean'], label='Programación dinámica optimizada', marker='x')

# x=labels and y=labels
plt.ylabel('Running time (milisegundos)')
plt.xlabel('Tamaño de los textos (caracteres)')

# show legend
plt.legend()

# save graphic in a file
plt.savefig('recursivo-only.png')
