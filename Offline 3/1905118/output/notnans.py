#! /usr/bin/python3

import pandas as pd
import matplotlib.pyplot as plt

plt.rcParams["figure.figsize"] = [16, 9]
plt.rcParams["figure.autolayout"] = True

df = pd.read_csv('out_new.csv')
df = df.convert_dtypes()
df = df[df['Best_Known_Solution'].notnull()].copy()

cnt = 0
alphas = [0.1, 0.5, 0.9]
grasp_iterations = [20, 100, 1000]



for i in range(len(alphas)):
    for j in range(len(grasp_iterations)):

        dfs = []

        tempdf = df.loc[(df['Alpha'] == alphas[i]) & (df['Grasp_Iteration_Count'] == grasp_iterations[j])].copy()
        tempdf['Inputs'] = pd.RangeIndex(0, int((tempdf.size / df.columns.size)), 1)

        dfs.append(tempdf.loc[(tempdf['Inputs'] <= 10)].copy())
        dfs.append(tempdf.loc[(tempdf['Inputs'] > 10)].copy())

        dfs[0].plot(x = "InputFile", y = ['Greedy_Search_Value', 'Average_Random_Search_Value', 'Average_Semi_Greedy_Search_Value', 'Average_Local_Search_Value', 'Best_GRASP_Value', 'Best_Known_Solution'], kind = 'bar')
        plt.legend(loc='best', fontsize='xx-large')
        plt.ylabel("Max Cut Weight", fontsize='xx-large')
        plt.xlabel('Input Graph Files', fontsize='xx-large')
        plt.xticks(fontsize='xx-large')
        plt.yticks(fontsize='xx-large')
        plt.title(f"Alpha = {alphas[i]}  GRASP Iteration = {grasp_iterations[j]}", fontsize='xx-large')
        cnt = cnt + 1
        plt.savefig(f"bar_graph_{cnt}.png")
        plt.close()

        dfs[1].plot(x = "InputFile", y = ['Greedy_Search_Value', 'Average_Random_Search_Value', 'Average_Semi_Greedy_Search_Value', 'Average_Local_Search_Value', 'Best_GRASP_Value', 'Best_Known_Solution'], kind = 'bar')
        plt.legend(loc='best', fontsize='xx-large')
        plt.ylabel("Max Cut Weight", fontsize='xx-large')
        plt.xlabel('Input Graph Files', fontsize='xx-large')
        plt.xticks(fontsize='xx-large')
        plt.yticks(fontsize='xx-large')
        plt.title(f"Alpha = {alphas[i]}  GRASP Iteration = {grasp_iterations[j]}", fontsize='xx-large')
        cnt = cnt + 1
        plt.savefig(f"bar_graph_{cnt}.png")
        plt.close()