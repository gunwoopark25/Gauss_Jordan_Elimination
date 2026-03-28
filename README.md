# Gauss-Jordan Elimination — Matrix Inverse Solver

C++17로 구현된 Gauss-Jordan Elimination(가우스-조르단 소거법) 기반 정방행렬(square matrix) 역행렬 계산기입니다.
텍스트 파일로 행렬을 입력받아 역행렬을 계산하고 결과를 파일로 출력합니다.

---

## 알고리즘 개요

Gauss-Jordan Elimination은 확장 행렬(augmented matrix) $[A \mid I]$에 행 연산(row operation)을 적용하여
기약 행 사다리꼴(RREF, Reduced Row Echelon Form)로 변환하는 방법입니다.

$$[A \mid I] \xrightarrow{\text{Row Operations}} [I \mid A^{-1}]$$

변환이 완료되면 오른쪽 블록이 $A^{-1}$이 됩니다.

**구현된 행 연산 순서:**

1. 피벗 행(pivot row)의 대각 원소로 해당 행 전체를 나누어 피벗을 1로 정규화
2. 피벗 열(pivot column)의 다른 모든 행을 소거(elimination)
3. 모든 열에 대해 반복 → RREF 달성

---

## 프로젝트 구조

```
Gauss_Jordan_Elimination/
├── Gauss_Jordan_Elimination.slnx          # Visual Studio 솔루션 파일
├── README.md
└── Gauss_Jordan_Elimination/
    ├── CMakeLists.txt                     # CMake 빌드 설정 (C++17)
    ├── Gauss_Jordan_Elimination.vcxproj   # Visual Studio 프로젝트 파일
    ├── Gauss_Jordan_Elimination.vcxproj.filters
    ├── Matrix.h                           # Matrix 클래스 선언
    ├── Matrix.cpp                         # Matrix 클래스 구현 (핵심 로직)
    ├── main.cpp                           # 진입점
    ├── Guassjordan_3.txt                  # 입력 샘플 — 3×3 행렬
    ├── Guassjordan_4.txt                  # 입력 샘플 — 4×4 행렬
    ├── Guassjordan_4_1.txt                # 입력 샘플 — 4×4 행렬 (대안)
    ├── GaussJordan_4_1.txt                # 입력 샘플 — 4×4 행렬
    ├── Guassjordan_5.txt                  # 입력 샘플 — 5×5 행렬
    └── Guassjordan_10.txt                 # 입력 샘플 — 10×10 행렬
```

---

## 클래스 설계

### `Matrix` 클래스 (`Matrix.h` / `Matrix.cpp`)

| 멤버 | 타입 | 설명 |
|------|------|------|
| `n` | `int` | (미사용 예약 변수) |
| `Size` | `int` | 행렬 크기 $n$ |
| `Unit` | `int` | `identityMatrix()` 내부에서 사용하는 크기 보조 변수 |
| `matrix` | `double**` | $n \times 2n$ 확장 행렬 (동적 2D 배열) |
| `Set2` | `double` | 피벗 정규화 계수 |
| `factor` | `double` | 행 소거 계수 |

| 메서드 | 설명 |
|--------|------|
| `Matrix()` | 생성자 — `fileLoad()` 호출하여 입력 행렬 로드 |
| `~Matrix()` | 소멸자 — `writeFile()` 호출하여 결과 파일 출력 |
| `fileLoad()` | `Guassjordan_3.txt`에서 행렬 크기 및 원소 읽기, 동적 메모리 할당 |
| `identityMatrix()` | 확장 행렬의 오른쪽 블록에 단위 행렬 삽입 |
| `loadFullmatrix()` | 확장 행렬 $[A \mid I]$ 전체 콘솔 출력 |
| `calulate()` | Gauss-Jordan Elimination 핵심 계산 수행 |
| `loadFinalinversematrix()` | 계산 완료 후 역행렬 블록만 콘솔 출력 |
| `writeFile()` | 역행렬을 `Guassjordan_3_ans.txt`로 저장 |

---

## 실행 흐름

```
[생성자] fileLoad()
    └─ Guassjordan_3.txt 읽기
    └─ n×2n 동적 배열 할당
    └─ 왼쪽 블록에 입력 행렬 A 적재

identityMatrix()
    └─ 오른쪽 블록에 단위 행렬 I 삽입
    └─ [A | I] 완성

calulate()  ← Gauss-Jordan Elimination
    └─ 피벗 정규화 (행 / 대각 원소)
    └─ 피벗 열 소거 (모든 다른 행에서 제거)
    └─ [I | A⁻¹] 완성

[소멸자] writeFile()
    └─ Guassjordan_3_ans.txt에 역행렬 저장
```

---

## 입력 파일 형식

첫 번째 줄에 행렬 크기 $n$, 이후 $n$개의 줄에 각 행의 원소를 공백으로 구분하여 입력합니다.

```
3
5 -6  9
4  3  7
-6  4  3
```

---

## 빌드 방법

### Visual Studio (Windows)

`Gauss_Jordan_Elimination.slnx`를 Visual Studio에서 열고 빌드합니다.

### CMake

```bash
cd Gauss_Jordan_Elimination
cmake -B build -DCMAKE_CXX_STANDARD=17
cmake --build build
./build/Guass_jordan_Elimination
```

---

## 주의 사항 및 한계

- 입력 파일명이 `Guassjordan_3.txt`로 하드코딩되어 있습니다. 다른 크기의 행렬을 테스트하려면 `Matrix.cpp`의 `fileLoad()` 함수 내 파일명을 직접 수정해야 합니다.
- 피벗 원소가 0인 경우(singular matrix(특이 행렬) 또는 행 교환이 필요한 경우)에 대한 예외 처리가 없어 0 나누기 오류가 발생할 수 있습니다.
- 동적 할당된 `double**` 메모리가 소멸자에서 해제되지 않아 메모리 누수(memory leak)가 존재합니다.

---

## 샘플 입력 파일 목록

| 파일명 | 행렬 크기 |
|--------|-----------|
| `Guassjordan_3.txt` | 3×3 |
| `Guassjordan_4.txt` | 4×4 |
| `Guassjordan_4_1.txt` / `GaussJordan_4_1.txt` | 4×4 |
| `Guassjordan_5.txt` | 5×5 |
| `Guassjordan_10.txt` | 10×10 |
