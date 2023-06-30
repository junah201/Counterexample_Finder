import os
import datetime
import random
import datetime
import subprocess


def measure_time(func):
    def wrapper(*args, **kwargs):
        start_time = datetime.datetime.now()
        result = func(*args, **kwargs)
        end_time = datetime.datetime.now()
        execution_time = end_time - start_time
        execution_time.seconds
        print(f"실행 시간: {execution_time.seconds}초")
        return result
    return wrapper


@measure_time
def run_tc(input_value: str):
    with open("input.txt", "w") as file:
        file.write(input_value)

    os.system("g++ -DONLINE_JUDGE my_code.cpp -o code1.exe")
    with open("input.txt", "r") as input_f, open("output1.txt", "w") as output_f:
        subprocess.run(
            ["code1.exe"],
            stdin=input_f,
            stdout=output_f,
            text=True
        )

    os.system("g++ -DONLINE_JUDGE answer_code.cpp -o code2.exe")
    with open("input.txt", "r") as input_f, open("output2.txt", "w") as output_f:
        subprocess.run(
            ["code2.exe"],
            stdin=input_f,
            stdout=output_f,
            text=True
        )

    with open("output1.txt", "r") as file1, open("output2.txt", "r") as file2:
        output1 = file1.read().strip()
        output2 = file2.read().strip()

        print(f"Output1: {output1}")
        print(f"Output2: {output2}")

        if output1 != output2:
            print("Wrong Answer")
            with open(f"./wrong_tc/{datetime.datetime.now().timestamp()}.txt", "w") as input_file:
                input_file.write(
                    input_value + "\n\n\n" + f"worng answer : {output1}\n" + f"currect answer : {output2}")


if __name__ == "__main__":
    # 검사할 횟수
    T = 100
    for i in range(1, T+1):
        print(f"Test Case: {i}")
        # 테스트 케이스를 생성하는 코드
        limit = 5
        limit2 = 100

        N = random.randint(1, limit)
        M = random.randint(1, limit)

        input_value = f"{N} {M}\n"

        for _ in range(N):
            input_value += f"{random.randint(1, limit2)} {random.randint(1, limit2)}\n"

        for _ in range(M):
            input_value += f"{random.randint(1, limit2)}\n"

        run_tc(input_value)
