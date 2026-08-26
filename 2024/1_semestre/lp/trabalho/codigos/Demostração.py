# Criação da classe Aluno
class Aluno:
    def __init__(self, nome, frequencia, ra, nota_p1, nota_p2):
        self.nome = nome
        self.frequencia = frequencia
        self.ra = ra
        self.nota_p1 = nota_p1
        self.nota_p2 = nota_p2
        self.media = (nota_p1 + nota_p2) / 2

    def pegar_media(self):
        return self.media

    def situacao_aluno(self, media):
        if media >= 5 and self.frequencia>=75:
            return "Aprovado"
        else:
            return "Reprovado"

    def pegar_ra(self):
        return self.ra

    def pegar_nome(self):
        return self.nome

    def pegar_idade(self):
        return self.idade

    def pegar_prova1(self):
        return self.nota_p1

    def pegar_prova2(self):
        return self.nota_p2
    
    def pegar_frequencia(self):
        return self.frequencia
    
#Fim da classe Aluno

#Cria uma lista de alunos
lista_alunos = []

#Abre o arquivo alunos.txt e criar objetos alunos de acordo com a linha do arquivo
f = open('C:\\Users\\felip\\OneDrive\\Área de Trabalho\\Facul\\2024\\LP\\Trabalho\\Codigos\\alunos.txt')
with f as arquivo:
    next(arquivo)
    for linha in arquivo:
        dados = linha.strip().split(";")
        aluno = Aluno(dados[0], int(dados[1]), int(dados[2]), float(dados[3]), float(dados[4]))
        lista_alunos.append(aluno)     

# Ordena a lista de alunos com base na média, do maior para o menor
lista_alunos.sort(key=lambda aluno: aluno.pegar_media(), reverse=True)

# Mostra a lista ordenada
for aluno in lista_alunos:
    campos = aluno.pegar_nome().split(" ")
    nomes = campos[0]
    print("Nome: ", nomes, "\tMedia final: ", aluno.pegar_media(), "\tFrequência do aluno: ", aluno.pegar_frequencia(), "\tSituação do aluno: ", aluno.situacao_aluno(aluno.pegar_media()))
