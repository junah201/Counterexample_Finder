# Counterexample Finder

당신의 코드와 정답 코드를 비교해서 반례를 찾아드립니다.

## C++ 사용법

```shell
git clone https://github.com/junah201/Counterexample_Finder.git)https://github.com/junah201/Counterexample_Finder.git
cd .\Counterexample_Finder
```

이 저장소를 `clone`합니다.

이후 cpp 폴더 안에 있는 `my_code.cpp`에 당신의 코드를, 그리고 `answer_code.cpp`에 정답 코드를 넣어주세요.

그 다음, `make_tc.py`에 테스트 케이스를 무작위로 생성하는 코드를 풀고자 하는 알고리즘 문제의 조건에 맞게 넣어주세요.

```shell
cd .\cpp
python main.py
```

`main.py`를 실행하면, 100개의 무작위 테스트 케이스에 대해 반례가 발생하면, 해당 반례, 실제 정답, 출력값을 담은 txt 파일이 /wrong_tc 폴더에 자동으로 생성됩니다.

# Contribute

Contributions are welcome!
