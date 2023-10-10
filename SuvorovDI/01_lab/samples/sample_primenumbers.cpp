#include <iostream>
#include "tbitfield.h"

using namespace std;
int main()
{
    int n, m, k, count;

    setlocale(LC_ALL, "Russian");

    /*cout << "Решето Эратосфена" << endl;
    cout << "Использование класса \"Битовое поле\"" << endl;

    cout << "Введите максимальное целое число: ";*/
    cin >> n;

    TBitField s(n + 1);
    // заполнение множества
    for (m = 2; m <= n; m++)
        s.SetBit(m);
    // проверка до sqrt(n) и удаление кратных
    for (m = 2; m * m <= n; m++)
        // если m в s, удаление кратных
        if (s.GetBit(m))
            for (k = 2 * m; k <= n; k += m)
            s.ClrBit(k);

    //оставшиеся в s элементы - простые числа
    /*cout << endl << "Печать множества некратных чисел" << endl << s << endl;
    cout << endl << "Печать простых чисел" << endl;*/

    count = 0;
    k = 1;
    for (m = 2; m <= n; m++)
        if (s.GetBit(m)) {
            count++;
            cout << m << " ";
            if (k++ % 10 == 0)
                cout << endl;
        }

    cout << endl;
    /*cout << "В первых " << n << " числах " << count << " простых" << endl;*/

    return 0;
}