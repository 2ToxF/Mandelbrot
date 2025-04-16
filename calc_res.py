def CalcAverageFromFile(file_name, message):
    with open(file_name, "r") as file:
        tests_number = int(file.readline())
        test_results = list(map(int, file.readlines()))

    average = sum(test_results) / tests_number
    variance = sum(map(lambda x: (x - average)**2, test_results)) / tests_number
    deviation = variance**0.5

    filtered_arr = list(filter(lambda x: x - average <= deviation * 3, test_results))
    filtered_arr_len = len(filtered_arr)

    filetered_average = sum(filtered_arr) / filtered_arr_len
    filtered_variance = sum(map(lambda x: (x - filetered_average)**2, filtered_arr)) / filtered_arr_len
    filtered_deviation = filtered_variance**0.5
    error = filtered_deviation / (filtered_arr_len**0.5)

    print(f"{message}\n"
          f"Среднее время выполнения (в тиках): {filetered_average:.2f} +- "
          f"{error:.2f} (стандартная ошибка среднего)\n"
          f"Среднеквадратичное отклонение: {filtered_deviation:.2f}\n"
          f"Погрешность измерений: {error / filetered_average * 100:.2f}%\n")


CalcAverageFromFile("tests_res/flags_opt_O0.txt",    "Без оптимизации [-O0]:")
CalcAverageFromFile("tests_res/flags_opt_O1.txt",    "С оптимизацией флагами [-O1]:")
CalcAverageFromFile("tests_res/flags_opt_O2.txt",    "С оптимизацией флагами [-O2]:")
CalcAverageFromFile("tests_res/flags_opt_O3.txt",    "С оптимизацией флагами [-O3]:")
CalcAverageFromFile("tests_res/flags_opt_Ofast.txt", "С оптимизацией флагами [-Ofast]:")

print("\n\n")

CalcAverageFromFile("tests_res/gcc_arr_opt_O0.txt", "С оптимизацией на массиве [gcc, -O0]:")
CalcAverageFromFile("tests_res/gcc_arr_opt_O1.txt", "С оптимизацией на массиве [gcc, -O1]:")
CalcAverageFromFile("tests_res/gcc_arr_opt_O3.txt", "С оптимизацией на массиве [gcc, -O3]:")
CalcAverageFromFile("tests_res/clang_arr_opt_O0.txt", "С оптимизацией на массиве [clang, -O0]:")
CalcAverageFromFile("tests_res/clang_arr_opt_O1.txt", "С оптимизацией на массиве [clang, -O1]:")
CalcAverageFromFile("tests_res/clang_arr_opt_O3.txt", "С оптимизацией на массиве [clang, -O3]:")

print("\n\n")

CalcAverageFromFile("tests_res/intr128_opt.txt", "С использованием intrinsics [m128]:")
CalcAverageFromFile("tests_res/intr256_opt.txt", "С использованием intrinsics [m256]:")
