#! /usr/bin/python3

import pandas as pd
import matplotlib.pyplot as plt

plt.rcParams["figure.figsize"] = [15, 7]
plt.rcParams["figure.autolayout"] = True

df = pd.read_csv('out_new.csv')

df = df.convert_dtypes()
df['Vertices'] = df['Vertices'].astype("Int64")

alphas = [0.0, 0.2, 0.5, 0.8, 1.0]
grasp_iterations = [20, 50, 100, 500, 1000]
cnt = 0

for i in range(len(alphas)):
    for j in range(len(grasp_iterations)):

        dfs = []

        df1 = df.loc[(df['Alpha'] == alphas[i]) & (df['Grasp_Iteration_Count'] == grasp_iterations[j])].copy()
        df1['Inputs'] = pd.RangeIndex(0, int((df1.size / df.columns.size)), 1)

        dfs.append(df1.loc[df1['Inputs'] == 0].copy())

        for k in range(1, 37, 6):
            dfs.append(df1.loc[(df1['Inputs'] >= k) & (df1['Inputs'] < (k + 6))].copy())

        for k in range(len(dfs)):
            dfs[k].plot(x = "InputFile", y = ['Greedy_Search_Value', 'Average_Random_Search_Value', 'Average_Semi_Greedy_Search_Value', 'Average_Local_Search_Value', 'Best_GRASP_Value', 'Best_Known_Solution'], kind = 'bar')
            plt.legend(loc='best', fontsize='xx-large')
            plt.title(f"Alpha = {alphas[i]}  GRASP Iteration = {grasp_iterations[j]}")
            cnt = cnt + 1
            plt.savefig(f"bar_graph_{cnt}.png")
            plt.close()