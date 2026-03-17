import numpy as np
import pandas as pd
import scipy.stats as stats

# Definição dos tamanhos de entrada (N) e simulação dos tempos de execução (em milissegundos)
np.random.seed(42)  # Garantir reprodutibilidade

N_sizes = [1000, 5000, 10000, 50000, 100000]  # Tamanhos das listas ordenadas
num_replicas = 10  # Número de medições para cada algoritmo

# Simulação dos tempos de execução para cada algoritmo
quicksort_times = [np.random.normal(loc=N * 0.00001, scale=0.0005, size=num_replicas) for N in N_sizes]
mergesort_times = [np.random.normal(loc=N * 0.000015, scale=0.0005, size=num_replicas) for N in N_sizes]
heapsort_times = [np.random.normal(loc=N * 0.000012, scale=0.0005, size=num_replicas) for N in N_sizes]

# Organização dos dados em DataFrame
data = []
for i, N in enumerate(N_sizes):
    for j in range(num_replicas):
        data.append(["QuickSort", N, quicksort_times[i][j]])
        data.append(["MergeSort", N, mergesort_times[i][j]])
        data.append(["HeapSort", N, heapsort_times[i][j]])

df = pd.DataFrame(data, columns=["Algoritmo", "Tamanho", "Tempo(ms)"])

# ANOVA: Verificar diferença significativa entre os algoritmos
anova_result = stats.f_oneway(
    df[df["Algoritmo"] == "QuickSort"]["Tempo(ms)"],
    df[df["Algoritmo"] == "MergeSort"]["Tempo(ms)"],
    df[df["Algoritmo"] == "HeapSort"]["Tempo(ms)"],
)

# Resultados estatísticos
mean_times = df.groupby("Algoritmo")["Tempo(ms)"].mean()
std_times = df.groupby("Algoritmo")["Tempo(ms)"].std()

# Criar planilha Excel
excel_path = "/mnt/data/ANOVA_Algoritmos.xlsx"
with pd.ExcelWriter(excel_path) as writer:
    df.to_excel(writer, sheet_name="Dados", index=False)
    summary_df = pd.DataFrame({"Média": mean_times, "Desvio Padrão": std_times})
    summary_df.to_excel(writer, sheet_name="Resumo")
    anova_df = pd.DataFrame({"F-Estatística": [anova_result.statistic], "p-Valor": [anova_result.pvalue]})
    anova_df.to_excel(writer, sheet_name="ANOVA")

# Verificar resultado da ANOVA
anova_result.statistic, anova_result.pvalue, excel_path
