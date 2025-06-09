import pandas as pd
import matplotlib
import matplotlib.pyplot as plt

# open a csv file
#df = pd.read_csv('recursivo.csv')
df2 = pd.read_csv('Memo.csv')
df3 = pd.read_csv('dp.csv')
df4 = pd.read_csv('dpOP.csv')

# graphic each line
# plot(x=values, y=values, label, points marker)
#plt.plot(df['n'], df['t_mean'], label='Programa recursivo', marker='o')
plt.plot(df2['n'], df2['t_mean'], label='Programa recursivo con Memoizacion', marker='s')
plt.plot(df3['n'], df3['t_mean'], label='Programacion dinamica', marker='v')
plt.plot(df4['n'], df4['t_mean'], label='Programacion dinamica optimizada', marker='x')

# x=labels and y=labels
plt.ylabel('Running time (millieseconds)')
plt.xlabel('size of texts (caracters)')

# show legend
plt.legend()

# save graphic in a file
plt.savefig('plot.png')