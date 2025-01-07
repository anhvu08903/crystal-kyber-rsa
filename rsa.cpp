#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Hàm tính a^b mod n
long long pow_mod(long long a, long long b, long long n) {
    long long result = 1;
    a = a % n;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % n;
        }
        b = b >> 1;
        a = (a * a) % n;
    }
    return result;
}

// Hàm mã hóa m?t t? thành s? nguyên
long long encode_word(const string &word) {
    const int base = 26;
    long long value = 0;
    for (char c : word) {
        value = value * base + (c - 'A');
    }
    return value;
}

// Hàm gi?i mã s? nguyên thành t?
string decode_word(long long value) {
    const int base = 26;
    string word = "";
    while (value > 0) {
        word = char((value % base) + 'A') + word;
        value /= base;
    }
    return word;
}

// Hàm mã hóa m?t thông di?p
vector<long long> rsa_encrypt(const vector<string> &message, long long d, long long n) {
    vector<long long> encrypted_message;
    for (const string &word : message) {
        long long encoded_word = encode_word(word);
        long long encrypted_word = pow_mod(encoded_word, d, n);
        encrypted_message.push_back(encrypted_word);
    }
    return encrypted_message;
}

// Hàm tìm u?c chung l?n nh?t (GCD)
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Hàm tìm ngh?ch d?o modular s? d?ng thu?t toán Euclid m? r?ng
long long mod_inverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Hàm gi?i mã m?t thông di?p
vector<string> rsa_decrypt(const vector<long long> &encrypted_message, long long e, long long n) {
    vector<string> decrypted_message;
    for (long long encrypted_word : encrypted_message) {
        long long decrypted_word = pow_mod(encrypted_word, e, n);
        decrypted_message.push_back(decode_word(decrypted_word));
    }
    return decrypted_message;
}

// Phân tích n thành tích c?a 2 s? nguyên t?
pair<long long, long long> factorize_n(long long n) {
    for (long long i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return {i, n / i};
        }
    }
    return {0, 0}; // Tru?ng h?p không tìm du?c th?a s? (ch? x?y ra n?u n là s? nguyên t?)
}

// Tính f(n)
long long compute_phi(long long p, long long q) {
    return (p - 1) * (q - 1);
}

int main() {
    // Khóa công khai
    long long d = 7;
    long long n = 187;

    // B?n rõ
    vector<string> message = {"DOG", "CAT"};

    // Mã hóa
    vector<long long> encrypted_message = rsa_encrypt(message, d, n);
    cout << "Encrypted message: ";
    for (long long num : encrypted_message) {
        cout << num << " ";
    }
    cout << endl;

    // Phá mã
    auto [p, q] = factorize_n(n);
    long long phi_n = compute_phi(p, q);
    long long e = mod_inverse(d, phi_n);
    vector<string> decrypted_message = rsa_decrypt(encrypted_message, e, n);
    cout << "Decrypted message: ";
    for (const string &word : decrypted_message) {
        cout << word << " ";
    }
    cout << endl;

    return 0;
}
