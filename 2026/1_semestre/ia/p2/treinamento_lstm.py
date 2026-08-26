import numpy as np
import matplotlib.pyplot as plt
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import LSTM, Dense, Dropout
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score

from preprocessamento import X_treino, y_treino, X_teste, y_teste, scaler, dados_teste, tamanho_da_janela

print("Dados importados")

# ==============================================================================
# CONSTRUÇÃO DA ARQUITETURA DA LSTM
# ==============================================================================
model = Sequential()

# primeira camada LSTM
model.add(LSTM(units=50, return_sequences=True, input_shape=(X_treino.shape[1], 1)))
model.add(Dropout(0.2))

# segunda camada LSTM
model.add(LSTM(units=50, return_sequences=False))
model.add(Dropout(0.2))

# camada de saída (prever o dia seguinte)
model.add(Dense(units=1))

# compilar
model.compile(optimizer='adam', loss='mean_squared_error')

print(model.summary()) # resumo da rede

# ==============================================================================
# TREINAMENTO
# ==============================================================================
print("\nIniciando o treinamento")
# epochs = quantas vezes a rede vai olhar todo o dataset
# batch_size = quantos blocos de dados ela olha antes de atualizar os pesos
historico = model.fit(X_treino, y_treino, epochs=15, batch_size=32, validation_split=0.1, verbose=1)

# ==============================================================================
# PREDIÇÕES (DADOS DE TESTE)
# ==============================================================================
predicoes_normalizadas = model.predict(X_teste)

# dados estavam entre 0 e 1, voltar ao preço real em dólares
predicoes = scaler.inverse_transform(predicoes_normalizadas)

# ==============================================================================
# GRÁFICO DE RESULTADOS
# ==============================================================================
valores_reais = dados_teste[tamanho_da_janela:]

plt.figure(figsize=(12, 6))
plt.plot(valores_reais, color='black', label='Preço Real da Apple (AAPL)')
plt.plot(predicoes, color='green', label='Previsão da Rede LSTM')
plt.title('Avaliação do Modelo LSTM - Previsão de Séries Temporais')
plt.xlabel('Tempo (Dias do Conjunto de Teste)')
plt.ylabel('Preço da Ação ($)')
plt.legend()
plt.grid(True)

plt.savefig('resultado_previsao_lstm.png')
print("\nGráfico salvo como 'resultado_previsao_lstm.png'")
plt.show()

# ==============================================================================
# CÁLCULO DAS MÉTRICAS
# =============================================================================
valores_reais = dados_teste[tamanho_da_janela:]

mae = mean_absolute_error(valores_reais, predicoes)
mse = mean_squared_error(valores_reais, predicoes)
rmse = np.sqrt(mse)
r2 = r2_score(valores_reais, predicoes)

print("\n" + "="*40)
print("     MÉTRICAS DE AVALIAÇÃO DO MODELO")
print("="*40)
print(f"Erro Médio Absoluto (MAE):         US$ {mae:.2f}")
print(f"Erro Quadrático Médio (MSE):       {mse:.2f}")
print(f"Raiz do Erro Quadrático (RMSE):    US$ {rmse:.2f}")
print(f"Coeficiente de Determinação (R²): {r2*100:.2f}%")
print("="*40)