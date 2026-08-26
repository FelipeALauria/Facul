import pandas as pd 
import matplotlib as plt
import sklearn as sk

filmes = pd.read_csv('movies.csv', sep=',')
print(filmes.head())
print("\n\n\n\n")

ratings = pd.read_csv('ratings.csv', sep=',')
print(ratings.head())
print("\n\n\n\n")

df = filmes.merge(ratings, on='movieId')
print(df.head())
print("\n\n\n\n")

tabela_filmes = pd.pivot_table(df, index='userId', columns='title', values='rating').fillna(0)
print(tabela_filmes.head())
print("\n\n\n\n")