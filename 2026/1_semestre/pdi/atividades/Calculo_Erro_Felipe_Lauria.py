import numpy as np

A = np.array([
    [255, 255, 255],
    [255,   0, 255],
    [255, 255, 255]
])

B = np.array([
    [250, 250, 250],
    [250,   1, 250],
    [250, 250, 250]
])

print("Matriz A:")
print(A)
print("\nMatriz B:")
print(B)

diff_abs = np.abs(A - B)

me = np.max(diff_abs)
mae = np.mean(diff_abs)
mse = np.mean((A - B)**2)
rmse = np.sqrt(mse)

A_binary = (A > 0).astype(int)
B_binary = (B > 0).astype(int)

intersection = np.sum(np.logical_and(A_binary, B_binary))
union = np.sum(np.logical_or(A_binary, B_binary))

if union == 0:
    jacard_index = 1.0 if intersection == 0 else 0.0
else:
    jacard_index = intersection / union

print(f"\n--- Resultados das Métricas ---")
print(f"Erro Máximo (ME): {me}")
print(f"Erro Absoluto Médio (MAE): {mae:.4f}")
print(f"Erro Quadrático Médio (MSE): {mse:.4f}")
print(f"Raiz do Erro Quadrático Médio (RMSE): {rmse:.4f}")
print(f"Índice de Jaccard (considerando pixels > 0 como 'foreground'): {jacard_index:.4f}")