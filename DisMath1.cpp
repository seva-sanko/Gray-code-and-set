#include <iostream>
#include <set>
#include <vector>
#include <bitset>
#include <random>
#include <cmath>
#include <algorithm>
#include <cctype> // Для функции isdigit
#include <stdlib.h> // нужен для вызова функции rand(), srand()
#include <time.h> // нужен для вызова функции time()

using namespace std;



// Функция для перевода числа в бинарный код Грея
int toGrayCode(int decimal) {
    return decimal ^ (decimal >> 1);
}

// Функция для преобразования числа в строку бинарного кода Грея с заданной разрядностью n
string toGrayCodeString(int decimal, int n) {
    bitset<32> binary(toGrayCode(decimal));
    return binary.to_string().substr(32 - n);
}

// Функция для преобразования бинарного кода Грея в десятичное значение
int grayToDecimal(const std::bitset<10>& binary) {
    std::bitset<10> gray = binary;
    for (size_t i = 1; i < binary.size(); i++) {
        gray[i] = binary[i] ^ binary[i - 1];
        //cout << gray[i] << " " << binary[i] << " " << binary[i - 1] << endl;
    }
    return static_cast<int>(gray.to_ulong());
}

struct MultiSetElement {
    int element;
    int multiplicity;

    MultiSetElement(int elem, int mult) : element(elem), multiplicity(mult) {}\
    MultiSetElement() : element(0), multiplicity(0) {}\
    bool operator==(const MultiSetElement& other) const {
        return element == other.element && multiplicity == other.multiplicity;
    }
};

bool operator<(const MultiSetElement& lhs, const MultiSetElement& rhs) {
    return lhs.element < rhs.element;
}

int generateRandomMultiplicity() {
    std::random_device rd;  // Источник случайных чисел
    std::mt19937 gen(rd()); // Генератор случайных чисел
    std::uniform_int_distribution<int> dist(1, 50);

    return dist(gen);
}

bool compareByGrayCode(const MultiSetElement& a, const MultiSetElement& b) {
    // Реализуйте сравнение элементов по коду Грея
    return toGrayCode(a.element) < toGrayCode(b.element);
}

multiset<MultiSetElement> convertToGrayOrder(const multiset<MultiSetElement>& binarySet) {
    // Копируем элементы в вектор
    std::vector<MultiSetElement> grayOrderVector(binarySet.begin(), binarySet.end());

    // Сортируем вектор с использованием компаратора, соответствующего порядку кода Грея
    std::sort(grayOrderVector.begin(), grayOrderVector.end(), compareByGrayCode);

    // Создаем мультимножество из отсортированного вектора
    multiset<MultiSetElement> grayOrderSet(grayOrderVector.begin(), grayOrderVector.end());

    return grayOrderSet;
}

int main() {
    setlocale(LC_ALL, "Rus");



    int n;
    char input[10];

    cout << "Введите разрядность бинарного кода Грея: ";
    cin >> input;

    while (true) {
        bool validInput = true;

        for (char* c = input; *c != '\0'; ++c) {
            if (!isdigit(*c)) {
                validInput = false;
                break;
            }
        }

        if (validInput) {
            n = atoi(input);
            if (n >= 0) {
                break;
            }
        }

        cerr << "Некорректный ввод. Разрядность должна быть положительным целым числом." << endl;
        cout << "Введите разрядность бинарного кода Грея: ";
        cin >> input;
    }

    int powerA;
    char inputP_A[10];

    if (n > 0) {
        cout << "Введите мощность множества A (количество элементов, не должно привышать " << (1 << n) << "): ";
    }
    else
        cout << "Введите мощность множества A (мощность не может быть больше " << 0 << "): ";


    cin >> inputP_A;

    while (true) {
        bool validInput = true;

        for (char* c = inputP_A; *c != '\0'; ++c) {
            if (!isdigit(*c)) {
                validInput = false;
                break;
            }
        }

        if (validInput) {
            powerA = atoi(inputP_A);
            if (powerA >= 0 && powerA <= (1 << n)) {
                break;
            }
        }

        cerr << "Некорректный ввод. Мощность должна быть неотрицательным целым числом, не больше чем 2^n(n - разрядность)." << endl;
        cout << "Введите мощность множества A: ";
        cin >> inputP_A;
    }

    int powerB;
    char inputP_B[10];
    if (n > 0) {
        cout << "Введите мощность множества B (количество элементов, не должно привышать " << (1 << n) << "): ";
    }
    else
        cout << "Введите мощность множества B (мощность не может быть больше " << 0 << "): ";

    cin >> inputP_B;

    while (true) {
        bool validInput = true;

        for (char* c = inputP_B; *c != '\0'; ++c) {
            if (!isdigit(*c)) {
                validInput = false;
                break;
            }
        }

        if (validInput) {
            powerB = atoi(inputP_B);
            if (powerB >= 0 && powerB <= (1 << n)) {
                break;
            }
        }

        cerr << "Некорректный ввод. Мощность должна быть неотрицательным целым числом, не больше чем 2^n(n - разрядность)." << endl;
        cout << "Введите мощность множества B: ";
        cin >> inputP_B;
    }


    char choice;
    cout << "Выберите способ заполнения множества (M - вручную, A - автоматически): ";
    cin >> choice;

    while (tolower(choice) != 'm' && tolower(choice) != 'a') {
        cerr << "Некорректный ввод. Введите 'M' для заполнения вручную или 'A' для автоматического заполнения." << endl;
        cout << "Выберите способ заполнения множества (M - вручную, A - автоматически): ";
        cin >> choice;
    }

    multiset<MultiSetElement> setA, setB, setU;

    // Создание универсума в виде бинарного кода Грея
    cout << endl;
    cout << "Универсум (в виде бинарного кода Грея): " << endl;
    int randomMultiplicity;
    int** box = new int* [1 << n];
    for (int i = 0; i < (1 << n); i++) {
        if (n > 0) {
            randomMultiplicity = generateRandomMultiplicity();
        }
        else {
            //cout << "Пустое множество" << endl;
            randomMultiplicity = 0;
        }
        setU.insert(MultiSetElement(toGrayCode(i), randomMultiplicity));
    }
    multiset<MultiSetElement> grayU = convertToGrayOrder(setU);
    for (const MultiSetElement& element : grayU) {
        if (n > 0) {
            cout << toGrayCodeString(element.element, n) << "|" << element.multiplicity << endl;
        }
        else {
            cout << "Пустое множество" << endl;
        }
        //cout << element.element << "|" << element.multiplicity << endl;
        box[element.element] = new int[2];
        box[element.element][0] = element.element;
        box[element.element][1] = element.multiplicity;
    }
    cout << endl;

    if (choice == 'M' || choice == 'm') {
        // Ввод множеств вручную
        int element;
        int multiplicity;

        if (powerA > 0) {
            for (int i = 0; i < powerA; i++) {
                cout << "Введите элемент " << i + 1 << " для множества A (в виде бинарного кода Грея): ";
                string el_A;
                cin >> el_A;

                    bool validInput = true;

                    for (char c : el_A) {
                        if (c != '0' && c != '1') {
                            validInput = false;
                            break;
                        }
                    }

                    if (!validInput) {
                        cout << "Некорректный ввод. Введите бинарное значение." << endl;
                        i--; // повторяем итерацию
                        continue;
                    }

                // Преобразование введенной строки в число
                bitset<10> binaryElement(el_A);
                element = binaryElement.to_ulong();
                //int elementG = toGrayCode(element);
                if (!(element >= 0 && element < (1 << n))) {
                    cout << "Некорректный ввод. Введите бинарное значение разрядности n." << endl;
                    i--; // повторяем итерацию
                    continue;
                }
                int j = 0;
                while (j < (1 << n) && toGrayCodeString(box[j][0], n) != el_A) {
                    j++;
                }
                element = j;
                 //Проверка на наличие элемента с тем же значением в setA
                MultiSetElement tempElement(element, 0);
                if (setA.find(tempElement) != setA.end()) {
                    cout << "Некорректный ввод. Данный элемент уже содержится в мультимножестве." << endl;
                    i--; // повторяем итерацию
                    continue;
                }


                cout << "Введите кратность для элемента " << i + 1 << " множества A: ";
                char m_A[10];
                cin >> m_A;

                while (true) {
                    bool validInput = true;

                    for (char* c = m_A; *c != '\0'; ++c) {
                        if (!isdigit(*c)) {
                            validInput = false;
                            break;
                        }
                    }

                    if (validInput) {
                        multiplicity = atoi(m_A);
                        int j = 0;
                        while (j < (1 << n) && box[j][0] != element ) {
                            j++;
                        }
                        if (box[j][1] > multiplicity) {
                            break;
                        }
                    } 
                     
                    cerr << "Некорректный ввод. Кратность элемента не должна превышать кратность универсума" << endl;
                    cout << "Введите кратность элемента: ";
                    cin >> m_A;
                }
               
                setA.insert(MultiSetElement(element, multiplicity));
            }
        }

        if (powerB > 0) {
            for (int i = 0; i < powerB; i++) {
                cout << "Введите элемент " << i + 1 << " для множества B (в виде бинарного кода Грея): ";
                string el_B;
                cin >> el_B;

                bool validInput = true;

                for (char c : el_B) {
                    if (c != '0' && c != '1') {
                        validInput = false;
                        break;
                    }
                }

                if (!validInput) {
                    cout << "Некорректный ввод. Введите бинарное значение." << endl;
                    i--; // повторяем итерацию
                    continue;
                }

                // Преобразование введенной строки в число
                bitset<10> binaryElement(el_B);
                element = binaryElement.to_ulong();
                //int elementG = toGrayCode(element);
                if (!(element >= 0 && element < (1 << n))) {
                    cout << "Некорректный ввод. Введите бинарное значение разрядности n." << endl;
                    i--; // повторяем итерацию
                    continue;
                }
                int j = 0;
                while (j < (1 << n) && toGrayCodeString(box[j][0], n) != el_B) {
                    j++;
                }
                element = j;
                //Проверка на наличие элемента с тем же значением в setA
                MultiSetElement tempElement(element, 0);
                if (setB.find(tempElement) != setB.end()) {
                    cout << "Некорректный ввод. Данный элемент уже содержится в мультимножестве." << endl;
                    i--; // повторяем итерацию
                    continue;
                }


                cout << "Введите кратность для элемента " << i + 1 << " множества B: ";
                char m_B[10];
                cin >> m_B;

                while (true) {
                    bool validInput = true;

                    for (char* c = m_B; *c != '\0'; ++c) {
                        if (!isdigit(*c)) {
                            validInput = false;
                            break;
                        }
                    }

                    if (validInput) {
                        multiplicity = atoi(m_B);
                        int j = 0;
                        while (j < (1 << n) && box[j][0] != element) {
                            j++;
                        }
                        if (box[j][1] >= multiplicity) {
                            break;
                        }
                    }

                    cerr << "Некорректный ввод. Кратность элемента не должна превышать кратность универсума" << endl;
                    cout << "Введите кратность элемента: ";
                    cin >> m_B;
                }

                setB.insert(MultiSetElement(element, multiplicity));
            }
        }
    }
    else if (choice == 'A' || choice == 'a') {
        // Автоматическая генерация мультимножеств
        int randomElement;
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> dis(0, (1 << n) - 1);

            for (int i = 0; i < powerA; i++) {

                randomElement = dis(gen);

                // Проверка на наличие элемента с тем же значением в setA
                MultiSetElement tempElement(randomElement, 0);
                while (setA.find(tempElement) != setA.end()) {
                    randomElement = dis(gen);
                    tempElement = MultiSetElement(randomElement, 0);
                }

                int j = 0;
                while (j < (1 << n) && box[j][0] != randomElement) {
                    j++;
                }                

                randomMultiplicity = generateRandomMultiplicity();
                while (box[j][1] <= randomMultiplicity) {
                    randomMultiplicity = generateRandomMultiplicity();
                }

                MultiSetElement elem;
                elem.element = randomElement;
                elem.multiplicity = randomMultiplicity;
                setA.insert(elem);
                //cout << toGrayCodeString(elem.element, n) << "|" << elem.multiplicity << endl;
            }
            

            for (int i = 0; i < powerB; i++) {
                randomElement = dis(gen);

                // Проверка на наличие элемента с тем же значением в setB
                MultiSetElement tempElement(randomElement, 0);
                while (setB.find(tempElement) != setB.end()) {
                    randomElement = dis(gen);
                    tempElement = MultiSetElement(randomElement, 0);
                }

                int j = 0;
                while (j < (1 << n) && box[j][0] != randomElement) {
                    j++;
                }

                randomMultiplicity = generateRandomMultiplicity();
                while (box[j][1] <= randomMultiplicity) {
                    randomMultiplicity = generateRandomMultiplicity();
                }

                MultiSetElement elem;
                elem.element = randomElement;
                elem.multiplicity = randomMultiplicity;
                setB.insert(elem);
                
            }
    }
    else {
        cout << "Ошибка: Некорректный выбор способа заполнения множества." << endl;
        return 1;
    }

    // Вывод результатов
    cout << "Множество A: " << endl;
    for (const MultiSetElement& element : setA) {
        cout << toGrayCodeString(element.element, n) << "|" << element.multiplicity << endl;
    }
    cout << endl;

    cout << "Множество B: " << endl;
    for (const MultiSetElement& element : setB) {
        cout << toGrayCodeString(element.element, n) << "|" << element.multiplicity << endl;
    }
    cout << endl;



    //Операции над мультимножествами


    multiset<MultiSetElement> unionSet;

    // Вставляем элементы из setA
    for (const MultiSetElement& elementA : setA) {
        MultiSetElement elementToInsert = elementA;
        // Если элемент уже есть в unionSet, добавляем его кратности
        auto it = unionSet.find(elementA);
        if (it != unionSet.end()) {
            elementToInsert.multiplicity += it->multiplicity;
            unionSet.erase(it);
        }
        unionSet.insert(elementToInsert);
    }

    // Вставляем элементы из setB
    for (const MultiSetElement& elementB : setB) {
        MultiSetElement elementToInsert = elementB;
        // Если элемент уже есть в unionSet, добавляем его кратности
        auto it = unionSet.find(elementB);
        if (it != unionSet.end()) {
            elementToInsert.multiplicity += it->multiplicity;
            unionSet.erase(it);
        }
        unionSet.insert(elementToInsert);
    }


    // Дополнение A (A')
    int complementMultiplicity;
    multiset<MultiSetElement> complementA;
    for (const MultiSetElement& element : setU) {
        complementMultiplicity = element.multiplicity;
        //auto foundInA = std::find(grayA.begin(), grayA.end(), element);
        auto foundInA = setA.find(element);
        if (foundInA != setA.end()) {
            complementMultiplicity -= foundInA->multiplicity;
        }
        if (complementMultiplicity > 0) {
            complementA.insert(MultiSetElement(element.element, complementMultiplicity));
        }
    }


    // Дополнение B (B')
    multiset<MultiSetElement> complementB;
    for (const MultiSetElement& element : setU) {
        complementMultiplicity = element.multiplicity;
        auto foundInB = setB.find(element);
        if (foundInB != setB.end()) {
            complementMultiplicity -= foundInB->multiplicity;
        }

        if (complementMultiplicity > 0) {
            complementB.insert(MultiSetElement(element.element, complementMultiplicity));
        }
    }

    // Разность A \ B
    multiset<MultiSetElement> differenceAB;
    for (const MultiSetElement& element : setA) {
        auto foundInB = setB.find(element);
        if (foundInB == setB.end()) {
            differenceAB.insert(MultiSetElement(element.element, max(0, element.multiplicity)));
        }
        else {
            int differenceMultiplicity = element.multiplicity - foundInB->multiplicity;
            if (differenceMultiplicity > 0) {
                differenceAB.insert(MultiSetElement(element.element, differenceMultiplicity));
            }
        }
    }
    // Разность B \ A
    multiset<MultiSetElement> differenceBA;
    for (const MultiSetElement& element : setB) {
        auto foundInA = setA.find(element);
        if (foundInA == setA.end()) {
            differenceBA.insert(MultiSetElement(element.element, element.multiplicity));
        }
        else {
            int differenceMultiplicity = element.multiplicity - foundInA->multiplicity;
            if (differenceMultiplicity > 0) {
                differenceBA.insert(MultiSetElement(element.element, differenceMultiplicity));
            }
        }
    }


    // Арифметическая разность мультимножеств A и B
    multiset<MultiSetElement> symmetricDifferenceSet;
    for (const MultiSetElement& element : setA) {
        auto foundInB = setB.find(element);
        if (foundInB != setB.end()) {
            int minMultiplicity = min(element.multiplicity, foundInB->multiplicity);
            int maxMultiplicity = max(element.multiplicity, foundInB->multiplicity);
            int result = maxMultiplicity - minMultiplicity;
            symmetricDifferenceSet.insert(MultiSetElement(element.element, result));
        }
        else
        {
            symmetricDifferenceSet.insert(MultiSetElement(element));
        }
    }

    for (const MultiSetElement& element : setB) {
        auto foundInB = setA.find(element);
        if (foundInB == setA.end()) {
            symmetricDifferenceSet.insert(MultiSetElement(element));
        }
    }

    //// Добавляем элементы из B, которые отсутствуют в A
    //for (const MultiSetElement& element : setB) {
    //    auto foundInA = setA.find(element);
    //    if (foundInA == setA.end()) {
    //        // Если элемент есть в B, но отсутствует в A, добавляем его с учётом кратности из B
    //        symmetricDifference.insert(MultiSetElement(element.element, element.multiplicity));
    //    }
    //}

    // Декартово произведение мультимножеств A и B
    set<pair<MultiSetElement, MultiSetElement>> cartesianProductA;
    for (const MultiSetElement& elementA : setA) {
        for (const MultiSetElement& elementB : setB) {
            cartesianProductA.insert({ elementA, elementB });
        }
    }

    // Декартово произведение мультимножеств B и A
    set<pair<MultiSetElement, MultiSetElement>> cartesianProductB;
    for (const MultiSetElement& elementB : setB) {
        for (const MultiSetElement& elementA : setA) {
            cartesianProductB.insert({ elementB, elementA });
        }
    }

    // Пересечение мультимножеств A и B
    multiset<MultiSetElement> intersectionSet;
    for (const MultiSetElement& element : setA) {
        auto foundInB = setB.find(element);
        if (foundInB != setB.end()) {
            // Находим минимум из кратностей элемента в A и B
            int minMultiplicity = min(element.multiplicity, foundInB->multiplicity);
            intersectionSet.insert(MultiSetElement(element.element, minMultiplicity));
        }
    }

    // Симметрическая разность A ∆ B
    multiset<MultiSetElement> symmetricDifference;
    for (const MultiSetElement& element : unionSet) {
        auto foundInB = intersectionSet.find(element);
        if (foundInB != intersectionSet.end()) {
            int minMultiplicity = min(element.multiplicity, foundInB->multiplicity);
            int maxMultiplicity = max(element.multiplicity, foundInB->multiplicity);
            int result = maxMultiplicity - minMultiplicity;
            symmetricDifference.insert(MultiSetElement(element.element, result));
        }
        else
        {
            symmetricDifference.insert(MultiSetElement(element));
        }
    }

    for (const MultiSetElement& element : setB) {
        auto foundInB = setA.find(element);
        if (foundInB == setA.end()) {
            symmetricDifference.insert(MultiSetElement(element));
        }
    }

    // Арифметическое умножение мультимножеств A и B (пересечение всех элементов)
    multiset<MultiSetElement> productSet = intersectionSet;

    // Арифметическое деление мультимножеств A и B (разность A и пересечения с B)
    multiset<MultiSetElement> divisionSet = differenceAB;


    // Вывод результатов
    cout << "Объединение (A U B): " << endl;
    for (const MultiSetElement& element : unionSet) {
        cout << toGrayCodeString(element.element, n) << "|" << element.multiplicity << endl;
    }
    cout << endl;

    cout << "Пересечение (A ∩ B): " << endl;
    for (const MultiSetElement& element : intersectionSet) {
        cout << toGrayCodeString(element.element, n) << "|" << element.multiplicity << endl;
    }
    cout << endl;

    cout << "Дополнение A (A'): " << endl;
    for (const MultiSetElement& element : complementA) {
        cout << toGrayCodeString(element.element, n) << "|" << element.multiplicity << endl;
    }
    cout << endl;

    cout << "Дополнение B (B'): " << endl;
    for (const MultiSetElement& element : complementB) {
        cout << toGrayCodeString(element.element, n) << "|" << element.multiplicity << endl;
    }
    cout << endl;

    cout << "Разность A \\ B: " << endl;
    for (const MultiSetElement& element : differenceAB) {
        cout << toGrayCodeString(element.element, n) << "|" << element.multiplicity << endl;
    }
    cout << endl;

    cout << "Разность B \\ A: " << endl;
    for (const MultiSetElement& element : differenceBA) {
        cout << toGrayCodeString(element.element, n) << "|" << element.multiplicity << endl;
    }
    cout << endl;

    cout << "Симметрическая разность (A ∆ B): " << endl;
    for (const MultiSetElement& element : symmetricDifference) {
        cout << toGrayCodeString(element.element, n) << "|" << element.multiplicity << endl;
    }
    cout << endl;

    cout << "Арифметическая разность множеств A и B: " << endl;
    for (const MultiSetElement& element : symmetricDifferenceSet) {
        cout << toGrayCodeString(element.element, n) << "|" << element.multiplicity << endl;
    }
    cout << endl;

    cout << "Арифметическое умножение множеств A и B (пересечение): " << endl;
    for (const MultiSetElement& element : productSet) {
        cout << toGrayCodeString(element.element, n) << "|" << element.multiplicity << endl;
    }
    cout << endl;

    cout << "Арифметическое деление множеств A и B: " << endl;
    for (const MultiSetElement& element : divisionSet) {
        cout << toGrayCodeString(element.element, n) << "|" << element.multiplicity << endl;
    }
    cout << endl;

    cout << "Декартово произведение A * B: " << endl;
    for (const pair<MultiSetElement, MultiSetElement>& pairAB : cartesianProductA) {
        cout << "(" << toGrayCodeString(pairAB.first.element, n) << ", " << toGrayCodeString(pairAB.second.element, n) << ") ";
    }
    cout << endl;

    cout << "Декартово произведение B * A: " << endl;
    for (const pair<MultiSetElement, MultiSetElement>& pairAB : cartesianProductB) {
        cout << "(" << toGrayCodeString(pairAB.first.element, n) << ", " << toGrayCodeString(pairAB.second.element, n) << ") ";
    }
    cout << endl;

    for (int i = 0; i < (1 << n); i++)
        delete[] box[i];
    delete[] box;

    return 0;
}
