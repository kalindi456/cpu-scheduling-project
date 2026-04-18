import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Read performance CSV
df = pd.read_csv("data/performance.csv")

# Algorithms
algorithms = df['algorithm'].tolist()

# Avg WT and Avg TAT
avg_wt = df['avg_wt'].tolist()
avg_tat = df['avg_tat'].tolist()
cs = df['context_switch'].tolist()

# Set up positions for bars
x = np.arange(len(algorithms))
width = 0.35  # width of the bars

# Create figure
fig, ax = plt.subplots(figsize=(8,5))

# Plot Avg WT and Avg TAT bars side by side
bars1 = ax.bar(x - width/2, avg_wt, width, label='Avg WT', color='skyblue', edgecolor='black')
bars2 = ax.bar(x + width/2, avg_tat, width, label='Avg TAT', color='lightgreen', edgecolor='black')

# Add labels and title
ax.set_xlabel('Scheduling Algorithm')
ax.set_ylabel('Time')
ax.set_title('CPU Scheduling Performance Comparison')
ax.set_xticks(x)
ax.set_xticklabels(algorithms)
ax.legend()

# Add value labels on top of bars
def add_labels(bars):
    for bar in bars:
        height = bar.get_height()
        ax.annotate(f'{height:.2f}',
                    xy=(bar.get_x() + bar.get_width()/2, height),
                    xytext=(0,3),  # 3 points vertical offset
                    textcoords="offset points",
                    ha='center', va='bottom')

add_labels(bars1)
add_labels(bars2)

plt.tight_layout()
plt.show()
