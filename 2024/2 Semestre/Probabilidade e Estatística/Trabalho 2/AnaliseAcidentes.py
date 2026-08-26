import pandas as pd
import numpy as np
from scipy.stats import binom, chi2_contingency
import matplotlib.pyplot as plt

# Carregar os dados
ds = pd.read_excel("DadosEstradasBrasileiras.xlsx")

total_acidentes = 292658

# Probabilidades reais de sucesso e fracasso
sucessos_reais = ((ds['mortos'] == 0) & (ds['feridos'] == 0) & 
                  (ds['feridos_leves'] == 0) & (ds['feridos_graves'] == 0)).sum()
fracassos_reais = total_acidentes - sucessos_reais

p_sucesso_real = sucessos_reais / total_acidentes
p_fracasso_real = fracassos_reais / total_acidentes

print(f"Probabilidade de Sucesso Real: {p_sucesso_real:.2f}")
print(f"Probabilidade de Fracasso Real: {p_fracasso_real:.2f}")
print('\n')

# Parâmetros para as simulações
tamanho_amostra = 10000 
n_amostras = 8 

resultados_simulacoes = []

# Simulação binomial para cada amostra (0 a 7)
for i in range(n_amostras):
    # Dividir o dataset em amostras de 10.000 acidentes
    amostra = ds.iloc[i * tamanho_amostra: (i + 1) * tamanho_amostra]
    
    # Calcular os sucessos e fracassos reais na amostra
    sucessos_reais_amostra = ((amostra['mortos'] == 0) & (amostra['feridos'] == 0) & 
                              (amostra['feridos_leves'] == 0) & (amostra['feridos_graves'] == 0)).sum()
    fracassos_reais_amostra = tamanho_amostra - sucessos_reais_amostra
    
    # Simulação binomial com base nos dados reais
    simulacao_sucessos = binom.rvs(n=1, p=p_sucesso_real, size=tamanho_amostra)
    sucessos_simulados = np.sum(simulacao_sucessos == 1)
    fracassos_simulados = tamanho_amostra - sucessos_simulados
    
    # Calcular Qui-Quadrado para comparar os sucessos e fracassos reais e simulados
    observados = [sucessos_reais_amostra, fracassos_reais_amostra]
    simulados = [sucessos_simulados, fracassos_simulados]
    chi2, p_valor, _, _ = chi2_contingency([observados, simulados])
    
    # Armazenar os resultados, incluindo o Qui-Quadrado e o P-Valor
    resultados_simulacoes.append({
        'Amostra': i + 1,
        'Sucessos Reais': sucessos_reais_amostra,
        'Fracassos Reais': fracassos_reais_amostra,
        'Sucessos Simulados': sucessos_simulados,
        'Fracassos Simulados': fracassos_simulados,
        'Qui-Quadrado': chi2,
        'P-Valor': p_valor
    })

# Adicionar a amostra total para a 9ª iteração
simulacao_sucessos_total = binom.rvs(n=1, p=p_sucesso_real, size=total_acidentes)
sucessos_simulados_total = np.sum(simulacao_sucessos_total == 1)
fracassos_simulados_total = total_acidentes - sucessos_simulados_total

observados_total = [sucessos_reais, fracassos_reais]
simulados_total = [sucessos_simulados_total, fracassos_simulados_total]
chi2_total, p_valor_total, _, _ = chi2_contingency([observados_total, simulados_total])

# Adicionar a última iteração na lista de resultados
resultados_simulacoes.append({
    'Amostra': 'Total',
    'Sucessos Reais': sucessos_reais,
    'Fracassos Reais': fracassos_reais,
    'Sucessos Simulados': sucessos_simulados_total,
    'Fracassos Simulados': fracassos_simulados_total,
    'Qui-Quadrado': chi2_total,
    'P-Valor': p_valor_total
})

# Criar DataFrame com os resultados
df_resultados = pd.DataFrame(resultados_simulacoes)

# Exibir a tabela de resultados
print(df_resultados)

# Salvar o DataFrame em um arquivo Excel, incluindo Qui-Quadrado e P-Valor
df_resultados.to_excel('resultados_simulacoes_qui_quadrado.xlsx', index=False)

# Geração dos Gráficos 

# Configuração dos subplots (3 linhas x 3 colunas para as 9 iterações)
fig, axs = plt.subplots(3, 3, figsize=(15, 10))

# Geração dos gráficos em subplots
labels = ['Sucesso (sem mortes)', 'Fracasso (com mortes)']

for i in range(len(df_resultados)):
    row = i // 3  
    col = i % 3  

    # Dados da amostra
    observed_counts = [df_resultados.loc[i, 'Sucessos Reais'], df_resultados.loc[i, 'Fracassos Reais']]
    simulated_counts = [df_resultados.loc[i, 'Sucessos Simulados'], df_resultados.loc[i, 'Fracassos Simulados']]
    
    x = np.arange(len(labels)) 
    
    axs[row, col].bar(x - 0.2, observed_counts, 0.4, label='Reais')
    axs[row, col].bar(x + 0.2, simulated_counts, 0.4, label='Simulados')
    
    axs[row, col].set_xlabel('Eventos')
    axs[row, col].set_ylabel('Contagem')
    axs[row, col].set_title(f'Amostra {df_resultados.loc[i, "Amostra"]}')
    axs[row, col].set_xticks(x)
    axs[row, col].set_xticklabels(labels)
    axs[row, col].legend()

# Ajustar o layout dos gráficos
plt.tight_layout()
plt.show()
