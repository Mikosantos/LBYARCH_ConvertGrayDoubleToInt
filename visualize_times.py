
import matplotlib.pyplot as plt
import csv
import pandas as pd
import numpy as np

def plot_execution_times(file_path):
    runs = []
    time_asm = []
    time_c = []

    with open(file_path, 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            runs.append(int(row['Run']))
            time_asm.append(float(row['Time_ASM']))
            time_c.append(float(row['Time_C']))

    x = np.arange(len(runs))

    plt.figure(figsize=(12, 6))

    plt.plot(x, time_asm, label="Assembly Execution Time", marker='o', linestyle='-', color='b')
    plt.plot(x, time_c, label="C Execution Time", marker='x', linestyle='-', color='r')

    plt.xlabel("Run Number")
    plt.ylabel("Execution Time (seconds)")
    plt.title("Execution Time Comparison (ASM vs C)")
    plt.xticks(x, runs) 
    plt.ylim(0.00)  
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.show()
    
def plot_avg_execution_times(file_path):
    try:
        data = pd.read_csv(file_path, header=None, names=["Width", "Height", "Avg_Time_ASM", "Avg_Time_C"])
        data["Dimension"] = data["Width"].astype(str) + "x" + data["Height"].astype(str)
        data["Dimension_Size"] = data["Width"] * data["Height"]
        data = data.sort_values("Dimension_Size")

        fig, ax = plt.subplots(figsize=(10, 6))
        
        ax.plot(data["Dimension"], data["Avg_Time_ASM"], label="Average Time ASM", marker="o")
        ax.plot(data["Dimension"], data["Avg_Time_C"], label="Average Time C", marker="o")
        
        ax.set_xlabel("Dimensions (Width x Height)")
        ax.set_ylabel("Average Execution Time (s)")
        ax.set_title("Average Execution Times for Assembly and C Functions")
        ax.legend()
        
        plt.xticks(rotation=45)
        plt.tight_layout()

        plt.show()

    except Exception as e:
        print(f"An error occurred: {e}")
    
if __name__ == "__main__":
    #plot_execution_times("./DEBUG/execution_times_10000.csv")
    plot_avg_execution_times("./DEBUG/avg_execution_times.csv")
