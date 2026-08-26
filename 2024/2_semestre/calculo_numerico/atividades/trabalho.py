import numpy as np

# Definindo o sistema de equações
A = np.array([[7, 1, 2], [2, -11, 6], [-1, -4, -7]], dtype=float)
b = np.array([9, -3, 1], dtype=float)

# Função para o método de Jacobi
def jacobi(A, b, x0, iterations):
    n = len(b)
    x = x0.copy()
    for k in range(iterations):
        x_new = x.copy()  # Usamos x da iteração anterior para atualizar x_new
        print(f"\nIteração {k+1} (Método de Jacobi):")
        
        # Cálculos baseados nas fórmulas reescritas
        x_new[0] = (b[0] - A[0][1] * x[1] - A[0][2] * x[2]) / A[0][0]
        x_new[1] = (b[1] - A[1][0] * x[0] - A[1][2] * x[2]) / A[1][1]
        x_new[2] = (b[2] - A[2][0] * x[0] - A[2][1] * x[1]) / A[2][2]
        
        # Exibindo o valor de cada variável em cada iteração
        print(f"x[1] = {x_new[0]:.6f}, x[2] = {x_new[1]:.6f}, x[3] = {x_new[2]:.6f}")
        
        # Atualizando x para a próxima iteração
        x = x_new.copy()
    return x

# Função para o método de Gauss-Seidel
def gauss_seidel(A, b, x0, iterations):
    n = len(b)
    x = x0.copy()
    for k in range(iterations):
        print(f"\nIteração {k+1} (Método de Gauss-Seidel):")
        
        # Cálculos para Gauss-Seidel, atualizando imediatamente
        x[0] = (b[0] - A[0][1] * x[1] - A[0][2] * x[2]) / A[0][0]
        print(f"x[1] = {x[0]:.6f}")
        
        x[1] = (b[1] - A[1][0] * x[0] - A[1][2] * x[2]) / A[1][1]
        print(f"x[2] = {x[1]:.6f}")
        
        x[2] = (b[2] - A[2][0] * x[0] - A[2][1] * x[1]) / A[2][2]
        print(f"x[3] = {x[2]:.6f}")
        
    return x

# Condições iniciais
x0 = np.zeros(len(b))
iterations = 6

# Executando o método de Jacobi
print("Método de Jacobi:")
x_jacobi = jacobi(A, b, x0, iterations)

# Executando o método de Gauss-Seidel
print("\nMétodo de Gauss-Seidel:")
x_gauss_seidel = gauss_seidel(A, b, x0, iterations)

# Vetores das iterações atual e anterior
x_prev = np.array([0.96, -1.86, 0.94])  # exemplo de valores da iteração anterior
x_current = np.array([0.978, -1.98, 0.966])  # exemplo de valores da iteração atual

# Cálculo do erro relativo usando a norma do máximo
erro = np.max(np.abs(x_current - x_prev)) / np.max(np.abs(x_current))

print("\n\n")
print("Erro relativo:", erro)