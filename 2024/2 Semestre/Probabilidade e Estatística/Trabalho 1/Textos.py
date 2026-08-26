import joblib
from docx import Document

# Função para carregar textos de um arquivo DOCX
def load_texts_from_docx(file_path):
    doc = Document(file_path)
    texts = [para.text for para in doc.paragraphs if para.text.strip()]
    return texts

# Função para classificar novos textos
def classify_texts(texts):
    # Carregar o modelo treinado
    model = joblib.load('text_classifier.pkl')
    
    # Fazer predições (usando o pipeline que inclui o TfidfVectorizer)
    predictions = model.predict(texts)
    
    # Mapear predições para rótulos legíveis
    return ["Humano" if pred == 0 else "IA" for pred in predictions]

# Caminho para o arquivo DOCX a ser classificado
file_path = 'C:/Users/felip/Desktop/Facul/2024/Probabilidade e Estatística/Analise de Textos.docx'

# Carregar os textos do arquivo DOCX
texts = load_texts_from_docx(file_path)

# Classificar os textos
predictions = classify_texts(texts)

# Exibir os resultados
for i, (text, prediction) in enumerate(zip(texts, predictions)):
    print(f"Texto {i+1} ({text[:50]}...): {prediction}")
