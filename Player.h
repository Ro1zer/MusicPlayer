#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <windows.h>
#include <SFML/Audio.hpp>//—торонн€ б≥бл≥отека,€ку потр≥бно додати до VS
#include <filesystem>
namespace fs = std::filesystem;

class Player {
private:
	std::string folderPath; 
	std::vector<std::string> list;
	//‘ункц≥€ пошуку шл€ху до папки sound
	std::string findFolderPath()
	{
		fs::path currentPath = fs::current_path();
		fs::path musicFolderPath = currentPath / "Music";

		if (fs::exists(musicFolderPath) && fs::is_directory(musicFolderPath))
		{//якщо папка ≥снуЇ:
			return musicFolderPath.string();
		}
		else
		{//≤накше створити папку Music
			fs::create_directory(musicFolderPath);
			return musicFolderPath.string();
		}
	}
public:
	Player():folderPath(findFolderPath()) {
		scanAndAdd();
	}
	//‘ункц≥€ €ка додаЇ назву музики у list
	void scanAndAdd() {
		int go = 0;
		int coincidence = 0;
		for (const auto& entry : fs::directory_iterator(folderPath))
		{//ѕерев≥рка,чи ≥снуЇ така назва у list
			for (int i = 0; i < list.size();i++) {
				if (entry.path().filename().string() == list[i]) {
					coincidence++;
				}
				else {
					continue;
				}
			}
			//якщо сп≥впад≥нн€ знайдено
			if (coincidence>0) {
				continue;
			}
			//якщо такоњ назви не ≥снуЇ н≥де в list
			else {
				list.push_back(entry.path().filename().string());
				go++;
			}
		}//якщо скануанн€ знайшло файл
		if (go>0) {
			std::cout << "Add "<<"(" << go << ")" << " music" << std::endl;
			system("pause");
			return;
		}
		else {//якщо новоњ музики не було знайдено при скануванн≥
			std::cout << "Program doesn't find a new music in the folder" << std::endl;
			system("pause");
			return;
		}
	}
	//‘ункц≥€ виводу вс≥х записаних трек≥в
	void getAll() {
		int  go = 0;
		for (const auto& temp : list) {
			std::cout << "(є" << go++ << ")" << " Music: " << temp << std::endl;
		}
		system("pause");
		return;
	}
	void play(int musicNumber) {
		bool trigger = false;
		//ƒодаЇмо виключенн€ на випадок €кщо користувач введе не≥снуючий номер треку
		for (const auto& entry : fs::directory_iterator(folderPath))
		{//якщо ми вийдемо за межи вектору,або користувач вкаже не≥снуючу ком≥рку list
			if (musicNumber > (list.size() - 1) || musicNumber < 0) {
				system("cls");
				std::cout << "Maximum amount of music exceeded" << std::endl;
				system("pause");
				return;
			}
			else if (entry.path().filename().string() == list[musicNumber]) {
				//¬ывести трек который сейчас играет
				system("cls");
				std::cout << "loading..."<< std::endl;
				sf::SoundBuffer buffer;
				if (!buffer.loadFromFile(entry.path().string()))
				{
					// ќбробка помилки загрузки файлу
					system("pause");
					system("cls");
					return;
				}
				sf::Sound sound;
				sound.setBuffer(buffer);
				sound.play();
				//“екст дл€ користувача
				system("cls");
				std::cout << "Now playing: " << list[musicNumber] << std::endl;
				std::cout << "Click (Esc) if you will off music\n"
					<< "Click (Space) if you will pause/play music\n"
					<< "Click (Enter) if you will restart music\n"
					<< "Click (q) if you will turn previous music\n"
					<< "Click (e) if you will turn next music\n";
				while (sound.getStatus() == sf::Sound::Playing || sound.getStatus() == sf::Sound::Paused)
				{

					char keyPressed;
					keyPressed = _getch();
					//¬ийти
					if (keyPressed == 27) {
						sound.stop();
						system("cls");
						return;
					}//ѕауза
					else if (keyPressed == 32) {
						if (sound.getStatus() == sf::Sound::Paused) {
							std::cout << "Playing" << std::endl;
							sound.play();
						}
						else {
							std::cout << "Paused"<<std::endl;
							sound.pause();
						}

					}//якщо бажаЇмо ув≥мкнути музику заного
					else if (keyPressed == '\r') {
						sound.stop();
						sound.play();
					}//якщо хочемо ув≥мкнути попередню музику
					else if (keyPressed == 81 || keyPressed == 113) {
						sound.stop();
						musicNumber--;
						trigger = true;
						system("cls");
						break;
					}//якщо бажаЇмо ув≥мкнути наступну музику
					else if (keyPressed == 69 || keyPressed == 101) {
						sound.stop();
						musicNumber++;
						trigger = true;
						system("cls");
						break;
					}
				}
			}
			else { continue; }
			}//¬икористовуЇмо рекурс≥ю дл€ того щоб була можлив≥сть перемикатис€ м≥ж треками
		if (trigger == true) {
				play(musicNumber);
		}
	}
	~Player() {
	}
};