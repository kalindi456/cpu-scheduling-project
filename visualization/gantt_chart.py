import pandas as pd
import matplotlib.pyplot as plt

# Read the log file
df = pd.read_csv("data/schedule_log.csv")

fig, ax = plt.subplots(figsize=(12,3))

colors = plt.cm.tab20.colors
y = 0

for i, row in df.iterrows():

    pid = int(row["pid"])
    start = float(row["start"])
    end = float(row["end"])
    duration = end - start

    color = colors[(pid-1) % len(colors)]

    # Draw Gantt block
    ax.barh(
        y,
        duration,
        left=start,
        height=0.6,
        color=color,
        edgecolor="black"
    )

    # Add process label
    if duration > 0.4:
        ax.text(
            start + duration/2,
            y,
            f"P{pid}",
            ha="center",
            va="center",
            color="white",
            fontsize=11,
            fontweight="bold"
        )

# Axis formatting
ax.set_yticks([])
ax.set_xlabel("Time")
ax.set_title("CPU Scheduling Gantt Chart")

# Show exact execution times
times = sorted(set(df["start"]).union(set(df["end"])))
ax.set_xticks(times)

ax.grid(axis="x", linestyle="--", alpha=0.5)

plt.tight_layout()
plt.show()
