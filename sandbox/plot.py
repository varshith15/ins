import sys
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

file = sys.argv[1]
bool = int(sys.argv[2])
save = sys.argv[3]
flag = int(sys.argv[4])
if flag:
    plt.ylim(0,0.005)
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
print(len(xs), len(ys))
if bool:
    xs = list(range(len(ys)))
    df = pd.DataFrame({"number":xs, "latency": ys})
    sns.scatterplot(data = df, x = "number", y = "latency")
    plt.title("Request number VS Latency")
else:
    mi = xs[0]
    xs =[x-mi for x in xs]
    df = pd.DataFrame({"time":xs, "latency": ys})
    sns.scatterplot(data = df, x = "time", y = "latency")
    plt.title("Time the request is sent VS Latency")

plt.savefig(save)
# plt.show()