#include <iostream>
#include <pthread.h>
#include <queue>
#include <map>
#include <chrono>
using namespace std;
pthread_mutex_t critMatrRes;
pthread_mutex_t critBlock[500][500];
pthread_mutex_t critQ1;
pthread_mutex_t critQ2;
pthread_mutex_t critQ3;
queue<map<string, int> > q1;
queue<map<string, int> > q2;
queue<map<string, int> > q3;
int** matr1;
int** matr2;

void f(int** arr, int n, int m) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < m; k++) {
                arr[i][j] += matr1[i][k] * matr2[k][j];
            }
        }
    }
}

void* f1(void* a123) {
    int** arr = (int**)a123;
    map<string, int> mapMatr;
    int a;
    int b;
    int n;
    int m;
    int* str;
    int* row;
    while (true) {
        pthread_mutex_lock(&critQ1);
        if (q1.size() == 0) {
            pthread_mutex_unlock(&critQ1);
            break;
        }
        mapMatr = q1.front();
        q1.pop();
        pthread_mutex_unlock(&critQ1);
        a = mapMatr.find("a")->second;
        b = mapMatr.find("b")->second;
        m = mapMatr.find("m")->second;
        str = new int[m];
        row = new int[m];
        for (int i = 0; i < m; i++) str[i] = matr1[a][i];
        for (int i = 0; i < m; i++) row[i] = matr2[i][b];

        arr[a][b] = 0;
        for (int i = 0; i < m; i++) {
            arr[a][b] += str[i] * row[i];
        }
    }
}

void* f2(void* a123) {
    int** arr = (int**)a123;
    map<string, int> mapMatr;
    int a;
    int n;
    int m;
    int* str;
    int* row;
    while (true) {
        pthread_mutex_lock(&critQ2);
        if (q2.size() == 0) {
            pthread_mutex_unlock(&critQ2);
            break;
        }
        mapMatr = q2.front();
        q2.pop();
        pthread_mutex_unlock(&critQ2);
        a = mapMatr.find("a")->second;
        n = mapMatr.find("n")->second;
        str = new int[n];
        row = new int[n];
        for (int i = 0; i < n; i++) row[i] = matr1[i][a];
        for (int i = 0; i < n; i++) str[i] = matr2[a][i];

        int** tmparr = new int* [n];
        for (int i = 0; i < n; i++) {
            tmparr[i] = new int[n];
            for (int j = 0; j < n; j++) {
                tmparr[i][j] = row[i] * str[j];
            }
        }
        pthread_mutex_lock(&critMatrRes);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                arr[i][j] += tmparr[i][j];
            }
        }
        pthread_mutex_unlock(&critMatrRes);
    }
}

void* f3(void* a123) {
    int** arr = (int**)a123;
    map<string, int> mapMatr;
    int a1;
    int b1;
    int a2;
    int b2;
    int n1;
    int m1;
    int n2;
    int m2;
    int k;
    int** arr1;
    int** arr2;
    while (true) {
        pthread_mutex_lock(&critQ3);
        if (q3.size() == 0) {
            pthread_mutex_unlock(&critQ3);
            break;
        }
        mapMatr = q3.front();
        q3.pop();
        pthread_mutex_unlock(&critQ3);
        a1 = mapMatr.find("a1")->second;
        b1 = mapMatr.find("b1")->second;
        a2 = mapMatr.find("a2")->second;
        b2 = mapMatr.find("b2")->second;
        n1 = mapMatr.find("n1")->second;
        n2 = mapMatr.find("n2")->second;
        m1 = mapMatr.find("m1")->second;
        m2 = mapMatr.find("m2")->second;
        k = mapMatr.find("k")->second;
        arr1 = new int* [n1];
        arr2 = new int* [n2];
        for (int i = 0; i < n1; i++) {
            arr1[i] = new int[m1];
            for (int j = 0; j < m1; j++) arr1[i][j] = matr1[a1 + i][b1 + j];
        }
        for (int i = 0; i < n2; i++) {
            arr2[i] = new int[m2];
            for (int j = 0; j < m2; j++) arr2[i][j] = matr2[a2 + i][b2 + j];
        }
        int** tmparr = new int* [n1];
        for (int i = 0; i < n1; i++) {
            tmparr[i] = new int[m2];
            for (int j = 0; j < m2; j++) {
                tmparr[i][j] = 0;
                for (int k = 0; k < n2; k++) {
                    tmparr[i][j] += arr1[i][k] * arr2[k][j];
                }
            }
        }
        pthread_mutex_lock(&(critBlock[a1 / k][b2 / k]));
        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < m2; j++) {
                arr[a1 + i][b2 + j] += tmparr[i][j];
            }
        }
        pthread_mutex_unlock(&(critBlock[a1 / k][b2 / k]));
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    freopen("input.txt", "r", stdin);

    pthread_mutex_init(&critMatrRes, NULL);
    pthread_mutex_init(&critQ1, NULL);
    pthread_mutex_init(&critQ2, NULL);
    pthread_mutex_init(&critQ3, NULL);
    map<string, int> tmp;
    int n;
    int m;
    int k;
    cout << "Enter n, m, k(n*m, m*n, k^2 blocks, k threads)\n";
    cin >> n >> m;
    cin >> k;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            pthread_mutex_init(&critBlock[i][j], NULL);
        }
    }
    matr1 = new int* [n];
    cout << "\nEnter matrix A\n";
    for (int i = 0; i < n; i++) {
        matr1[i] = new int[m];
        for (int j = 0; j < m; j++) {
            cin >> matr1[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tmp.clear();
            tmp.insert(make_pair("a", i));
            tmp.insert(make_pair("b", j));
            tmp.insert(make_pair("m", m));
            q1.push(tmp);
        }
    }
    for (int i = 0; i < m; i++) {
        tmp.clear();
        tmp.insert(make_pair("a", i));
        tmp.insert(make_pair("n", n));
        q2.push(tmp);
    }
    matr2 = new int* [m];
    cout << "\nEnter matrix B\n";
    for (int i = 0; i < m; i++) {
        matr2[i] = new int[n];
        for (int j = 0; j < n; j++) {
            cin >> matr2[i][j];
        }
    }
    int n1 = n;
    int m1 = m;
    int* size1 = new int[k];
    int* size2 = new int[k];
    for (int i = 0; i < k - 1; i++) {
        size1[i] = n / k;
        n1 -= n / k;
        size2[i] = m / k;
        m1 -= m / k;
    }
    size1[k - 1] = n1;
    size2[k - 1] = m1;
    n1 = 0;
    int n2 = 0;
    int m2 = 0;
    for (int i = 0; i < k; i++) {
        m1 = 0;
        for (int j = 0; j < k; j++) {
            n2 = 0;
            for (int l = 0; l < k; l++) {
                tmp.clear();
                tmp.insert(make_pair("a1", n1));
                tmp.insert(make_pair("a2", m1));
                tmp.insert(make_pair("b1", m1));
                tmp.insert(make_pair("b2", n2));
                tmp.insert(make_pair("n1", size1[i]));
                tmp.insert(make_pair("m1", size2[j]));
                tmp.insert(make_pair("n2", size2[j]));
                tmp.insert(make_pair("m2", size1[l]));
                tmp.insert(make_pair("k", k));
                q3.push(tmp);
                n2 += size1[l];
            }
            m1 += size2[j];
        }
        n1 += size1[i];
    }
    int** res = new int* [n];

    for (int i = 0; i < n; i++) {
        res[i] = new int[n];
        for (int j = 0; j < n; j++) {
            res[i][j] = 0;
        }
    }
    auto start = std::chrono::steady_clock::now();
    f(res, n, m);
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "\n" << duration.count() << " ms";

    cout << "\nf\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << res[i][j] << " ";
        }
        cout << "\n";
    }

    for (int i = 0; i < n; i++) res[i] = new int[n];
    pthread_t* arrH = new pthread_t[k];
    start = std::chrono::steady_clock::now();
    for (int i = 0; i < k; i++) {
        pthread_create(&arrH[i], NULL, &f1, (void*)(res));
        pthread_join(arrH[i], NULL);
    }
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "\n" << duration.count() << " ms";

    cout << "\nf1\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << res[i][j] << " ";
        }
        cout << "\n";
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = 0;
        }
    }
    start = std::chrono::steady_clock::now();
    for (int i = 0; i < k; i++) {
        pthread_create(&arrH[i], NULL, &f2, (void*)(res));
        pthread_join(arrH[i], NULL);
    }
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "\n" << duration.count() << " ms";

    cout << "\nf2\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << res[i][j] << " ";
        }
        cout << "\n";
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = 0;
        }
    }

    start = std::chrono::steady_clock::now();
    for (int i = 0; i < k; i++) {
        pthread_create(&arrH[i], NULL, &f3, (void*)(res));
        pthread_join(arrH[i], NULL);
    }
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "\n" << duration.count() << " ms";

    cout << "\nf3\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << res[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
