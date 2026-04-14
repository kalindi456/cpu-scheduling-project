import pandas as pd
import matplotlib.pyplot as plt
import sys
algorithm=sys.argv[1]
csv_file=sys.argv[2]
df = pd.read_csv("data/schedule_log.csv")
df = df.sort_values(by="start")

fig, ax = plt.subplots(figsize=(12,3))

colors = plt.cm.tab20.colors
y = 0

for _, row in df.iterrows():
    pid = int(row["pid"])
    start = float(row["start"])
    end = float(row["end"])
    duration = end - start

    if pid == 0:
        color = "lightgray"
        label = "Idle"
        text_color = "black"
    else:
        color = colors[(pid-1) % len(colors)]
        label = f"P{pid}"
        text_color = "white"

    ax.barh(y, duration, left=start, height=0.6, color=color, edgecolor="black")

    if duration > 0.4:
        ax.text(start + duration/2, y, label, ha="center", va="center",
                color=text_color, fontsize=11, fontweight="bold")

ax.set_yticks([])
ax.set_xlabel("Time")
ax.set_title(algorithm)

times = sorted(set(df["start"]).union(set(df["end"])))
ax.set_xticks(times)

ax.grid(axis="x", linestyle="--", alpha=0.5)

plt.tight_layout()
plt.show()
