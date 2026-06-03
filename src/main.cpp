#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <random>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include "../include/MinHeapQueue.h"
#include "../include/LinkedListQueue.h"

/**
 * @brief Uruchamia interaktywna symulacje dzialania routera QoS.
 * Generuje losowy ruch sieciowy, prezentuje stan kopca i proces obslugi pakietow.
 */
void runQoSSimulation() {
    srand(time(NULL));

    const std::string qosApps[10][2] = {
        {"Discord (Rozmowa glosowa)", "MS Teams (Wyklad na zywo)"},
        {"CS:GO (Pakiety gry)", "League of Legends"},
        {"Twitch.tv (Stream live)", "YouTube Live"},
        {"Netflix", "YouTube (Zwykly film VOD)"},
        {"Przegladanie Facebooka", "Wyszukiwanie w Wikipedii"},
        {"Spotify", "Apple Music"},
        {"GitHub (git clone)", "Pobieranie PDF z maila"},
        {"Aktualizacja Windowsa", "Steam (Pobieranie gry)"},
        {"Google Drive (Upload)", "OneDrive (Synchronizacja)"},
        {"uTorrent", "BitTorrent"}
    };

    MinHeapQueue qosQueue;

    for (int i = 0; i < 10; ++i) {
        std::cout << "\033[2J\033[1;1H";

        int randomPrio = (rand() % 10) + 1;
        int randomAppIndex = rand() % 2;
        std::string appName = qosApps[randomPrio - 1][randomAppIndex];

        qosQueue.insert(NetworkPacket{randomPrio, appName});

        std::cout << "============================================\n";
        std::cout << " FAZA 1: ODBIERANIE RUCHU SIECIOWEGO\n";
        std::cout << " Wpadl pakiet: [" << randomPrio << "] " << appName << "\n";
        std::cout << "============================================\n\n";

        qosQueue.printTree();

        std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    }

    std::cout << "\n\nKolejka pelna! Za 3 sekundy router zacznie rozsylac pakiety (Faza 2)...";
    std::cout.flush();
    std::this_thread::sleep_for(std::chrono::seconds(7));

    while (!qosQueue.empty()) {
        std::cout << "\033[2J\033[1;1H";

        NetworkPacket topPacket = qosQueue.front();
        qosQueue.pop();

        std::cout << "============================================\n";
        std::cout << " FAZA 2: QOS WYPUSZCZA NAJWAZNIEJSZY PAKIET\n";
        std::cout << " Wyslano: Prio " << topPacket.prio << " | " << topPacket.type << "\n";
        std::cout << "============================================\n\n";

        qosQueue.printTree();

        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }

    std::cout << "\nWszystkie pakiety obsluzone! Nacisnij Enter, aby wrocic do menu...";
    std::cin.ignore(10000, '\n');
    std::cin.get();
}

/**
 * @brief Przeprowadza testy wydajnosciowe porownujace Min-Heap oraz Liste jednokierunkowa.
 * Mierzy czas wstawiania i usuwania elementow i zapisuje wyniki do pliku results.csv.
 */
void runBenchmark() {
    std::ofstream file("results.csv");
    file << "RozmiarDanych,CzasWstawianiaKopiec,CzasWstawianiaLista,CzasUsuwaniaKopiec,CzasUsuwaniaLista\n";

    std::vector<int> testSizes = {1000, 5000, 10000, 50000, 100000};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 10);

    std::cout << "\nRozpoczynam testy wydajnosciowe...\n";

    for (int N : testSizes) {
        std::cout << "Testuje " << N << " elementow...\n";

        MinHeapQueue heapQueue;
        LinkedListQueue listQueue;

        std::vector<NetworkPacket> packets;
        for (int i = 0; i < N; ++i) {
            packets.push_back({distrib(gen), "TestPacket"});
        }

        auto start = std::chrono::high_resolution_clock::now();
        for (const auto& p : packets)
            heapQueue.insert(p);
        auto end = std::chrono::high_resolution_clock::now();
        long long heapInsertTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        for (const auto& p : packets) listQueue.insert(p);
        end = std::chrono::high_resolution_clock::now();
        long long listInsertTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        while (!heapQueue.empty()) heapQueue.pop();
        end = std::chrono::high_resolution_clock::now();
        long long heapPopTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        while (!listQueue.empty()) listQueue.pop();
        end = std::chrono::high_resolution_clock::now();
        long long listPopTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        file << N << "," << heapInsertTime << "," << listInsertTime << ","
             << heapPopTime << "," << listPopTime << "\n";
    }

    file.close();
    std::cout << "Zapisano wyniki do results.csv!\n";
}

/**
 * @brief Uruchamia skrypt w Pythonie na podstawie juz wygenerowanych danych.
 */
void showGraphs() {
    std::cout << "\nUruchamiam wizualizator Pythona na podstawie zapisanego pliku results.csv...\n";
    std::system("python ../scripts/visualizer.py");
}

/**
 * @brief Glowna funkcja programu, obslugujaca interaktywne menu w petli.
 * @return 0 po poprawnym zakonczeniu.
 */
int main() {
    int choice = 0;
    bool running = true;

    while (running) {
        std::cout << "\033[2J\033[1;1H";
        std::cout << "=======================================\n";
        std::cout << "   QoS Queue Analyzer - Menu Glowne\n";
        std::cout << "=======================================\n";
        std::cout << "1. Uruchom symulacje routera (Min-Heap)\n";
        std::cout << "2. Uruchom testy wydajnosci i wykresy\n";
        std::cout << "3. Pokaz wykresy wydajnosci (z gotowego pliku CSV)\n";
        std::cout << "4. Wyjdz\n";
        std::cout << "Wybierz opcje (1-4): ";
        std::cin >> choice;

        if (choice == 1) {
            runQoSSimulation();
        } else if (choice == 2) {
            runBenchmark();
            showGraphs();
        } else if (choice == 3) {
            showGraphs();
        } else if (choice == 4) {
            running = false;
        } else {
            std::cout << "Niepoprawny wybor. Sprobuj ponownie.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        }
    }

    return 0;
}
