
import matplotlib.pyplot as plt
import csv
import pandas as pd
import numpy as np
import csv
import matplotlib.pyplot as plt
import numpy as np

def plot_execution_times(file_path):
    """
    Reads execution times from a CSV file and displays a line graph
    comparing assembly and C execution times for each run, ensuring a line is plotted even if values are zero.
    
    :param file_path: Path to the CSV file containing execution times.
    """
    runs = []
    time_asm = []
    time_c = []

    # Read execution times from the CSV file
    with open(file_path, 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            runs.append(int(row['Run']))
            time_asm.append(float(row['Time_ASM']))
            time_c.append(float(row['Time_C']))

    # Convert runs to positions on x-axis
    x = np.arange(len(runs))

    # Plot line graph
    plt.figure(figsize=(12, 6))

    # Plotting the lines even if values are zero
    plt.plot(x, time_asm, label="Assembly Execution Time", marker='o', linestyle='-', color='b')
    plt.plot(x, time_c, label="C Execution Time", marker='x', linestyle='-', color='r')

    # Add labels, title, and legend
    plt.xlabel("Run Number")
    plt.ylabel("Execution Time (seconds)")
    plt.title("Execution Time Comparison (ASM vs C)")
    plt.xticks(x, runs)  # Use run numbers as x-axis labels
    plt.ylim(0.00)  # Ensure the y-axis starts at 0.00, even if values are zero
    plt.legend()
    plt.grid(True)
    plt.tight_layout()

    # Display the plot
    plt.show()
    
def plot_avg_execution_times(file_path):
    try:
        # Read the file into a DataFrame
        data = pd.read_csv(file_path, header=None, names=["Width", "Height", "Avg_Time_ASM", "Avg_Time_C"])
        
        # Combine width and height into a single string for labeling
        data["Dimension"] = data["Width"].astype(str) + "x" + data["Height"].astype(str)

        # Sort the data by the product of Width and Height (increasing order of dimension)
        data["Dimension_Size"] = data["Width"] * data["Height"]
        data = data.sort_values("Dimension_Size")

        # Create the plot
        fig, ax = plt.subplots(figsize=(10, 6))
        
        ax.plot(data["Dimension"], data["Avg_Time_ASM"], label="Average Time ASM", marker="o")
        ax.plot(data["Dimension"], data["Avg_Time_C"], label="Average Time C", marker="o")
        
        # Customize the plot
        ax.set_xlabel("Dimensions (Width x Height)")
        ax.set_ylabel("Average Execution Time (s)")
        ax.set_title("Average Execution Times for Assembly and C Functions")
        ax.legend()
        
        # Rotate x-axis labels for readability
        plt.xticks(rotation=45)
        plt.tight_layout()

        # Show the plot
        plt.show()

    except Exception as e:
        print(f"An error occurred: {e}")
    
if __name__ == "__main__":
    #plot_execution_times("./DEBUG/execution_times_10000.csv")
    plot_avg_execution_times("./DEBUG/avg_execution_times.csv")
