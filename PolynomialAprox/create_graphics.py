import matplotlib.pyplot as plt
import os

def get_file_info(path, metric):
    is_a = True
    with open(path, "r") as file:
        for line in file:
            m, value, _ = line.split(",")[:3]
            if (m != metric):
                continue
            if is_a:
                value_a = float(value)
                is_a = False
            else:
                value_b = float(value)
    return value_a, value_b


def get_info(group, metric):
    path_v1 = "results/v1"
    path_v2 = "results/v2"

    data = {
        "a": {
            ("v1", 10): {},
            ("v1", 1000): {},
            ("v2", 10): {},
            ("v2", 1000): {}
        },
        "b": {
            ("v1", 10): {},
            ("v1", 1000): {},
            ("v2", 10): {},
            ("v2", 1000): {}
        }
    }

    for file in os.listdir(path_v1):
        if "FLOPS" in file:
            g1, g2, k, n = file.split("_")
            g = g1+"_"+g2
        else:
            g, k, n = file.split("_")
        n = int(n[:-4])
        if (g != group):
            continue
        full_path = "results/v1/"+file
        value_a, value_b = get_file_info(full_path, metric)
        data["a"][("v1", n)][int(k)] = value_a
        data["b"][("v1", n)][int(k)] = value_b

    for file in os.listdir(path_v2):
        if "FLOPS" in file:
            g1, g2, k, n = file.split("_")
            g = g1+"_"+g2
        else:
            g, k, n = file.split("_")
        n = int(n[:-4])
        if (g != group):
            continue
        full_path = "results/v2/"+file
        value_a, value_b = get_file_info(full_path, metric)
        data["a"][("v2", n)][int(k)] = value_a
        data["b"][("v2", n)][int(k)] = value_b

    return data


# returns in the following format:
# vector k
# vector v1_10
# vector v1_1000
# vector v2_10
# vector v2_1000
def organize_data(data):
    organized_data = {
        "a": [[], [], [], [], []],
        "b": [[], [], [], [], []]
    }
    k = list(data["a"][("v1", 10)].keys())
    k.sort()

    organized_data["a"][0] = k
    organized_data["b"][0] = k

    for i in k:
        data_a = data["a"]
        data_b = data["b"]
        organized_data["a"][1].append(data_a[("v1", 10)][i])
        organized_data["a"][2].append(data_a[("v1", 1000)][i])
        organized_data["a"][3].append(data_a[("v2", 10)][i])
        organized_data["a"][4].append(data_a[("v2", 1000)][i])
        organized_data["b"][1].append(data_b[("v1", 10)][i])
        organized_data["b"][2].append(data_b[("v1", 1000)][i])
        organized_data["b"][3].append(data_b[("v2", 10)][i])
        organized_data["b"][4].append(data_b[("v2", 1000)][i])
    return organized_data


def plot_graphic(x, Y, file_path):
    plt.xscale('log')
    labels = ["v1 10", "v1 1000", "v2 10", "v2 1000"]
    for i, y in enumerate(Y):
        plt.plot(x, y, label=labels[i])
    plt.legend()
    plt.savefig(file_path)




data = organize_data(get_info("L3CACHE", "L3 miss ratio"))
x = data["a"][0]
Y = data["a"][1:]
print(Y)
plot_graphic(x, Y, "test.png")
