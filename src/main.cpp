#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <random>
#include <string>
#include <cstdlib>
#include <ctime>
#include "../include/MinHeapQueue.h"
#include "../include/LinkedListQueue.h"

/**
 * @brief Uruchamia interaktywną symulację działania routera QoS.
 * Generuje losowy ruch sieciowy z uwzględnieniem priorytetów (1-10)
 * i prezentuje proces obsługi najważniejszych pakietów z wykorzystaniem kopca minimalnego.
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

    std::cout << "\n--- Faza 1: Odbieranie chaotycznego ruchu ---\n";
    for (int i = 0; i < 20; ++i) {
        int randomPrio = (rand() % 10) + 1;
        int randomAppIndex = rand() % 2;
        std::string appName = qosApps[randomPrio - 1][randomAppIndex];

        qosQueue.insert(NetworkPacket{randomPrio, appName});
        std::cout << "Wpadl pakiet: [" << randomPrio << "] " << appName << "\n";
    }

    std::cout << "\n--- Faza 2: Wypuszczanie pakietow wedlug priorytetu ---\n";
    while (!qosQueue.empty()) {
        NetworkPacket topPacket = qosQueue.front();
        std::cout << "Wysylam: Prio " << topPacket.prio << " | Aplikacja: " << topPacket.type << "\n";
        qosQueue.pop();
    }
}

/**
 * @brief Przeprowadza testy wydajnościowe porównujące Min-Heap oraz Listę jednokierunkową.
 * Mierzy czas wstawiania i usuwania elementów (od 1000 do 100000) w mikrosekundach.
 * Zapisuje wyniki do pliku results.csv i wywołuje skrypt wizualizacyjny w Pythonie.
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
        for (const auto& p : packets) heapQueue.insert(p);
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
 * @brief Uruchamia skrypt w Pythonie na podstawie już wygenerowanych danych.
 * Oszczędza czas podczas prezentacji, pomijając ponowne przeliczanie.
 */
void showGraphs() {
    std::cout << "\nUruchamiam wizualizator Pythona na podstawie zapisanego pliku results.csv...\n";
    std::system("python ../scripts/visualizer.py");
}

/**
 * @brief Główna funkcja programu, obsługująca interaktywne menu.
 * @return 0 po poprawnym zakończeniu.
 */
int main() {
    int choice = 0;

    std::cout << "=======================================\n";
    std::cout << "   QoS Queue Analyzer - Menu Glowne\n";
    std::cout << "=======================================\n";
    std::cout << "1. Uruchom symulacje routera (Min-Heap)\n";
    std::cout << "2. Uruchom testy wydajnosci i wykresy\n";
    std::cout << "3. Pokaz wykresy wydajnosci (z gotowego pliku CSV)\n";
    std::cout << "Wybierz opcje (1-3): ";
    std::cin >> choice;

    if (choice == 1) {
        runQoSSimulation();
    } else if (choice == 2) {
        runBenchmark();
    } else if (choice == 3) {
        showGraphs();
    } else {
        std::cout << "Niepoprawny wybor.\n";
    }

    return 0;
}