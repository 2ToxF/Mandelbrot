import matplotlib.pyplot as plt


def CalcAverageAndError(arr, arr_len):
        average = sum(arr) / arr_len
        variance = sum(map(lambda x: (x - average)**2, arr)) / arr_len
        deviation = variance**0.5
        deviation_x3 = deviation * 3

        filtered_arr = list(filter(lambda x: x - average <= deviation_x3, arr))
        filtered_arr_len = len(filtered_arr)

        filetered_average = sum(filtered_arr) / filtered_arr_len
        filtered_variance = sum(map(lambda x: (x - filetered_average)**2, filtered_arr)) / filtered_arr_len
        filtered_deviation = filtered_variance**0.5
        error = filtered_deviation / (filtered_arr_len**0.5)
        return (deviation, round(filetered_average, 2), round(error, 2))


def BuildOneGraph(file_name, label):
    with open(f"tests_res/{file_name}.txt", "r") as results:
        tests_number = int(results.readline())
        data = [x for x in map(lambda x: x.split(), results.readlines())]

    tests_num_arr = list(range(1, tests_number+1))
    time_arr = []
    for line in data:
        time_arr.append(int(line[1]))

    deviation, average, error = CalcAverageAndError(time_arr, tests_number)

    for i in range(len(tests_num_arr)):
        if abs(time_arr[i] - average) > deviation:
            time_arr[i] = average

    plt.plot(tests_num_arr, time_arr, label=label)
    plt.axhline(y=average)


def BuildEntireGraph(data_file_names, labels, graph_file_name, graph_title):
    plt.figure(figsize=(10, 10))
    plt.title(graph_title)
    plt.xlabel("Test number")
    plt.ylabel("Calculation time in ticks")
    plt.grid()

    for i in range(len(data_file_names)):
        BuildOneGraph(data_file_names[i], labels[i])
    plt.legend()
    plt.savefig(f"graphs/{graph_file_name}.svg")


BuildEntireGraph(["flags_opt_O0",         "flags_opt_O1"],
                 ["No optimiztion [-O0]", "-O1 Optimization"],
                 "flags_opt_O0_O1",
                 "Compiler flags optmization")


BuildEntireGraph(["flags_opt_O2", "flags_opt_O3", "flags_opt_Ofast"],
                 ["-O2 Optimization", "-O3 Optimization", "-Ofast Optimization"],
                 "flags_opt_O2_O3_Ofast",
                 "Compiler flags optmization")
