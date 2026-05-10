# Gray-code-and-set

Discrete Mathematics 1 lab — Gray code generation and multiset algebra in C++.

## Two parts in one program

### Part 1 — Gray Code

The universe `U` is built as the set of all n-bit Gray codes, where `n` is entered by the user.

| Function | Description |
|----------|-------------|
| `toGrayCode(decimal)` | Convert decimal to Gray code: `n ^ (n >> 1)` |
| `toGrayCodeString(decimal, n)` | Format as n-bit binary string via `bitset<32>` |
| `grayToDecimal(bitset)` | Decode Gray code back to decimal (XOR chain) |
| `compareByGrayCode(a, b)` | Comparator for sorting elements in Gray order |
| `convertToGrayOrder(set)` | Re-sort a multiset by Gray code value |

Each universe element gets a random multiplicity in `[1, 50]` generated with `std::mt19937`.

### Part 2 — Multiset Operations

The program works with two multisets **A** and **B** that are subsets of universe **U**. Each element has an associated **multiplicity** (кратность) that must not exceed the multiplicity of the corresponding universe element.

```cpp
struct MultiSetElement {
    int element;      // Gray code value
    int multiplicity; // кратность
};
```

**Input modes:**
- `M` — manual: enter each element as an n-bit Gray code string + its multiplicity
- `A` — automatic: random elements and multiplicities from U

**Operations computed and printed:**

| Operation | Formula |
|-----------|---------|
| Union `A ∪ B` | μ(x) = μ_A(x) + μ_B(x) |
| Intersection `A ∩ B` | μ(x) = min(μ_A(x), μ_B(x)) |
| Complement `A'` | μ(x) = μ_U(x) − μ_A(x) |
| Complement `B'` | μ(x) = μ_U(x) − μ_B(x) |
| Difference `A \ B` | μ(x) = max(0, μ_A(x) − μ_B(x)) |
| Difference `B \ A` | μ(x) = max(0, μ_B(x) − μ_A(x)) |
| Symmetric difference `A △ B` | (A ∪ B) − (A ∩ B), by multiplicity |
| Arithmetic difference | \|μ_A(x) − μ_B(x)\| for common elements |
| Arithmetic multiplication | = Intersection |
| Arithmetic division | = A \ B |
| Cartesian product `A × B` | all pairs (a, b), displayed as Gray codes |
| Cartesian product `B × A` | all pairs (b, a) |

All results are displayed with elements shown as n-bit Gray code strings.

## Input validation

- `n` must be a non-negative integer
- Set sizes must be in `[0, 2^n]`
- Manual element input must be an n-bit binary string
- Multiplicity must not exceed the universe multiplicity for that element
- Duplicate elements within a set are rejected

## Build

```
Visual Studio — open DisMath1.sln
```

## Files

| File | Description |
|------|-------------|
| `DisMath1.cpp` | Full implementation (single file) |
| `dismath1.pdf` | Full lab report |
