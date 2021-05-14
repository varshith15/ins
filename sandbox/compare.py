import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker
# n = {'Avg': 404, 'median': 391, 'p90': 436, 'p95': 460, 'p99': 579, 'p99.9': 1849, 'p99.99': 3922}
# s = {'Avg': 616, 'median': 605, 'p90': 665, 'p95': 689, 'p99': 794, 'p99.9': 1994, 'p99.99': 5513}
# n = {'Avg': 113, 'median': 105, 'p90': 125, 'p95': 140, 'p99': 350, 'p99.9': 519, 'p99.99': 2891}
# s = {'Avg': 351, 'median': 339, 'p90': 412, 'p95': 484, 'p99': 622, 'p99.9': 789, 'p99.99': 2966}
# n = {'Avg': 647, 'median': 629, 'p90': 749, 'p95': 793, 'p99': 1019, 'p99.9': 2173}
# s = {'Avg': 742, 'median': 472, 'p90': 577, 'p95': 626, 'p99': 1484, 'p99.9': 2764}
# n = {'Avg': 114, 'median': 107, 'p90': 124, 'p95': 136, 'p99': 266, 'p99.9': 544, 'p99.99': 1165}
# s = {'Avg': 121, 'median': 109, 'p90': 133, 'p95': 160, 'p99': 402, 'p99.9': 574, 'p99.99': 3328}
# n = {'Avg': 582, 'median': 577, 'p90': 660, 'p95': 688, 'p99': 757, 'p99.9': 927, 'p99.99': 3695}
# s = {'Avg': 459, 'median': 450, 'p90': 490, 'p95': 506, 'p99': 578, 'p99.9': 1693, 'p99.99': 3731}
n = {'Avg': 111, 'median': 106, 'p90': 118, 'p95': 124, 'p99': 320, 'p99.9': 428, 'p99.99': 684}
s = {'Avg': 112, 'median': 106, 'p90': 118, 'p95': 125, 'p99': 360, 'p99.9': 483, 'p99.99': 1500}


df = pd.DataFrame({
    'type': list(n.keys()),
    'normal node': list(n.values()),
    'slow node': list(s.values())
})

#plotting graph
ax = df.plot(x="type", y=["normal node", "slow node"], kind="bar")

for p in ax.patches:
    ax.annotate(str(int(p.get_height())), (p.get_x() * 1.005, p.get_height() * 1.005))

plt.title('Slow Node Experiment - Read')
plt.ylabel('micro-seconds')
plt.xticks(rotation = 360)

plt.savefig("./../report/slow_node_read_correct.png", bbox_inches='tight')
plt.show()