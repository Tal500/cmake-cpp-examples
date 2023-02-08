#include <string>

#include "./MemoStore.h"

const std::string& MemoStore::topMemo() const {
	return _memos.back();
}

const std::string& MemoStore::getMemo(int index) const {
	return _memos[index];
}

std::size_t MemoStore::size() const {
	return _memos.size();
}

bool MemoStore::empty() const {
	return _memos.empty();
}

void MemoStore::pushMemo(const std::string& memo) {
	_memos.push_back(memo);
}

std::string MemoStore::fetchMemo(int index) {
	const std::string memo = std::move(_memos[index]);
	_memos.erase(_memos.begin() + index);
	return memo;
}