#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <windows.h>
#include <SFML/Audio.hpp>//�������� ��������,��� ������� ������ �� VS
#include <filesystem>
namespace fs = std::filesystem;

class Player {
private:
	std::string folderPath; 
	std::vector<std::string> list;
	//������� ������ ����� �� ����� sound
	std::string findFolderPath()
	{
		fs::path currentPath = fs::current_path();
		fs::path musicFolderPath = currentPath / "Music";

		if (fs::exists(musicFolderPath) && fs::is_directory(musicFolderPath))
		{//���� ����� ����:
			return musicFolderPath.string();
		}
		else
		{//������ �������� ����� Music
			fs::create_directory(musicFolderPath);
			return musicFolderPath.string();
		}
	}
public:
	Player():folderPath(findFolderPath()) {
		scanAndAdd();
	}
	//������� ��� ���� ����� ������ � list
	void scanAndAdd() {
		int go = 0;
		int coincidence = 0;
		for (const auto& entry : fs::directory_iterator(folderPath))
		{//��������,�� ���� ���� ����� � list
			for (int i = 0; i < list.size();i++) {
				if (entry.path().filename().string() == list[i]) {
					coincidence++;
				}
				else {
					continue;
				}
			}
			//���� ��������� ��������
			if (coincidence>0) {
				continue;
			}
			//���� ���� ����� �� ���� ��� � list
			else {
				list.push_back(entry.path().filename().string());
				go++;
			}
		}//���� ��������� ������� ����
		if (go>0) {
			std::cout << "Add "<<"(" << go << ")" << " music" << std::endl;
			system("pause");
			return;
		}
		else {//���� ���� ������ �� ���� �������� ��� ���������
			std::cout << "Program doesn't find a new music in the folder" << std::endl;
			system("pause");
			return;
		}
	}
	//������� ������ ��� ��������� �����
	void getAll() {
		int  go = 0;
		for (const auto& temp : list) {
			std::cout << "(�" << go++ << ")" << " Music: " << temp << std::endl;
		}
		system("pause");
		return;
	}
	void play(int musicNumber) {
		bool trigger = false;
		//������ ���������� �� ������� ���� ���������� ����� ��������� ����� �����
		for (const auto& entry : fs::directory_iterator(folderPath))
		{//���� �� ������� �� ���� �������,��� ���������� ����� �������� ������ list
			if (musicNumber > (list.size() - 1) || musicNumber < 0) {
				system("cls");
				std::cout << "Maximum amount of music exceeded" << std::endl;
				system("pause");
				return;
			}
			else if (entry.path().filename().string() == list[musicNumber]) {
				//������� ���� ������� ������ ������
				system("cls");
				std::cout << "loading..."<< std::endl;
				sf::SoundBuffer buffer;
				if (!buffer.loadFromFile(entry.path().string()))
				{
					// ������� ������� �������� �����
					system("pause");
					system("cls");
					return;
				}
				sf::Sound sound;
				sound.setBuffer(buffer);
				sound.play();
				//����� ��� �����������
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
					//�����
					if (keyPressed == 27) {
						sound.stop();
						system("cls");
						return;
					}//�����
					else if (keyPressed == 32) {
						if (sound.getStatus() == sf::Sound::Paused) {
							std::cout << "Playing" << std::endl;
							sound.play();
						}
						else {
							std::cout << "Paused"<<std::endl;
							sound.pause();
						}

					}//���� ������ �������� ������ ������
					else if (keyPressed == '\r') {
						sound.stop();
						sound.play();
					}//���� ������ �������� ��������� ������
					else if (keyPressed == 81 || keyPressed == 113) {
						sound.stop();
						musicNumber--;
						trigger = true;
						system("cls");
						break;
					}//���� ������ �������� �������� ������
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
			}//������������� ������� ��� ���� ��� ���� ��������� ������������ �� �������
		if (trigger == true) {
				play(musicNumber);
		}
	}
	~Player() {
	}
};