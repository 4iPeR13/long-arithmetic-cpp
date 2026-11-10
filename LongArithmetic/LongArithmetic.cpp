#include "LongNumber.h"
#include "LongNumberModulo.h"
#include <stdlib.h>
#include <chrono>


LongNumber generateLongNumber(int n) {
    std::string hexs = "0123456789abcdef";
    std::string result = "";
    result += hexs[rand() % 15 + 1];
    for (int i = 1; i < n; i++) {
        result += hexs[rand() % 16];
    }
    return LongNumber(result);
}

void TestNumbers() {
    LongNumber A("53656cec489801ea6e0e2eb8713db96dc89de8851b73d468163ad6b6baad7a5336aca9adac00c57142b6163a4a52561d5a96b4601628393d9e9cda5a8e43920c");
    LongNumber B("ab4502d3b5509e044da80acd63d08aba46c1d6ae371b8b0b580ae6bd116d7bec848e156c5183917a6804ab6b1c57320739901d1e3d68e4b99db98d9652532074");

    LongNumber N("3524b9b3c12aa844e551d242a857b575e076c83ba157db75e66e43bc7324206731428b2566721e0a72e72445902814b3674953cec5732179262d36e981ca56d");
    LongNumberModulo modulo(N);



    std::cout << "A + B mod N = " << modulo.add(A, B) << '\n';
    std::cout << "A - B mod N = " << modulo.sub(A, B) << '\n';
    std::cout << "A * B mod N = " << modulo.mult(A, B) << '\n';
    std::cout << "A ^ 2 mod N = " << modulo.square(A) << '\n';

    std::cout << "A ^ B mod N = " << modulo.power(A, B) << '\n';

    std::cout << "gcd(A,B) = " << LongNumber::GCD(A, B) << '\n';
    std::cout << "lcm(A,B) = " << LongNumber::LCM(A, B) << '\n';

}


int main()
{

    TestNumbers();

    int numberOfMeasurements = 200;
    int size = 128;

    long long nanoseconds = 0;

    for (int i = 0; i < numberOfMeasurements; i++) {
        LongNumber first = generateLongNumber(size);
        LongNumber second = generateLongNumber(size);

        LongNumber mod = generateLongNumber(size / 2);

        LongNumberModulo modulo(mod);
        const auto start{ std::chrono::high_resolution_clock::now() };
        modulo.add(first,second);
        const auto end{ std::chrono::high_resolution_clock::now() };
        const std::chrono::duration<int64_t, std::nano> elapsed_seconds{ end - start };
        nanoseconds += elapsed_seconds.count();
    }

    std::cout << "Elapsed nanoseconds for addition: " << nanoseconds / numberOfMeasurements << '\n';

    nanoseconds = 0;

    for (int i = 0; i < numberOfMeasurements; i++) {
        LongNumber first = generateLongNumber(size);
        LongNumber second = generateLongNumber(size);

        LongNumber mod = generateLongNumber(size / 2);

        LongNumberModulo modulo(mod);
        const auto start{ std::chrono::high_resolution_clock::now() };
        modulo.sub(first, second);
        const auto end{ std::chrono::high_resolution_clock::now() };
        const std::chrono::duration<int64_t, std::nano> elapsed_seconds{ end - start };
        nanoseconds += elapsed_seconds.count();
    }

    std::cout << "Elapsed nanoseconds for subtraction: " << nanoseconds / numberOfMeasurements << '\n';

    nanoseconds = 0;

    for (int i = 0; i < numberOfMeasurements; i++) {
        LongNumber first = generateLongNumber(size);
        LongNumber second = generateLongNumber(size);

        LongNumber mod = generateLongNumber(size);

        LongNumberModulo modulo(mod);
        const auto start{ std::chrono::high_resolution_clock::now() };
        modulo.mult(first, second);
        const auto end{ std::chrono::high_resolution_clock::now() };
        const std::chrono::duration<int64_t, std::nano> elapsed_seconds{ end - start };
        nanoseconds += elapsed_seconds.count();
    }

    std::cout << "Elapsed nanoseconds for multiplication: " << nanoseconds / numberOfMeasurements << '\n';
    nanoseconds = 0;

    for (int i = 0; i < numberOfMeasurements; i++) {
        LongNumber first = generateLongNumber(size);
        LongNumber second = generateLongNumber(size/2);

        LongNumber mod = generateLongNumber(size);

        LongNumberModulo modulo(mod);
        const auto start{ std::chrono::high_resolution_clock::now() };
        modulo.power(first, second);
        const auto end{ std::chrono::high_resolution_clock::now() };
        const std::chrono::duration<int64_t, std::nano> elapsed_seconds{ end - start };
        nanoseconds += elapsed_seconds.count();
    }

    std::cout << "Elapsed nanoseconds for power: " << nanoseconds / numberOfMeasurements << '\n';
    nanoseconds = 0;

    for (int i = 0; i < numberOfMeasurements; i++) {
        auto first = generateLongNumber(size);
        auto second = generateLongNumber(size);

        const auto start{ std::chrono::high_resolution_clock::now() };
        LongNumber::GCD(first,second);
        const auto end{ std::chrono::high_resolution_clock::now() };
        const std::chrono::duration<int64_t, std::nano> elapsed_seconds{ end - start };
        nanoseconds += elapsed_seconds.count();
    }

    std::cout << "Elapsed nanoseconds for gcd: " << nanoseconds / numberOfMeasurements << '\n';

    nanoseconds = 0;
    for (int i = 0; i < numberOfMeasurements; i++) {
        auto first = generateLongNumber(size);
        auto second = generateLongNumber(size);

        const auto start{ std::chrono::high_resolution_clock::now() };
        LongNumber::LCM(first, second);
        const auto end{ std::chrono::high_resolution_clock::now() };
        const std::chrono::duration<int64_t, std::nano> elapsed_seconds{ end - start };
        nanoseconds += elapsed_seconds.count();
    }

    std::cout << "Elapsed nanoseconds for lcm: " << nanoseconds / numberOfMeasurements << '\n';




}

