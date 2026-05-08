import csv
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np

FISERE_DATE = ["date_random.csv", "date_aproape_sortat.csv", "date_invers_sortat.csv", "date_nr_mici.csv", "date_sortat.csv"]

# Function x**(1/2)
def forward(x):
    return x**(1/100)


def inverse(x):
    return x**100

for fisier in FISERE_DATE:
    with open("date/" + fisier) as f:
        rd = csv.reader(f)
        data_ = []
        for row in rd:
            data_.append(row)
        data = np.matrix(data_)
        # data = data.transpose()

        fig, ax = plt.subplots(figsize=(7, 5), layout='constrained')
        x_axis = data[1:,0].astype(float)
        ax.set_xscale('log')
        ax.set_yscale('log', base=2)
        for i in range(1, 8):
            zeroi = 1
            while zeroi < 14:
                if data[zeroi, i] == '-':
                    break
                zeroi += 1
            ax.plot(x_axis[:zeroi-1], data[1:zeroi, i].astype(float), label=data[0, i])
        ax.set_xlabel('Număr elemente în tablou')
        ax.set_ylabel('Timp de executare (s)')
        
        ax.set_xlim(10, 10000000)
        ax.set_ylim(1e-8, 32)
        ax.xaxis.set_major_formatter(ticker.FuncFormatter(lambda val, pos: f"{val:g}"))
        ax.yaxis.set_major_formatter(ticker.FuncFormatter(lambda val, pos: f"{val:g}"))
        ax.legend()

        plt.savefig("grafice/" + fisier[:-4] + ".png")