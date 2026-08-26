import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from scipy import stats

# Carregar o CSV
df = pd.read_csv('travessia.csv', sep=';')

# Exibir as primeiras linhas do DataFrame
print(df.head())

# Definir a paleta de cores
palette = ['red']

# Análise do tempo de resolução associado ao número de tentativas
plt.figure(figsize=(12, 6))
sns.scatterplot(data=df, x='tentativas', y='tempo', palette=, s=100, alpha=0.6, edgecolor='w')
sns.regplot(data=df, x='tentativas', y='tempo', scatter=False, color='green')
plt.title('Tempo de Resolução vs Número de Tentativas')
plt.xlabel('Número de Tentativas')
plt.ylabel('Tempo de Resolução')
plt.show()

# Estatísticas descritivas
estatisticas_tempo_tentativas = df.groupby('tentativas')['tempo'].describe()

print("\nEstatísticas descritivas do Tempo de Resolução por Número de Tentativas:")
print(estatisticas_tempo_tentativas)

# Cálculo da correlação entre tempo de resolução e número de tentativas
correlacao = df[['tentativas', 'tempo']].corr()

print("\nCorrelação entre Tempo de Resolução e Número de Tentativas:")
print(correlacao)