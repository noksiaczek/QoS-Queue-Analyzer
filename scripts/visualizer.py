# Plik stworzylem z ogromna pomoca sztucznej inteligencji, bo nie znam pythona zbytnio

import pandas as pd
import matplotlib.pyplot as plt

# Wczytanie danych z pliku wygenerowanego przez program w C++
data = pd.read_csv('results.csv')

# Konwersja z mikrosekund na sekundy (1 sekunda = 1 000 000 mikrosekund)
for col in ['CzasWstawianiaKopiec', 'CzasWstawianiaLista', 'CzasUsuwaniaKopiec', 'CzasUsuwaniaLista']:
    data[col] = data[col] / 1000000.0

# Obliczenie czasu całkowitego
data['CzasCalkowityKopiec'] = data['CzasWstawianiaKopiec'] + data['CzasUsuwaniaKopiec']
data['CzasCalkowityLista'] = data['CzasWstawianiaLista'] + data['CzasUsuwaniaLista']


plt.figure(figsize=(18, 5))

# --- Wykres 1: Wstawianie pakietów
plt.subplot(1, 3, 1)
plt.plot(data['RozmiarDanych'], data['CzasWstawianiaKopiec'], label='Min-Heap', marker='o', color='green')
plt.plot(data['RozmiarDanych'], data['CzasWstawianiaLista'], label='Lista (Dopinanie)', marker='x', color='red')
plt.title('Czas wstawiania pakietów')
plt.xlabel('Ilość pakietów w kolejce (N)')
plt.ylabel('Czas [s]')
plt.legend()
plt.grid(True, linestyle='--')

# --- Wykres 2: Wypuszczanie pakietów
plt.subplot(1, 3, 2)
plt.plot(data['RozmiarDanych'], data['CzasUsuwaniaKopiec'], label='Min-Heap', marker='o', color='green')
plt.plot(data['RozmiarDanych'], data['CzasUsuwaniaLista'], label='Lista (Szukanie)', marker='x', color='red')
plt.title('Czas wypuszczania najważniejszego pakietu')
plt.xlabel('Ilość pakietów w kolejce (N)')
plt.ylabel('Czas [s]')
plt.legend()
plt.grid(True, linestyle='--')

# --- Wykres 3: Czas całkowity ---
plt.subplot(1, 3, 3)
plt.plot(data['RozmiarDanych'], data['CzasCalkowityKopiec'], label='Min-Heap (Suma)', marker='o', color='green', linewidth=2)
plt.plot(data['RozmiarDanych'], data['CzasCalkowityLista'], label='Lista (Suma)', marker='x', color='red', linewidth=2)
plt.title('Czas całkowity (Pełna obsługa ruchu)')
plt.xlabel('Ilość pakietów w kolejce (N)')
plt.ylabel('Czas [s]')
plt.legend()
plt.grid(True, linestyle='--')

# Wyświetlenie gotowych wykresów na ekranie
plt.tight_layout()
plt.show()