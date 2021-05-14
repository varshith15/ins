import numpy as np
import sys

file = str(sys.argv[1])
xs = []
ys = []
with open(file) as f:
    for line in f.readlines():
        try:
            line = line.strip().split(" ")
            x = float(line[1])
            y = float(line[0])
            xs.append(x)
            ys.append(y)
        except:
            pass
a = np.array(ys)
avg = np.mean(a)*1000000
p50 = np.percentile(a, 50)*1000000
p75 = np.percentile(a, 75)*1000000
p90 = np.percentile(a, 90)*1000000
p95 = np.percentile(a, 95)*1000000
p99 = np.percentile(a, 99)*1000000
p99_9 = np.percentile(a, 99.9)*1000000
p99_99 = np.percentile(a, 99.99)*1000000

print("Count: {}".format(len(xs)))
print({"Avg": round(avg), "median":round(p50), "p90":round(p90), "p95":round(p95),
       "p99":round(p99), "p99.9":round(p99_9), "p99.99": round(p99_99)})