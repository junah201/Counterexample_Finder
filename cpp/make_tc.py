import random


def make_tc() -> str:
    """테스트 케이스를 랜덤하게 생성합니다."""
    limit = 5
    limit2 = 100

    N = random.randint(1, limit)
    M = random.randint(1, limit)

    input_value = f"{N} {M}\n"

    for _ in range(N):
        input_value += f"{random.randint(1, limit2)} {random.randint(1, limit2)}\n"

    for _ in range(M):
        input_value += f"{random.randint(1, limit2)}\n"

    return input_value
