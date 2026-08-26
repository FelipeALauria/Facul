import numpy as np
import pandas as pd
import yfinance as yf
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler

# ==============================================================================
# COLETA DOS DADOS
# ==============================================================================
# dados da Apple (AAPL) de 2020-2026
ticket = "AAPL"
dados = yf.download(ticket, start="2020-01-01", end="2026-06-01")

dados_fechamento = dados[['Close']].values

print(f"Total de dias baixados: {len(dados_fechamento)}")

# ==============================================================================
# DIVISÃO DOS DADOS
# ==============================================================================
tamanho_treino = int(len(dados_fechamento) * 0.80)

dados_treino = dados_fechamento[0:tamanho_treino]
dados_teste = dados_fechamento[tamanho_treino:len(dados_fechamento)]

print(f"Registros para Treino: {len(dados_treino)} | Registros para Teste: {len(dados_teste)}")

# ==============================================================================
# NORMALIZAÇÃO
# ==============================================================================
scaler = MinMaxScaler(feature_range=(0, 1))

# só nos dados de treino para evitar vazamento de dados
dados_treino_normalizados = scaler.fit_transform(dados_treino)
# mesma transformação no teste
dados_teste_normalizados = scaler.transform(dados_teste)

# ==============================================================================
# CRIAÇÃO DAS JANELAS TEMPORAIS
# ==============================================================================
def criar_janelas(dataset, tamanho_janela=60):
    X, Y = [], []
    for i in range(len(dataset) - tamanho_janela):
        # do índice 'i' até 'i + tamanho_janela' será a entrada (X)
        X.append(dataset[i:(i + tamanho_janela), 0])
        # o próximo elemento imediatamente após a janela será o alvo (Y)
        Y.append(dataset[i + tamanho_janela, 0])
    return np.array(X), np.array(Y)

# configurar o tamanho da janela
tamanho_da_janela = 60

X_treino, y_treino = criar_janelas(dados_treino_normalizados, tamanho_da_janela)
X_teste, y_teste = criar_janelas(dados_teste_normalizados, tamanho_da_janela)

# ==============================================================================
# REDIMENSIONAMENTO PARA O PADRÃO DA LSTM (3D)
# ==============================================================================
# mudar os dados em 2d para 3d.

X_treino = np.reshape(X_treino, (X_treino.shape[0], X_treino.shape[1], 1))
X_teste = np.reshape(X_teste, (X_teste.shape[0], X_teste.shape[1], 1))

print(f"X_treino final: {X_treino.shape}")
print(f"Formato final do X_teste (Pronto para LSTM): {X_teste.shape}")