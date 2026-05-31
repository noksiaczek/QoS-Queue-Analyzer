import pandas as pd
import matplotlib.pyplot as plt

# Wczytanie danych z pliku wygenerowanego przez Twój program w C++
data = pd.read_csv('results.csv')

# Ustawienie rozmiaru okna z wykresami
plt.figure(figsize=(12, 5))

# --- Wykres 1: Wstawianie pakietów ---
plt.subplot(1, 2, 1)
plt.plot(data['RozmiarDanych'], data['CzasWstawianiaKopiec'], label='Min-Heap', marker='o', color='green')
plt.plot(data['RozmiarDanych'], data['CzasWstawianiaLista'], label='Lista (Zwykłe dopinanie)', marker='x', color='red')
plt.title('Czas wstawiania pakietów')
plt.xlabel('Ilość pakietów w kolejce (N)')
plt.ylabel('Czas [mikrosekundy]')
plt.legend()
plt.grid(True, linestyle='--')

# --- Wykres 2: Wypuszczanie pakietów (QoS) ---
plt.subplot(1, 2, 2)
plt.plot(data['RozmiarDanych'], data['CzasUsuwaniaKopiec'], label='Min-Heap (Opadanie)', marker='o', color='green')
plt.plot(data['RozmiarDanych'], data['CzasUsuwaniaLista'], label='Lista (Szukanie minimum)', marker='x', color='red')
plt.title('Czas wypuszczania najważniejszego pakietu')
plt.xlabel('Ilość pakietów w kolejce (N)')
plt.ylabel('Czas [mikrosekundy]')
plt.legend()
plt.grid(True, linestyle='--')

# Wyświetlenie gotowych wykresów na ekranie
plt.tight_layout()
plt.show()