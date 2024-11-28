import matplotlib.pyplot as plt
import csv

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

    plt.figure(figsize=(10, 6))
    plt.plot(runs, time_asm, label="Assembly Execution Time", marker='o')
    plt.plot(runs, time_c, label="C Execution Time", marker='x')

    plt.title("Execution Time Comparison")
    plt.xlabel("Run Number")
    plt.ylabel("Execution Time (seconds)")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()

    plt.show()

if __name__ == "__main__":
    plot_execution_times("execution_times.csv")
