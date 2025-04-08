def CalcAverageFromFile(file_name, message):
    with open(file_name, "r") as file:
        tests_number = int(file.readline())
        test_results = list(map(int, file.readlines()))

        average = sum(test_results) / tests_number
        variance = sum(map(lambda x: (x - average)**2, test_results)) / tests_number
        deviation = variance**0.5
        deviation_x3 = deviation * 3

        filtered_list = list(filter(lambda x: x - average <= deviation_x3, test_results))
        average_filtered = sum(filtered_list) / len(filtered_list)

        error = deviation / (tests_number**0.5)
        print(f"{message}\n"
              f"Среднее время выполнения (в тиках): {round(average_filtered, 2)} +- "
              f"{round(error, 2)} (стандартная ошибка среднего)\n"
              f"Среднеквадратичное отклонение: {round(deviation, 2)}\n"
              f"Погрешность измерений: {round(error / average_filtered, 4) * 100}%\n")


CalcAverageFromFile("tests_res/no_opt_O0.txt", "Результат наивной версии [-O0]")
CalcAverageFromFile("tests_res/no_opt_O1.txt", "Результат наивной версии [-O1]")
CalcAverageFromFile("tests_res/no_opt_O2.txt", "Результат наивной версии [-O2]")
CalcAverageFromFile("tests_res/no_opt_O3.txt", "Результат наивной версии [-O3]")
CalcAverageFromFile("tests_res/no_opt_Ofast.txt", "Результат наивной версии [-Ofast]")
