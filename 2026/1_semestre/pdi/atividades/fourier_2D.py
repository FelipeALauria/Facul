import numpy as np
import matplotlib.pyplot as plt
from PIL import Image

def dft_2d_manual(image):
    M, N = image.shape
    F = np.zeros((M, N), dtype=complex)
    
    for u in range(M):
        for v in range(N):
            soma = 0.0 + 0.0j
            for x in range(M):
                for y in range(N):
                    angulo = -2j * np.pi * ((u * x) / M + (v * y) / N)
                    soma += image[x, y] * np.exp(angulo)
            F[u, v] = soma
            
    return F

caminho_imagem = r"C:\Users\felip\Desktop\Facul\2026\1 Semestre\PDI\Atividades\Marcos.webp"

try:
    img = Image.open(caminho_imagem).convert('L')
except FileNotFoundError:
    print(f"Erro: Não foi possível encontrar a imagem no caminho:\n{caminho_imagem}")
    print("Verifique se o nome ou a extensão do arquivo estão corretos.")
    exit()

tamanho = 32
img_pequena = img.resize((tamanho, tamanho))
matriz_imagem = np.array(img_pequena)

print(f"Lendo Marcos.webp e calculando a DFT manual ({tamanho}x{tamanho})... Isso pode levar alguns segundos.")

# --- Cálculos da Transformada ---
resultado_frequencia = dft_2d_manual(matriz_imagem)
f_shift = np.fft.fftshift(resultado_frequencia)
magnitude_spectrum = 20 * np.log(np.abs(f_shift) + 1)

# ==========================================
# EXIBINDO OS RESULTADOS NUMÉRICOS
# ==========================================
print("\n" + "="*50)
print("RESULTADOS DA TRANSFORMAÇÃO (ANTES DA IMAGEM)")
print("="*50)

print(f"Formato da matriz gerada: {resultado_frequencia.shape}")

print("\n1. Amostra da matriz DFT Bruta (Números Complexos):")
print("   (Mostrando apenas o canto superior esquerdo 3x3)")
# Arredondando para 2 casas decimais para facilitar a leitura
print(np.round(resultado_frequencia[:3, :3], 2))

print("\n2. Amostra do Espectro de Magnitude (Valores Reais com Log):")
print("   (Mostrando o centro 3x3, onde fica o pico de baixa frequência/DC)")
meio = tamanho // 2
print(np.round(magnitude_spectrum[meio-1:meio+2, meio-1:meio+2], 2))

print(f"\nMaior valor no espectro de magnitude: {np.max(magnitude_spectrum):.2f}")
print(f"Menor valor no espectro de magnitude: {np.min(magnitude_spectrum):.2f}")
print("="*50 + "\n")
# ==========================================

# --- Exibição Gráfica ---
plt.figure(figsize=(12, 5))

plt.subplot(1, 2, 1)
plt.imshow(matriz_imagem, cmap='gray')
plt.title('Antes: Domínio Espacial (Pixels)')
plt.axis('off')

plt.subplot(1, 2, 2)
plt.imshow(magnitude_spectrum, cmap='gray')
plt.title('Depois: Espectro de Magnitude')
plt.axis('off')

plt.tight_layout()
plt.show()