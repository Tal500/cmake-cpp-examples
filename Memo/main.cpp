// CMakeProject1.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <vector>
#include <string>
#include <array>

#include "./MemoStore.h"
#include "./MemoChoice.h"

int locationChoiceFromUser(const auto& list) {
	while (true) {
		int chosen;
		std::cin >> chosen;

		if (chosen < 1 || chosen > list.size()) {
			std::cerr << "Choise is out of range! Try Again" << std::endl;
		}
		else
		{
			return chosen - 1;
		}
	}
}

const std::array choices{
	MemoChoice{.title = "Add memo",.method = [](MemoStore& memos) -> bool {
		std::cout << "Please enter memo:" << std::endl;

		std::string currentMemo;
		std::cin.ignore();
		std::getline(std::cin, currentMemo);
		memos.pushMemo(currentMemo);

		std::cout << "The following memo was added: " << currentMemo << std::endl;

		return true;
	}},
	MemoChoice{.title = "Print Top Memo",.method = [](MemoStore& memos) -> bool {
		if (memos.empty())
		{
			std::cout << "Memo store is empty!" << std::endl;
		}
		else
		{
			std::cout << "Your memo: " << memos.topMemo() << std::endl;
		}
		return true;
	}},
	MemoChoice{.title = "Get Memo",.method = [](MemoStore& memos) -> bool {
		if (memos.empty())
		{
			std::cout << "Memo store is empty!" << std::endl;
		}
		else
		{
			int location = locationChoiceFromUser(memos);
			std::cout << "Your memo: " << memos.getMemo(location) << std::endl;
		}
		return true;
	}},
	MemoChoice{.title = "Retrieve and Remove Memo",.method = [](MemoStore& memos) -> bool {
		if (memos.empty())
		{
			std::cout << "Memo store is empty!" << std::endl;
		}
		else
		{
			int location = locationChoiceFromUser(memos);
			std::cout << "Your memo: " << memos.fetchMemo(location) << std::endl;
		}
		return true;
	}},
	MemoChoice{.title = "Exit",.method = [](MemoStore& memos) -> bool {
		std::cout << "Bye Bye!" << std::endl;
		return false;
	}}
};

bool step(MemoStore& memos) {
	std::cout << "Please choose:" << std::endl;

	for (int i = 0; i < choices.size(); ++i) {
		std::cout << (i + 1) << ". " << choices[i].title << std::endl;
	}

	int chosen = locationChoiceFromUser(choices);

	return choices[chosen].method(memos);
}

int main()
{
	MemoStore memos;

	while (step(memos)) {}

	return 0;
}
